/*	SIM-VICUS - Building and District Energy Simulation Tool.

	Copyright (c) 2020-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
	  Dirk Weiss  <dirk.weiss -[at]- tu-dresden.de>
	  Stephan Hirth  <stephan.hirth -[at]- tu-dresden.de>
	  Hauke Hirsch  <hauke.hirsch -[at]- tu-dresden.de>

	  ... all the others from the SIM-VICUS team ... :-)

	This program is part of SIM-VICUS (https://github.com/ghorwin/SIM-VICUS)

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
*/

#include "SVPropEditGeometry.h"
#include "IBKMK_2DCalculations.h"
#include "RC_VicusClipping.h"
#include "ui_SVPropEditGeometry.h"

#include <IBK_physics.h>

#include <IBKMK_3DCalculations.h>
#include <IBKMK_Quaternion.h>

#include <QtExt_ValidatingLineEdit.h>
#include <QtExt_ValidatingInputBase.h>

#include <VICUS_Project.h>
#include <VICUS_Object.h>
#include <VICUS_BuildingLevel.h>
#include <VICUS_Polygon3D.h>
#include <VICUS_utilities.h>

#include <QMessageBox>
#include <QQuaternion>

#include <SVConversions.h>

#include "SVViewStateHandler.h"
#include "SVProjectHandler.h"
#include "SVUndoModifySurfaceGeometry.h"
#include "SVUndoAddSurface.h"
#include "SVUndoAddZone.h"
#include "SVUndoModifyProject.h"
#include "SVUndoTrimObjects.h"
#include "SVUndoCopyBuildingGeometry.h"
#include "SVPropVertexListWidget.h"
#include "SVGeometryView.h"
#include "SVPropAddWindowWidget.h"
#include "SVLocalCoordinateView.h"

#include "Vic3DNewGeometryObject.h"
#include "Vic3DCoordinateSystemObject.h"
#include "Vic3DWireFrameObject.h"
#include "Vic3DTransform3D.h"
#include "Vic3DSceneView.h"

#include <QLocale>
#include <QWheelEvent>
#include <QProgressDialog>


///*! helper function to compare two IBKMK vectors */
//template <int digits>
//static bool vectors_equal(const IBKMK::Vector3D &v1, const IBKMK::Vector3D &v2 ) {
//	return ( IBK::nearly_equal<digits>(v1.m_x, v2.m_x) &&
//			 IBK::nearly_equal<digits>(v1.m_y, v2.m_y) &&
//			 IBK::nearly_equal<digits>(v1.m_z, v2.m_z) );
//}

class TrimmingProgress : public IBK::Notification {
public:
	void notify() override {}
	void notify(double percentage) override;

	char				pad[7]; // fix padding, silences compiler warning
	QProgressDialog		*m_prgDlg = nullptr;
};

void TrimmingProgress::notify(double percentage) {
	m_prgDlg->setValue((int)(m_prgDlg->maximum() * percentage));
	qApp->processEvents();
	if (m_prgDlg->wasCanceled())
		m_aborted = true;
}


class LineEditFormater : public QtExt::FormatterBase {
public:
	~LineEditFormater() override;
	QString formatted(double value) override {
		return QString("%L1").arg(value, 0, 'f', 3);
	}
};

// dummy destructor needed to tell compiler to place virtual function table in this object file
LineEditFormater::~LineEditFormater() {}


// *** Widget implementation ***

SVPropEditGeometry::SVPropEditGeometry(QWidget *parent) :
	QWidget(parent),
	m_copyTranslationVector(0,0,3),
	m_ui(new Ui::SVPropEditGeometry)
{
	m_ui->setupUi(this);
	// remove layout margins for all pages
	for (int i=0; i<NUM_MT; ++i)
		m_ui->stackedWidget->widget(i)->layout()->setMargin(0);

	installEventFilter(this);
	SVViewStateHandler::instance().m_propEditGeometryWidget = this;

	connect(&SVProjectHandler::instance(), &SVProjectHandler::modified,
			this, &SVPropEditGeometry::onModified);

	connect(&SVViewStateHandler::instance(), &SVViewStateHandler::viewStateChanged,
			this, &SVPropEditGeometry::onViewStateChanged);

	m_ui->lineEditTranslateX->setFormatter(new LineEditFormater);
	m_ui->lineEditTranslateY->setFormatter(new LineEditFormater);
	m_ui->lineEditTranslateZ->setFormatter(new LineEditFormater);

	m_ui->lineEditTranslateX->installEventFilter(this);
	m_ui->lineEditTranslateY->installEventFilter(this);
	m_ui->lineEditTranslateZ->installEventFilter(this);


	m_ui->lineEditRotateOrientation->setFormatter(new LineEditFormater);
	m_ui->lineEditRotateInclination->setFormatter(new LineEditFormater);
	m_ui->lineEditRotateInclination->setup(-90, 90, tr("Inclination must be between -90..90°."), true, true);
	m_ui->lineEditRotateX->setFormatter(new LineEditFormater);
	m_ui->lineEditRotateY->setFormatter(new LineEditFormater);
	m_ui->lineEditRotateZ->setFormatter(new LineEditFormater);

	m_ui->lineEditRotateOrientation->installEventFilter(this);
	m_ui->lineEditRotateInclination->installEventFilter(this);
	m_ui->lineEditRotateX->installEventFilter(this);
	m_ui->lineEditRotateY->installEventFilter(this);
	m_ui->lineEditRotateZ->installEventFilter(this);


	m_ui->lineEditScaleX->setup(0, 1E5, tr("A positive value is required here."), false, true);
	m_ui->lineEditScaleY->setup(0, 1E5, tr("A positive value is required here."), false, true);
	m_ui->lineEditScaleZ->setup(0, 1E5, tr("A positive value is required here."), false, true);

	m_ui->lineEditRotateXTrimming->setFormatter(new LineEditFormater);
	m_ui->lineEditRotateYTrimming->setFormatter(new LineEditFormater);
	m_ui->lineEditRotateZTrimming->setFormatter(new LineEditFormater);
	m_ui->lineEditRotateXTrimming->installEventFilter(this);
	m_ui->lineEditRotateYTrimming->installEventFilter(this);
	m_ui->lineEditRotateZTrimming->installEventFilter(this);

	m_ui->lineEditTranslateTrimmingX->setFormatter(new LineEditFormater);
	m_ui->lineEditTranslateTrimmingY->setFormatter(new LineEditFormater);
	m_ui->lineEditTranslateTrimmingZ->setFormatter(new LineEditFormater);
	m_ui->lineEditTranslateTrimmingX->installEventFilter(this);
	m_ui->lineEditTranslateTrimmingY->installEventFilter(this);
	m_ui->lineEditTranslateTrimmingZ->installEventFilter(this);

	m_ui->lineEditScaleX->setFormatter(new LineEditFormater);
	m_ui->lineEditScaleY->setFormatter(new LineEditFormater);
	m_ui->lineEditScaleZ->setFormatter(new LineEditFormater);

	m_ui->lineEditScaleX->installEventFilter(this);
	m_ui->lineEditScaleY->installEventFilter(this);
	m_ui->lineEditScaleZ->installEventFilter(this);

	// m_ui->lineEditScaleFactor->installEventFilter(this);

	m_ui->lineEditCopyX->setText( QString("%L1").arg(m_copyTranslationVector.m_x,0,'f',3));
	m_ui->lineEditCopyY->setText( QString("%L1").arg(m_copyTranslationVector.m_y,0,'f',3));
	m_ui->lineEditCopyZ->setText( QString("%L1").arg(m_copyTranslationVector.m_z,0,'f',3));

	m_ui->lineEditCopyX->setFormatter(new LineEditFormater);
	m_ui->lineEditCopyY->setFormatter(new LineEditFormater);
	m_ui->lineEditCopyZ->setFormatter(new LineEditFormater);

	connect(m_ui->lineEditCopyX, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditCopyY, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditCopyZ, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);

	connect(m_ui->lineEditRotateInclination, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditRotateOrientation, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);

	connect(m_ui->lineEditRotateX, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditRotateY, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditRotateZ, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);

	connect(m_ui->lineEditRotateXTrimming, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditRotateYTrimming, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditRotateZTrimming, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);

	connect(m_ui->lineEditRotateXTrimming, &QLineEdit::editingFinished, this, &SVPropEditGeometry::onTrimmingRotationFinished);
	connect(m_ui->lineEditRotateYTrimming, &QLineEdit::editingFinished, this, &SVPropEditGeometry::onTrimmingRotationFinished);
	connect(m_ui->lineEditRotateZTrimming, &QLineEdit::editingFinished, this, &SVPropEditGeometry::onTrimmingRotationFinished);

	connect(m_ui->lineEditTranslateTrimmingX, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditTranslateTrimmingY, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditTranslateTrimmingZ, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);

	connect(m_ui->lineEditScaleX, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditScaleY, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditScaleZ, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	// connect(m_ui->lineEditScaleFactor, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);

	connect(m_ui->lineEditTranslateX, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditTranslateY, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditTranslateZ, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);

	m_ui->pushButtonApply->hide();
	m_ui->pushButtonCancel->hide();
}


SVPropEditGeometry::~SVPropEditGeometry() {
	delete m_ui;
}


void SVPropEditGeometry::enableTransformation() {
	m_ui->pushButtonApply->setEnabled(true);
	m_ui->pushButtonCancel->setEnabled(true);
}


void SVPropEditGeometry::setModificationType(ModificationType modType) {
	m_ui->stackedWidget->setCurrentIndex(modType);
	updateInputs(); // update all inputs
	// adjust size
	QSize preferredSize = m_ui->stackedWidget->currentWidget()->sizeHint();
	m_ui->stackedWidget->setFixedHeight(preferredSize.height());
	// only adjust local coordinate system, if this widget is visible
	if (this->isVisibleTo(qobject_cast<QWidget*>(parent())) ) {
		// Note: setting new coordinates to the local coordinate system object will in turn call setCoordinates()
		//       and indirectly also updateInputs()
		updateCoordinateSystemLook();
		//		updateTrimmingPlane();
		adjustLocalCoordinateSystemForRotateToAngle();
	}

	SVViewStateHandler::instance().m_trimmingObject->m_trimmingPlaneVisible = modType == MT_Trim;
}


void SVPropEditGeometry::setCoordinates(const Vic3D::Transform3D &t) {
	Vic3D::CoordinateSystemObject *cso = SVViewStateHandler::instance().m_coordinateSystemObject;

	// is being called from local coordinate system object, whenever this has changed location (regardless of
	// its own visibility)
	m_lcsTransform =  t;

	// compute dimensions of bounding box (dx, dy, dz) and center point of all selected surfaces
	m_bbDim[OM_Local] = project().boundingBox(m_selDrawings, m_selSurfaces, m_selSubSurfaces,
											  m_selEdges, m_selNodes,
											  m_bbCenter[OM_Local],
											  QVector2IBKVector(cso->translation() ),
											  QVector2IBKVector(cso->localXAxis() ),
											  QVector2IBKVector(cso->localYAxis() ),
											  QVector2IBKVector(cso->localZAxis() ) );

	m_bbDim[OM_Global] = project().boundingBox(m_selDrawings, m_selSurfaces, m_selSubSurfaces,
											   m_selEdges, m_selNodes, m_bbCenter[OM_Global]);

	m_normal = QVector2IBKVector(cso->localZAxis());
	updateInputs();
}


bool SVPropEditGeometry::handleGlobalKeyPress(Qt::Key k) {
	switch (k) {
	case Qt::Key_Escape :
		if (!m_ui->pushButtonCancel->isEnabled())
			return false;
		m_ui->pushButtonCancel->click();
		break;

	default:
		return false;
	}
	return true;
}

void SVPropEditGeometry::finishTransformation() {
	on_pushButtonApply_clicked();
}

// *** PUBLIC SLOTS ***

void SVPropEditGeometry::onModified(int modificationType, ModificationInfo * ) {
	SVProjectHandler::ModificationTypes modType((SVProjectHandler::ModificationTypes)modificationType);
	switch (modType) {
	case SVProjectHandler::AllModified:
		updateUi();
		break;
	case SVProjectHandler::BuildingGeometryChanged:
		// When the building geometry has changed, we need to update the geometrical info
		// in the widget based on the current selection. LCS is not moved.
		updateUi(false);
		break;
	case SVProjectHandler::NodeStateModified:
		updateUi();
		break;

	default: ; // just to make compiler happy
	}
}


void SVPropEditGeometry::onViewStateChanged() {
	const SVViewState & vs = SVViewStateHandler::instance().viewState();
	if (vs.m_sceneOperationMode == SVViewState::NUM_OM) {
		SVViewStateHandler::instance().m_selectedGeometryObject->resetTransformation();
	}
	else if (vs.m_sceneOperationMode == SVViewState::OM_TrimObjects) {
		const QVector3D &trans = SVViewStateHandler::instance().m_coordinateSystemObject->translation();
		updateTrimmingPlane(QVector2IBKVector(trans));
	}
}

void SVPropEditGeometry::onLineEditTextEdited(const QString) {

	// We get our sender object
	QObject* obj = sender();

	// object should be always a line edit
	QtExt::ValidatingLineEdit *edit = dynamic_cast<QtExt::ValidatingLineEdit *>(obj);

	// Assert that object is a validating line edit
	Q_ASSERT(edit != nullptr);

	// Update all transformations.
	onLineEditTextChanged(edit);
}


void SVPropEditGeometry::onTrimmingRotationFinished() {
	updateTrimGridRotationPreview(true);

	/*! Set values back. */
	m_ui->lineEditRotateXTrimming->blockSignals(true);
	m_ui->lineEditRotateYTrimming->blockSignals(true);
	m_ui->lineEditRotateZTrimming->blockSignals(true);

	m_ui->lineEditRotateXTrimming->setValue(0);
	m_ui->lineEditRotateYTrimming->setValue(0);
	m_ui->lineEditRotateZTrimming->setValue(0);

	m_ui->lineEditRotateXTrimming->blockSignals(false);
	m_ui->lineEditRotateYTrimming->blockSignals(false);
	m_ui->lineEditRotateZTrimming->blockSignals(false);
}


// *** PROTECTED FUNCTIONS ***

bool SVPropEditGeometry::eventFilter(QObject * target, QEvent * event) {

	//	qDebug() << "Event type: " << event->type();
	QLineEdit *lineEdit = dynamic_cast<QLineEdit *>(target);
	if (event->type() == QEvent::Leave)
		qDebug() << "Object: " << target->objectName() << " Event: " << event->type();

	if ( event->type() == QEvent::Wheel ) {

		// We have both types in trimming
		bool isTrimmingTranslation = target == m_ui->lineEditTranslateTrimmingX ||
				target == m_ui->lineEditTranslateTrimmingY ||
				target == m_ui->lineEditTranslateTrimmingZ;

		// we listen to scroll wheel turns only for some line edits
		if (target == m_ui->lineEditTranslateX ||
				target == m_ui->lineEditTranslateY ||
				target == m_ui->lineEditTranslateZ ||
				target == m_ui->lineEditRotateInclination ||
				target == m_ui->lineEditRotateOrientation ||
				target == m_ui->lineEditRotateX ||
				target == m_ui->lineEditRotateY ||
				target == m_ui->lineEditRotateZ ||
				target == m_ui->lineEditRotateXTrimming ||
				target == m_ui->lineEditRotateYTrimming ||
				target == m_ui->lineEditRotateZTrimming ||
				target == m_ui->lineEditTranslateTrimmingX ||
				target == m_ui->lineEditTranslateTrimmingY ||
				target == m_ui->lineEditTranslateTrimmingZ ||
				target == m_ui->lineEditScaleX ||
				target == m_ui->lineEditScaleY ||
				target == m_ui->lineEditScaleZ ||
				target == m_ui->lineEditCopyX ||
				target == m_ui->lineEditCopyY ||
				target == m_ui->lineEditCopyZ )
		{
			double delta = 0.1; // default
			switch (m_ui->stackedWidget->currentIndex()) {
			case MT_Translate				:
			case MT_Scale					: delta = 0.01; break;
			case MT_Trim					: delta = isTrimmingTranslation ? 0.1 : 1.0; break;
			case MT_Rotate					: delta = 1; break;
			case NUM_MT : ; // just to make compiler happy
			}

			QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
			// offset are changed in 0.01 steps
			double offset = (wheelEvent->angleDelta().y()>0) ? delta : -delta;
			onWheelTurned(offset, qobject_cast<QtExt::ValidatingLineEdit*>(target)); // we know that target points to a ValidatingLineEdit
		}
	}
	else if ( lineEdit != nullptr && event->type() == QEvent::Leave ) {
		// ToDo Stephan: Find out if something really changed!
		//				 Prevent calling of undo-action calling all the time
		bool ok;
		double val = lineEdit->text().toDouble(&ok);
		if (!ok)
			return false;

		if (m_cachedValues.find(lineEdit) != m_cachedValues.end()) {
			double oldVal = m_cachedValues[lineEdit];
			if (oldVal == val)
				return false;
		}

		for (QLineEdit *lEdit : m_ui->stackedWidget->findChildren<QLineEdit*>()) {
			double valNew = lEdit->text().toDouble(&ok);
			if (!ok)
				continue;

			m_cachedValues[lEdit] = valNew;
		}

		if (m_ui->stackedWidget->currentIndex() == MT_Trim)
			onTrimmingRotationFinished();
		else
			on_pushButtonApply_clicked();

		return false;
	}

	return false;
}

void SVPropEditGeometry::focusOutEvent(QFocusEvent *event) {
	if (m_ui->stackedWidget->currentIndex() == MT_Trim)
		onTrimmingRotationFinished();
	// Let the rest happen ;)
	QWidget::focusOutEvent(event);
}

// *** PRIVATE SLOTS ***

void SVPropEditGeometry::on_radioButtonTranslationAbsolute_toggled(bool) {
	updateInputs();
}

void SVPropEditGeometry::on_radioButtonTranslationRelative_toggled(bool) {
	updateInputs();
}

void SVPropEditGeometry::on_radioButtonTranslationRelativeLCS_toggled(bool) {
	updateInputs();
}


void SVPropEditGeometry::on_lineEditTranslateX_editingFinishedSuccessfully() {
	updateTranslationPreview();
}

void SVPropEditGeometry::on_lineEditTranslateY_editingFinishedSuccessfully() {
	updateTranslationPreview();
}

void SVPropEditGeometry::on_lineEditTranslateZ_editingFinishedSuccessfully() {
	updateTranslationPreview();
}



void SVPropEditGeometry::on_radioButtonRotationAlignToAngles_toggled(bool) {
	updateInputs();
	adjustLocalCoordinateSystemForRotateToAngle();
}

void SVPropEditGeometry::on_lineEditRotateOrientation_editingFinishedSuccessfully() {
	updateRotationPreview();
}

void SVPropEditGeometry::on_lineEditRotateInclination_editingFinishedSuccessfully() {
	updateRotationPreview();
}

void SVPropEditGeometry::on_lineEditRotateX_editingFinishedSuccessfully() {
	m_ui->lineEditRotateY->setValue(0);
	m_ui->lineEditRotateZ->setValue(0);
	updateRotationPreview();
}

void SVPropEditGeometry::on_lineEditRotateY_editingFinishedSuccessfully() {
	m_ui->lineEditRotateX->setValue(0);
	m_ui->lineEditRotateZ->setValue(0);
	updateRotationPreview();
}

void SVPropEditGeometry::on_lineEditRotateZ_editingFinishedSuccessfully() {
	m_ui->lineEditRotateX->setValue(0);
	m_ui->lineEditRotateY->setValue(0);
	updateRotationPreview();
}

void SVPropEditGeometry::on_lineEditRotateXTrimming_editingFinishedSuccessfully() {
	m_ui->lineEditRotateYTrimming->setValue(0);
	m_ui->lineEditRotateZTrimming->setValue(0);
	updateTrimGridRotationPreview();
}


void SVPropEditGeometry::on_lineEditRotateYTrimming_editingFinishedSuccessfully() {
	m_ui->lineEditRotateXTrimming->setValue(0);
	m_ui->lineEditRotateZTrimming->setValue(0);
	updateTrimGridRotationPreview();
}


void SVPropEditGeometry::on_lineEditRotateZTrimming_editingFinishedSuccessfully() {
	m_ui->lineEditRotateYTrimming->setValue(0);
	m_ui->lineEditRotateXTrimming->setValue(0);
	updateTrimGridRotationPreview();
}

void SVPropEditGeometry::on_lineEditTranslateTrimmingX_editingFinishedSuccessfully() {
	double newX = m_ui->lineEditTranslateTrimmingX->value();
	double newY = m_ui->lineEditTranslateTrimmingY->value();
	double newZ = m_ui->lineEditTranslateTrimmingZ->value();
	IBKMK::Vector3D translation ((float)newX, (float)newY, (float)newZ);

	updateTrimmingPlane(translation);
}


void SVPropEditGeometry::on_lineEditTranslateTrimmingY_editingFinishedSuccessfully() {
	double newX = m_ui->lineEditTranslateTrimmingX->value();
	double newY = m_ui->lineEditTranslateTrimmingY->value();
	double newZ = m_ui->lineEditTranslateTrimmingZ->value();
	IBKMK::Vector3D translation ((float)newX, (float)newY, (float)newZ);

	updateTrimmingPlane(translation);
}


void SVPropEditGeometry::on_lineEditTranslateTrimmingZ_editingFinishedSuccessfully() {
	double newX = m_ui->lineEditTranslateTrimmingX->value();
	double newY = m_ui->lineEditTranslateTrimmingY->value();
	double newZ = m_ui->lineEditTranslateTrimmingZ->value();
	IBKMK::Vector3D translation ((float)newX, (float)newY, (float)newZ);

	updateTrimmingPlane(translation);
}

void SVPropEditGeometry::on_pushButtonThreePointRotation_clicked() {
	// when clicked, we set the scene into three-point-rotation mode
	// TODO Stephan
}


void SVPropEditGeometry::on_checkBoxKeepAspectRatio_toggled(bool checked) {
	if (checked) {
		// TODO : act like we have entered just a value in x
	}
}

void SVPropEditGeometry::on_radioButtonScaleResize_toggled(bool) {
	updateInputs();
}

void SVPropEditGeometry::on_lineEditScaleX_editingFinishedSuccessfully() {
	// if we have "aspect ratio" on, we need to adjust the sizes of the other line edits as well
	if (m_ui->checkBoxKeepAspectRatio->isChecked())
		updateScalePreview(0);
	else
		updateScalePreview(-1);
}

void SVPropEditGeometry::on_lineEditScaleY_editingFinishedSuccessfully() {
	if (m_ui->checkBoxKeepAspectRatio->isChecked())
		updateScalePreview(1);
	else
		updateScalePreview(-1);
}

void SVPropEditGeometry::on_lineEditScaleZ_editingFinishedSuccessfully() {
	if (m_ui->checkBoxKeepAspectRatio->isChecked())
		updateScalePreview(2);
	else
		updateScalePreview(-1);
}


void SVPropEditGeometry::on_pushButtonCenterHorizontally_clicked() {
	QMessageBox::critical(this, QString(), tr("Not implemented, yet."));
}


void SVPropEditGeometry::on_pushButtonCenterVertically_clicked() {
	QMessageBox::critical(this, QString(), tr("Not implemented, yet."));
}


void SVPropEditGeometry::on_pushButtonFlipNormals_clicked() {
	// process all selected surfaces (not subsurfaces) and flip their normal vectors
	// this is done directly, without use of apply/cancel buttons
	std::vector<VICUS::Surface>			modifiedSurfaces;
	std::vector<VICUS::Drawing>			modifiedDrawings;
	for (const VICUS::Surface* s : m_selSurfaces) {
		// create a copy of the surface
		VICUS::Surface modS(*s);
		modS.flip();
		modifiedSurfaces.push_back(modS);
	}
	// in case operation was executed without any selected objects - should be prevented
	if (modifiedSurfaces.empty())
		return;

	SVUndoModifySurfaceGeometry * undo = new SVUndoModifySurfaceGeometry(tr("Surface normal flipped"), modifiedSurfaces, modifiedDrawings );
	undo->push();

	// also disable apply and cancel buttons
	m_ui->pushButtonApply->setEnabled(false);
	m_ui->pushButtonCancel->setEnabled(false);
	SVViewStateHandler::instance().m_selectedGeometryObject->resetTransformation();
	// and update our inputs again
	updateUi();
}


void SVPropEditGeometry::on_lineEditCopyX_editingFinishedSuccessfully() {
	m_copyTranslationVector.m_x = m_ui->lineEditCopyX->value();
}

void SVPropEditGeometry::on_lineEditCopyY_editingFinishedSuccessfully() {
	m_copyTranslationVector.m_y = m_ui->lineEditCopyY->value();
}

void SVPropEditGeometry::on_lineEditCopyZ_editingFinishedSuccessfully() {
	m_copyTranslationVector.m_z = m_ui->lineEditCopyZ->value();
}



// *** PRIVATE FUNCTIONS ***

void SVPropEditGeometry::updateUi(bool resetLCS) {
	Vic3D::CoordinateSystemObject *cso = SVViewStateHandler::instance().m_coordinateSystemObject;
	Q_ASSERT(cso != nullptr);

	// update our selection lists
	std::set<const VICUS::Object*> sel;

	// first we get how many surfaces are selected
	project().selectObjects(sel, VICUS::Project::SG_All, false, false);

	// we also have to cache all existing names, so we take alle existing objects
	m_selEdges.clear();
	m_selNodes.clear();
	m_selDrawings.clear();
	m_selSurfaces.clear();
	m_selRooms.clear();
	m_selSubSurfaces.clear();
	m_selBuildings.clear();
	m_selBuildingLevels.clear();

	m_subSurfNames.clear();
	m_surfNames.clear();
	m_buildingNames.clear();
	m_buildingLevelNames.clear();

	// process all selected objects and sort them into vectors
	for (const VICUS::Object * o : sel) {
		const VICUS::Surface * s = dynamic_cast<const VICUS::Surface *>(o);
		if (s != nullptr ) {
			m_surfNames.insert(s->m_displayName );
			if (s->m_selected && s->m_visible)
				m_selSurfaces.push_back(s);
		}
		const VICUS::Room * r = dynamic_cast<const VICUS::Room *>(o);
		if (r != nullptr ) {
			m_roomNames.insert(r->m_displayName );
			if (r->m_selected && r->m_visible)
				m_selRooms.push_back(r);
		}
		const VICUS::SubSurface * sub = dynamic_cast<const VICUS::SubSurface *>(o);
		if (sub != nullptr ) {
			m_subSurfNames.insert(sub->m_displayName );
			if (sub->m_selected && sub->m_visible)
				m_selSubSurfaces.push_back(sub);
		}
		const VICUS::BuildingLevel * bl = dynamic_cast<const VICUS::BuildingLevel *>(o);
		if (bl != nullptr ) {
			m_buildingLevelNames.insert(bl->m_displayName );
			if (bl->m_selected && bl->m_visible)
				m_selBuildingLevels.push_back(bl);
		}
		const VICUS::Building * b = dynamic_cast<const VICUS::Building *>(o);
		if (b != nullptr ) {
			m_subSurfNames.insert(b->m_displayName );
			if (b->m_selected && b->m_visible)
				m_selBuildings.push_back(b);
		}

		const VICUS::Drawing * d = dynamic_cast<const VICUS::Drawing *>(o);
		if (d != nullptr) {
			if (d->m_selected && d->m_visible)
				m_selDrawings.push_back(d);
			//			for (const VICUS::Drawing::DrawingLayer &dl : d->m_layers) {
			//				if (dl.m_selected && dl.m_visible)
			//					m_selDrawings.push_back(d);
			//			}
		}

		const VICUS::NetworkNode * nn = dynamic_cast<const VICUS::NetworkNode *>(o);
		if (nn != nullptr) {
			if (nn->m_selected && nn->m_visible)
				m_selNodes.push_back(nn);
		}

		const VICUS::NetworkEdge * ne = dynamic_cast<const VICUS::NetworkEdge *>(o);
		if (ne != nullptr) {
			if (ne->m_selected && ne->m_visible)
				m_selEdges.push_back(ne);
		}
	}

	// compute dimensions of bounding box (dx, dy, dz) and center point of all selected surfaces
	m_bbDim[OM_Local] = project().boundingBox(m_selDrawings, m_selSurfaces, m_selSubSurfaces,
											  m_selEdges, m_selNodes, m_bbCenter[OM_Local],
											  QVector2IBKVector(cso->translation() ),
											  QVector2IBKVector(cso->localXAxis() ),
											  QVector2IBKVector(cso->localYAxis() ),
											  QVector2IBKVector(cso->localZAxis() ) );
	m_bbDim[OM_Global] = project().boundingBox(m_selDrawings, m_selSurfaces, m_selSubSurfaces,
											   m_selEdges, m_selNodes, m_bbCenter[OM_Global]);

	// NOTE: this function is being called even if edit geometry property widget is not
	SVViewStateHandler::instance().m_localCoordinateViewWidget->setBoundingBoxDimension(m_bbDim[OM_Global]);
	// position local coordinate system
	if(resetLCS)
		cso->setTranslation(IBKVector2QVector(m_bbCenter[OM_Global]) );

	// only adjust local coordinate system, if this widget is visible
	if (this->isVisibleTo(qobject_cast<QWidget*>(parent())) ) {
		// adjust local coordinate system based on selection
		adjustLocalCoordinateSystemForRotateToAngle();

		// Note: setting new coordinates to the local coordinate system object will in turn call setCoordinates()
		//       and indirectly also updateInputs()
		updateCoordinateSystemLook();
	}

	// enable buttons based on selections
	m_ui->pushButtonCopySurface->setEnabled(!m_selSurfaces.empty());
	m_ui->pushButtonCopySubsurface->setEnabled(!m_selSubSurfaces.empty());
	m_ui->pushButtonCopyRoom->setEnabled(!m_selRooms.empty());
	m_ui->pushButtonCopyBuildingLevel->setEnabled(!m_selBuildingLevels.empty());
	m_ui->pushButtonCopyBuilding->setEnabled(!m_selBuildings.empty());

	bool noSelection = m_selDrawings.empty() && m_selSurfaces.empty() && m_selSubSurfaces.empty() &&
			m_selRooms.empty() && m_selBuildingLevels.empty() && m_selBuildings.empty();

	setEnabled(!noSelection);

	//	if (m_selDrawings.size() == 1)
	//		m_ui->lineEditScaleFactor->setValue(m_selDrawings.back()->m_scalingFactor);
	//	else
	//		m_ui->lineEditScaleFactor->setValue(1.0);

	updateInputs();
}


void SVPropEditGeometry::updateTranslationPreview() {
	double newX = m_ui->lineEditTranslateX->value();
	double newY = m_ui->lineEditTranslateY->value();
	double newZ = m_ui->lineEditTranslateZ->value();
	QVector3D translation = QVector3D((float)newX, (float)newY, (float)newZ);
	if (m_ui->radioButtonTranslationAbsolute->isChecked()) {
		// obtain new absolute position of local coordinate system
		// subtract original lcs position
		// obtain offset and rotation of local coordinate system
		QVector3D offset = m_lcsTransform.translation();
		// apply offset using global coordinate system
		translation -= offset;
	}
	else if (m_ui->radioButtonTranslationRelativeLCS->isChecked()) {
		// rotate translation vector with current LCS transformation matrix
		translation = m_lcsTransform.rotation().rotatedVector(translation);
	}

	// adjust wireframe object transform
	SVViewStateHandler::instance().m_selectedGeometryObject->translate(translation);
	const_cast<Vic3D::SceneView*>(SVViewStateHandler::instance().m_geometryView->sceneView())->renderLater();

	// also enable the apply/cancel buttons
	enableTransformation();
}


void SVPropEditGeometry::updateRotationPreview() {

	Vic3D::Transform3D rot;
	if (m_ui->radioButtonRotationAlignToAngles->isChecked()) {
		// get the rotation angles in [Rad]
		double oriDeg = m_ui->lineEditRotateOrientation->value();
		// inclination is 90-inc...
		double incliRad = (90-m_ui->lineEditRotateInclination->value()) * IBK::DEG2RAD;
		double oldOrientationDeg = std::atan2(m_normal.m_x, ( m_normal.m_y == 0. ? 1E-8 : m_normal.m_y ) ) / IBK::DEG2RAD;
		if (oldOrientationDeg < 0)
			oldOrientationDeg += 360;
		//		qDebug() << "Old orientation deg = " << oldOrientationDeg;
		//		qDebug() << "New orientation deg = " << oriDeg;
		//		qDebug() << "New 90-inclination deg = " << incliRad / IBK::DEG2RAD;

		// we need to do two different rotations, one along the same orientation, but to different
		// inclination - hereby the rotation axis is computed from old normal vector and new normal vector
		// and

		IBKMK::Vector3D newNormal(	std::sin( oldOrientationDeg * IBK::DEG2RAD) * std::cos( incliRad ),
									std::cos( oldOrientationDeg * IBK::DEG2RAD) * std::cos( incliRad ),
									std::sin( incliRad ) );

		QQuaternion rotationInc;

		// we only want to rotate if the normal vectors are not the same - in this case we may not be able
		// to compute the rotation axis
		if (m_normal != newNormal) {

			// we find the rotation axis by taking the cross product of the normal vector and the normal vector we want to
			// rotate to
			IBKMK::Vector3D rotationAxis ( m_normal.crossProduct(newNormal).normalized() );
			//		qDebug() << "Rotation axis: " << rotationAxis.m_x << "\t" << rotationAxis.m_y << "\t" << rotationAxis.m_z;

			// we now also have to find the angle between both normals

			double angle = angleBetweenVectorsDeg(m_normal, newNormal);

			rotationInc = QQuaternion::fromAxisAndAngle(IBKVector2QVector(rotationAxis), (float)angle);
			//		qDebug() << "Roation angle: " << angle << " °";
		}

		QQuaternion rotationOrientation;

		// we only rotate around global z if angles differ
		if (!IBK::near_equal(oriDeg, oldOrientationDeg, 1e-4)) {
			rotationOrientation = QQuaternion::fromAxisAndAngle(QVector3D(0,0,1), (float)(oriDeg - oldOrientationDeg));
		}
		rot.setRotation(rotationOrientation*rotationInc);

	}
	else {
		Vic3D::CoordinateSystemObject *cso = SVViewStateHandler::instance().m_coordinateSystemObject;
		Q_ASSERT(cso != nullptr);

		// only one of the inputs may have a value different from 0
		if (m_ui->lineEditRotateX->isValid() && m_ui->lineEditRotateX->value() != 0.)
			rot.setRotation((float)m_ui->lineEditRotateX->value(), cso->localXAxis());
		if (m_ui->lineEditRotateY->isValid() && m_ui->lineEditRotateY->value() != 0.)
			rot.setRotation((float)m_ui->lineEditRotateY->value(), cso->localYAxis());
		if (m_ui->lineEditRotateZ->isValid() && m_ui->lineEditRotateZ->value() != 0.)
			rot.setRotation((float)m_ui->lineEditRotateZ->value(), cso->localZAxis());
	}

	// adjust wireframe object transform
	// we need to compute the transformation so that new lcs offset point becomes the original point again
	QVector3D newLCSOrigin = rot.rotation().rotatedVector(m_lcsTransform.translation());
	QVector3D trans = m_lcsTransform.translation() - newLCSOrigin;

	SVViewStateHandler::instance().m_selectedGeometryObject->rotate(rot.rotation(), trans);
	const_cast<Vic3D::SceneView*>(SVViewStateHandler::instance().m_geometryView->sceneView())->renderLater();

	// also enable the apply/cancel buttons
	enableTransformation();
}

void SVPropEditGeometry::updateTrimGridRotationPreview(bool updateNormal) {

	Vic3D::CoordinateSystemObject *cso = SVViewStateHandler::instance().m_coordinateSystemObject;
	Q_ASSERT(cso != nullptr);

	Vic3D::TrimmingObject &to = *SVViewStateHandler::instance().m_trimmingObject;
	IBKMK::Vector3D normal = to.planeNormal();

	// only one of the inputs may have a value different from 0
	QMatrix4x4 trans;
	if (m_ui->lineEditRotateXTrimming->isValid() && m_ui->lineEditRotateXTrimming->value() != 0.)
		trans.rotate((float)m_ui->lineEditRotateXTrimming->value(), cso->localXAxis());
	if (m_ui->lineEditRotateYTrimming->isValid(	) && m_ui->lineEditRotateYTrimming->value() != 0.)
		trans.rotate((float)m_ui->lineEditRotateYTrimming->value(), cso->localYAxis());
	if (m_ui->lineEditRotateZTrimming->isValid() && m_ui->lineEditRotateZTrimming->value() != 0.)
		trans.rotate((float)m_ui->lineEditRotateZTrimming->value(), cso->localZAxis());

	normal = QVector2IBKVector(trans * IBKVector2QVector(normal));
	to.updateTrimmingPlane(normal);

	if (updateNormal)
		to.setTrimmingPlaneNormal(normal);

	const_cast<Vic3D::SceneView*>(SVViewStateHandler::instance().m_geometryView->sceneView())->renderLater();
}


void SVPropEditGeometry::updateScalePreview(int aspectRatioSourceEdit) {
	QVector3D scaleFactors;
	if (m_ui->radioButtonScaleResize->isChecked()) {
		// compute scale factors
		double newX = m_ui->lineEditScaleX->value();
		double newY = m_ui->lineEditScaleY->value();
		double newZ = m_ui->lineEditScaleZ->value();
		// Mind: dimension in x, y, z might be zero, for example, if only a single
		//       surface had been selected. In this case the scale factor must be always exactly 1
		//       regardless of the user input

		if (IBK::near_equal(m_bbDim[OM_Local].m_x,0.0,1e-6))			scaleFactors.setX(1);
		else															scaleFactors.setX(float(newX/m_bbDim[OM_Local].m_x));

		if (IBK::near_equal(m_bbDim[OM_Local].m_y,0.0,1e-6))			scaleFactors.setY(1);
		else															scaleFactors.setY(float(newY/m_bbDim[OM_Local].m_y));

		if (IBK::near_equal(m_bbDim[OM_Local].m_z,0.0,1e-6))			scaleFactors.setZ(1);
		else															scaleFactors.setZ(float(newZ/m_bbDim[OM_Local].m_z));

		switch (aspectRatioSourceEdit) {
		case 0 : {
			float scale = scaleFactors.x();
			scaleFactors.setY(scale);
			scaleFactors.setZ(scale);
			m_ui->lineEditScaleY->setValue((double)scale*m_bbDim[OM_Local].m_y);
			m_ui->lineEditScaleZ->setValue((double)scale*m_bbDim[OM_Local].m_z);
		} break;
		case 1 : {
			float scale = scaleFactors.y();
			scaleFactors.setX(scale);
			scaleFactors.setZ(scale);
			m_ui->lineEditScaleX->setValue((double)scale*m_bbDim[OM_Local].m_x);
			m_ui->lineEditScaleZ->setValue((double)scale*m_bbDim[OM_Local].m_z);
		} break;
		case 2 : {
			float scale = scaleFactors.z();
			scaleFactors.setX(scale);
			scaleFactors.setY(scale);
			m_ui->lineEditScaleX->setValue((double)scale*m_bbDim[OM_Local].m_x);
			m_ui->lineEditScaleY->setValue((double)scale*m_bbDim[OM_Local].m_y);
		} break;
		}
	}
	else {
		scaleFactors.setX( (float)m_ui->lineEditScaleX->value());
		scaleFactors.setY( (float)m_ui->lineEditScaleY->value());
		scaleFactors.setZ( (float)m_ui->lineEditScaleZ->value());
		switch (aspectRatioSourceEdit) {
		case 0 : {
			float scale = scaleFactors.x();
			scaleFactors.setY(scale);
			scaleFactors.setZ(scale);
			m_ui->lineEditScaleY->setValue((double)scale);
			m_ui->lineEditScaleZ->setValue((double)scale);
		} break;
		case 1 : {
			float scale = scaleFactors.y();
			scaleFactors.setX(scale);
			scaleFactors.setZ(scale);
			m_ui->lineEditScaleX->setValue((double)scale);
			m_ui->lineEditScaleZ->setValue((double)scale);
		} break;
		case 2 : {
			float scale = scaleFactors.z();
			scaleFactors.setX(scale);
			scaleFactors.setY(scale);
			m_ui->lineEditScaleX->setValue((double)scale);
			m_ui->lineEditScaleY->setValue((double)scale);
		} break;
		}
	}
	// obtain offset and rotation of local coordinate system
	QVector3D offset = m_lcsTransform.translation();
	QQuaternion rot = m_lcsTransform.rotation();

	// adjust wireframe object transform
	SVViewStateHandler::instance().m_selectedGeometryObject->localScaling(offset, rot, scaleFactors);
	const_cast<Vic3D::SceneView*>(SVViewStateHandler::instance().m_geometryView->sceneView())->renderLater();

	// also enable the apply/cancel buttons
	enableTransformation();
}


void SVPropEditGeometry::onWheelTurned(double offset, QtExt::ValidatingLineEdit * lineEdit) {
	if (!lineEdit->isValid())
		return; // invalid input, do nothing
	double val = lineEdit->value();
	val += offset;
	lineEdit->setValue(val); // this does not trigger any signals, so we need to send change info manually
	onLineEditTextChanged(lineEdit);
}


void SVPropEditGeometry::onLineEditTextChanged(QtExt::ValidatingLineEdit * lineEdit) {
	// not valid? don't send a signal
	if (!lineEdit->isValid())
		return;

	if (lineEdit == m_ui->lineEditTranslateX)
		on_lineEditTranslateX_editingFinishedSuccessfully();
	else if (lineEdit == m_ui->lineEditTranslateY)
		on_lineEditTranslateY_editingFinishedSuccessfully();
	else if (lineEdit == m_ui->lineEditTranslateZ)
		on_lineEditTranslateZ_editingFinishedSuccessfully();
	else if (lineEdit == m_ui->lineEditRotateOrientation)
		on_lineEditRotateOrientation_editingFinishedSuccessfully();
	else if (lineEdit == m_ui->lineEditRotateInclination)
		on_lineEditRotateInclination_editingFinishedSuccessfully();
	else if (lineEdit == m_ui->lineEditRotateX)
		on_lineEditRotateX_editingFinishedSuccessfully();
	else if (lineEdit == m_ui->lineEditRotateY)
		on_lineEditRotateY_editingFinishedSuccessfully();
	else if (lineEdit == m_ui->lineEditRotateZ)
		on_lineEditRotateZ_editingFinishedSuccessfully();
	else if (lineEdit == m_ui->lineEditScaleX)
		on_lineEditScaleX_editingFinishedSuccessfully();
	else if (lineEdit == m_ui->lineEditScaleY)
		on_lineEditScaleY_editingFinishedSuccessfully();
	else if (lineEdit == m_ui->lineEditScaleZ)
		on_lineEditScaleZ_editingFinishedSuccessfully();
	else if (lineEdit == m_ui->lineEditRotateXTrimming)
		on_lineEditRotateXTrimming_editingFinishedSuccessfully();
	else if (lineEdit == m_ui->lineEditRotateYTrimming)
		on_lineEditRotateYTrimming_editingFinishedSuccessfully();
	else if (lineEdit == m_ui->lineEditRotateZTrimming)
		on_lineEditRotateZTrimming_editingFinishedSuccessfully();
	else if (lineEdit == m_ui->lineEditTranslateTrimmingX)
		on_lineEditTranslateTrimmingX_editingFinishedSuccessfully();
	else if (lineEdit == m_ui->lineEditTranslateTrimmingY)
		on_lineEditTranslateTrimmingY_editingFinishedSuccessfully();
	else if (lineEdit == m_ui->lineEditTranslateTrimmingZ)
		on_lineEditTranslateTrimmingZ_editingFinishedSuccessfully();
}


void SVPropEditGeometry::updateInputs() {
	switch (m_ui->stackedWidget->currentIndex()) {

	// *** Translation page ***
	case MT_Translate : {
		if (m_ui->radioButtonTranslationAbsolute->isChecked()) {

			m_ui->labelTranslateX->setText("X [m]:");
			m_ui->labelTranslateY->setText("Y [m]:");
			m_ui->labelTranslateZ->setText("Z [m]:");

			// cache current local coordinate systems position as fall-back values
			m_originalValues = QVector2IBKVector(m_lcsTransform.translation());
		}
		else {
			m_ui->labelTranslateX->setText("ΔX [m]:");
			m_ui->labelTranslateY->setText("ΔY [m]:");
			m_ui->labelTranslateZ->setText("ΔZ [m]:");

			m_originalValues.set(0,0,0);
		}
		m_ui->lineEditTranslateX->setValue( m_originalValues.m_x );
		m_ui->lineEditTranslateY->setValue( m_originalValues.m_y );
		m_ui->lineEditTranslateZ->setValue( m_originalValues.m_z );
	} break;


	case MT_Rotate: {
		bool align2Angles = m_ui->radioButtonRotationAlignToAngles->isChecked();
		m_ui->labelRotateInclinationAbs->setEnabled(align2Angles);
		m_ui->labelRotateOrientationAbs->setEnabled(align2Angles);
		m_ui->labelRotationX->setEnabled(!align2Angles);
		m_ui->labelRotationY->setEnabled(!align2Angles);
		m_ui->labelRotationZ->setEnabled(!align2Angles);
		m_ui->lineEditRotateInclination->setEnabled(align2Angles);
		m_ui->lineEditRotateOrientation->setEnabled(align2Angles);
		m_ui->lineEditRotateX->setEnabled(!align2Angles);
		m_ui->lineEditRotateY->setEnabled(!align2Angles);
		m_ui->lineEditRotateZ->setEnabled(!align2Angles);

		m_ui->lineEditRotateX->setValue(0);
		m_ui->lineEditRotateY->setValue(0);
		m_ui->lineEditRotateZ->setValue(0);

		if (align2Angles) {
			m_ui->lineEditRotateInclination->setText( QString("%L1").arg(std::acos(m_normal.m_z)/IBK::DEG2RAD, 0, 'f', 3) );
			// positive y Richtung = Norden = Orientation 0°
			// positive x Richtung = Osten = Orientation 90°

			double orientation = std::atan2(m_normal.m_x, ( m_normal.m_y == 0. ? 1E-8 : m_normal.m_y ) ) /IBK::DEG2RAD ;
			m_ui->lineEditRotateOrientation->setText( QString("%L1").arg(orientation < 0 ? ( orientation + 360 ) : orientation, 0, 'f', 3 ) );
		}
		else {
			m_ui->lineEditRotateInclination->setValue(0);
			m_ui->lineEditRotateOrientation->setValue(0);
		}

	} break;

	case MT_Scale: {

		if (m_ui->radioButtonScaleResize->isChecked()) {
			m_ui->labelScaleX->setText("L<sub>X</sub> [m]:");
			m_ui->labelScaleY->setText("W<sub>Y</sub> [m]:");
			m_ui->labelScaleZ->setText("H<sub>Z</sub> [m]:");

			// always local bounding box
			m_originalValues = m_bbDim[OM_Local];

			m_ui->lineEditScaleX->setEnabled(!IBK::near_equal(m_bbDim[OM_Local].m_x,0.0,1e-6));
			m_ui->lineEditScaleY->setEnabled(!IBK::near_equal(m_bbDim[OM_Local].m_y,0.0,1e-6));
			m_ui->lineEditScaleZ->setEnabled(!IBK::near_equal(m_bbDim[OM_Local].m_z,0.0,1e-6));

		}
		else {
			m_ui->labelScaleX->setText("s<sub>X</sub>:");
			m_ui->labelScaleY->setText("s<sub>Y</sub>:");
			m_ui->labelScaleZ->setText("s<sub>Z</sub>:");

			m_originalValues = IBKMK::Vector3D( 1,1,1 );

			m_ui->lineEditScaleX->setEnabled(true);
			m_ui->lineEditScaleY->setEnabled(true);
			m_ui->lineEditScaleZ->setEnabled(true);
		}
		m_ui->lineEditScaleX->setValue(m_originalValues.m_x );
		m_ui->lineEditScaleY->setValue(m_originalValues.m_y );
		m_ui->lineEditScaleZ->setValue(m_originalValues.m_z );
	} break;

	case MT_Copy: {
		// Nothing for now?
	} break;

		// *** TRIMMING ***
	case MT_Trim: {
		m_originalValues = QVector2IBKVector(m_lcsTransform.translation());
		m_ui->lineEditTranslateTrimmingX->setValue( m_originalValues.m_x );
		m_ui->lineEditTranslateTrimmingY->setValue( m_originalValues.m_y );
		m_ui->lineEditTranslateTrimmingZ->setValue( m_originalValues.m_z );
	} break;

	} // switch modification type

	// reset wireframe transform
	SVViewStateHandler::instance().m_selectedGeometryObject->resetTransformation();
	const_cast<Vic3D::SceneView*>(SVViewStateHandler::instance().m_geometryView->sceneView())->renderLater();

	// disable apply and cancel buttons
	m_ui->pushButtonApply->setEnabled(false);
	m_ui->pushButtonCancel->setEnabled(false);
}


void SVPropEditGeometry::adjustLocalCoordinateSystemForRotateToAngle() {
	if (!this->isVisibleTo(qobject_cast<QWidget*>(parent())) )
		return;
	// special handling when rotation mode with "orient to angle" is selected
	if (m_ui->stackedWidget->currentIndex() == MT_Rotate &&
			m_ui->radioButtonRotationAlignToAngles->isChecked() &&
			!m_selSurfaces.empty())
	{
		// check all selected surfaces and obtain their orientation/inclination
		IBKMK::Vector3D normal;
		bool allTheSame = true;
		for (const VICUS::Surface* surf : m_selSurfaces) {
			if (normal.magnitudeSquared() == 0.0)
				normal = surf->geometry().normal();
			else {
				if (normal != surf->geometry().normal()) {
					allTheSame = false;
					break;
				}
			}
		}
		// all surfaces have same orientation/inclinatin - set this in the local coordinate system object
		if (allTheSame) {
			Vic3D::CoordinateSystemObject *cso = SVViewStateHandler::instance().m_coordinateSystemObject;
			const VICUS::PlaneGeometry & geo = m_selSurfaces.front()->geometry();
			QQuaternion q2 = QQuaternion::fromAxes(IBKVector2QVector(geo.localX().normalized()),
												   IBKVector2QVector(geo.localY().normalized()),
												   IBKVector2QVector(geo.normal().normalized()));
			cso->setRotation(q2);
			m_normal = geo.normal();
			// also update line edits
			updateInputs();
		}
	}
}



void SVPropEditGeometry::updateCoordinateSystemLook() {
	Vic3D::CoordinateSystemObject *cso = SVViewStateHandler::instance().m_coordinateSystemObject;
	if (SVViewStateHandler::instance().m_geometryView == nullptr)
		return; // do nothing while initializing
	// adjust appearance of local coordinate system
	if (m_ui->stackedWidget->currentIndex() == MT_Align ||
			m_ui->stackedWidget->currentIndex() == MT_Copy) {
		// put local coordinate system back into "plain" mode
		if (cso->m_geometryTransformMode != 0) {
			cso->m_geometryTransformMode = 0;
			SVViewStateHandler::instance().m_geometryView->refreshSceneView();
		}
	}
	else {
		// put local coordinate system back into correct transform mode
		switch (m_ui->stackedWidget->currentIndex()) {
		case MT_Translate:
			if (cso->m_geometryTransformMode != Vic3D::CoordinateSystemObject::TM_Translate) {
				cso->m_geometryTransformMode = Vic3D::CoordinateSystemObject::TM_Translate;
				SVViewStateHandler::instance().m_geometryView->refreshSceneView();
			}
			break;

		case MT_Rotate:
			if (cso->m_geometryTransformMode != Vic3D::CoordinateSystemObject::TM_RotateMask) {
				cso->m_geometryTransformMode = Vic3D::CoordinateSystemObject::TM_RotateMask;
				SVViewStateHandler::instance().m_geometryView->refreshSceneView();
			}
			break;

		case MT_Scale:
			if (cso->m_geometryTransformMode != Vic3D::CoordinateSystemObject::TM_ScaleMask) {
				cso->m_geometryTransformMode = Vic3D::CoordinateSystemObject::TM_ScaleMask;
				SVViewStateHandler::instance().m_geometryView->refreshSceneView();
			}
			break;

		case MT_Trim:
			if (cso->m_geometryTransformMode != Vic3D::CoordinateSystemObject::TM_Trim) {
				cso->m_geometryTransformMode = Vic3D::CoordinateSystemObject::TM_Trim;
				SVViewStateHandler::instance().m_geometryView->refreshSceneView();
			}
			break;

		case NUM_MT : ; // just to make compiler happy
		}
	}
}

void SVPropEditGeometry::updateTrimmingPlane(const IBKMK::Vector3D &trans) {

	const VICUS::Project &prj = SVProjectHandler::instance().project();

	std::vector<const VICUS::Surface *> surfs;
	std::vector<const VICUS::SubSurface *> subSurfs;
	prj.selectedSurfaces(surfs, VICUS::Project::SG_All);
	prj.selectedSubSurfaces(subSurfs, VICUS::Project::SG_All);

	IBKMK::Vector3D center;
	std::vector<const VICUS::Drawing *> draws;
	std::vector<const VICUS::NetworkNode *> nodes;
	std::vector<const VICUS::NetworkEdge *> edges;
	IBKMK::Vector3D bb = prj.boundingBox(draws, surfs, subSurfs, edges, nodes, center);

	Vic3D::CoordinateSystemObject &cso = *SVViewStateHandler::instance().m_coordinateSystemObject;
	QVector3D q3dTrans = IBKVector2QVector(trans);
	if (q3dTrans != cso.translation())
		cso.setTranslation(q3dTrans);

	Vic3D::TrimmingObject &to = *SVViewStateHandler::instance().m_trimmingObject;
	to.setBoundingBoxDimension(center, bb);
	to.setTrimmingPlanePoint(trans);
	to.updateTrimmingPlane();

	SVViewStateHandler::instance().m_geometryView->refreshSceneView();
}


IBKMK::Vector3D SVPropEditGeometry::localCopyTranslationVector() const {
	QQuaternion q = SVViewStateHandler::instance().m_coordinateSystemObject->transform().rotation();
	IBKMK::Quaternion qm = QQuaternion2IBKQuaternion(q);
	IBKMK::Vector3D localCopyTranslationVector(m_copyTranslationVector);
	qm.rotateVector(localCopyTranslationVector);
	return localCopyTranslationVector;
}


void SVPropEditGeometry::on_pushButtonCancel_clicked() {
	// TODO
	// reset LCS when it had been moved as part of an interactive transformation, reset its original position
	// for now we just reset the LCS based on the current selection - but actually, the state before starting the transform
	// includes the (modified) location/orientation of the LCS _after_ the selection had been made
	//	SVViewStateHandler::instance().m_coordinateSystemObject->setTranslation(SVViewStateHandler::instance().m_coordinateSystemObject->m_originalTranslation);
	//	SVViewStateHandler::instance().m_coordinateSystemObject->setRotation(SVViewStateHandler::instance().m_coordinateSystemObject->m_originalRotation);
	SVViewStateHandler::instance().m_selectedGeometryObject->resetTransformation();
	// also disable apply and cancel buttons
	m_ui->pushButtonApply->setEnabled(false);
	m_ui->pushButtonCancel->setEnabled(false);
	// and update our inputs again
	updateUi(); // NOTE: this updates the position of the LCS again, but not its orientation!
	const_cast<Vic3D::SceneView*>(SVViewStateHandler::instance().m_geometryView->sceneView())->renderLater();
}


void SVPropEditGeometry::on_pushButtonApply_clicked() {
	FUNCID(SVPropEditGeometry::on_pushButtonApply_clicked);

	// retrieve current transformation from selection object
	QVector3D translation, scaling;
	QQuaternion rotation;
	SVViewStateHandler::instance().m_selectedGeometryObject->currentTransformation(translation, rotation, scaling);


	// distinguish operations
	// we have a local scaling operation, which we need to do in a special way
	bool haveScaling = (scaling != QVector3D(0,0,0));

	// compose vector of modified surface geometries
	std::vector<VICUS::Surface>			modifiedSurfaces;
	std::vector<VICUS::Drawing>			modifiedDrawings;
	std::set<const VICUS::Surface*>		handledSurfaces;

	// process all selected surfaces
	for (const VICUS::Surface* s : m_selSurfaces) {
		// create a copy of the surface
		VICUS::Surface modS(*s);
		IBKMK::Polygon3D origPoly = const_cast<IBKMK::Polygon3D&>(modS.polygon3D());
		handledSurfaces.insert(s);

		if (haveScaling) {
			// local scaling involves translation, rotation _and_ changes to the local polyome... hence we better work
			// on 3D polygon coordinates
			IBKMK::Polygon3D poly = modS.polygon3D();

			// get the transformation matrix
			QMatrix4x4 transMat = SVViewStateHandler::instance().m_selectedGeometryObject->transform().toMatrix();
			std::vector<IBKMK::Vector3D> verts = poly.vertexes();
			for (IBKMK::Vector3D & v : verts) {
				v = QVector2IBKVector( transMat*IBKVector2QVector(v) );
			}
			// reconstruct the polygon with new vertexes
			if (!poly.setVertexes(verts)) {
				IBK::IBK_Message("Error scaling polygon of surface.", IBK::MSG_WARNING, FUNC_ID);
				continue;
			}
			// now also scale all windows within the polygon
			// If the localX and localY vectors would not be normalized, we would already be finished.
			// But since we normalize the localX and localY vectors, we need to scale the local subsurface polygon coordinates

			// simplest way is to get the bounding box (in local coordinates) before the scaling and afterwards
			IBKMK::Vector2D lowerValuesOrig, upperValuesOrig;
			IBKMK::Vector2D lowerValuesNew, upperValuesNew;
			origPoly.polyline().boundingBox(lowerValuesOrig, upperValuesOrig);
			poly.polyline().boundingBox(lowerValuesNew, upperValuesNew);

			IBKMK::Vector2D diffOrig, diffNew;
			diffOrig = upperValuesOrig - lowerValuesOrig;
			diffNew =  upperValuesNew  - lowerValuesNew;

			IBK_ASSERT(std::fabs(diffOrig.m_x) > 1e-4);
			IBK_ASSERT(std::fabs(diffOrig.m_y) > 1e-4);
			double scaleX = diffNew.m_x/diffOrig.m_x;
			double scaleY = diffNew.m_y/diffOrig.m_y;

			std::vector<VICUS::SubSurface> modSubs = modS.subSurfaces();
			for (VICUS::SubSurface & sub : modSubs) {
				std::vector<IBKMK::Vector2D> polyVerts = sub.m_polygon2D.vertexes();
				for (unsigned int i=0; i<polyVerts.size(); ++i) {
					polyVerts[i].m_x *= scaleX;
					polyVerts[i].m_y *= scaleY;
				}
				// now set the new subsurface polygon
				sub.m_polygon2D.setVertexes(polyVerts);
			}
			//			for (VICUS::Surface & child : modChilds) {
			//				std::vector<IBKMK::Vector3D> verts = child.polygon3D().vertexes();
			//				for (IBKMK::Vector3D & v : verts) {
			//					v = QVector2IBKVector( transMat*IBKVector2QVector(v) );
			//				}
			//				// now set the new subsurface polygon
			//				const_cast<IBKMK::Polygon3D &>(child.polygon3D()).setVertexes(verts);
			//			}

			modS.setPolygon3D((VICUS::Polygon3D)poly);
			modS.setSubSurfaces(modSubs);
			modS.updateGeometryHoles();
			modifiedSurfaces.push_back(modS);
		}
		else {
			// we have translation and/or rotation
			// since we only manipulate the local coordinate system, we can just use in-place modifications
			// also, we do not redo the triangulation, which speeds up things a bit
			IBKMK::Polygon3D poly = modS.polygon3D();

			// we copy the surface's local, normal and offset
			IBKMK::Vector3D localX = poly.localX();
			IBKMK::Vector3D normal = poly.normal();
			IBKMK::Vector3D offset = poly.offset();
			IBKMK::Vector3D trans = QVector2IBKVector(translation);

			if (rotation != QQuaternion()) {
				// we rotate our axis and offset
				IBKMK::Quaternion rotate = QQuaternion2IBKQuaternion(rotation);
				rotate.rotateVector(localX);
				rotate.rotateVector(normal);
				rotate.rotateVector(offset);
			}

			trans = QVector2IBKVector(translation);

			// we set our rotated axises
			poly.setRotation(normal, localX);
			// we have to mind the we rotate around our
			// local coordinate system center point
			poly.translate(offset-poly.offset()+trans);

			// Polygon3D is dirty, but geometry is not
			modS.setPolygon3D((VICUS::Polygon3D)poly); // now geometry is also marked as dirty

			// rotateChild(modS, modifiedSurfaces, rotation, translation);

			modifiedSurfaces.push_back(modS);
		}

		// TODO : Stephan, scaling of subsurfaces _without_ their parent
		//
		// Note: m_selSubSurfaces may contain subsurfs whose parent surfaces are also selected - these
		//       need to be ignored since they are implicitely handled already.
		//
		// For isolated selected subsurface, we need to identify the parent surface and do:
		// - generate 3D vertexes for subsurface
		// - apply transformation to 3D vertexes
		// - compute projection of 3D vertexes onto local plane of parent subsurface and update polylines accordingly
		//
		// Mind: it is possible that due to the transformation the new subsurface geometry lies outside the original
		//       surface - this may easily happen if, for example, a subsurface is translated out of its parent surface.
		//       In this case the subsurface will still exist, but won't be a hole in the parent's surface geometry.
		//       TODO : such invalid subsurfaces should be visualized somehow.... ???? -> TODO : Andreas

	}

	for (const VICUS::SubSurface *ss : m_selSubSurfaces) {

		VICUS::Surface *parentSurf = dynamic_cast<VICUS::Surface*>(ss->m_parent);
		if (parentSurf == nullptr)
			continue; // just to be sure that we have a parental surface

		if(handledSurfaces.find(parentSurf) != handledSurfaces.end())
			continue; // already handled by surface scaling

		// copy our old surface and update its sub-surfaces
		VICUS::Surface newSurf(*parentSurf);

		// we cache our polygon data
		const IBKMK::Vector3D &offset3d = newSurf.geometry().offset();
		const IBKMK::Vector3D &localX = newSurf.geometry().localX();
		const IBKMK::Vector3D &localY = newSurf.geometry().localY();

		// we have to temporarily copy our old sub-surfaces
		std::vector<VICUS::SubSurface> newSubSurfs = newSurf.subSurfaces();

		for (unsigned int i=0; i<newSubSurfs.size(); ++i) {

			// number of sub-surfaces and holes should always be equal
			// Just in order to be safe
			Q_ASSERT( ( newSurf.subSurfaces().size() + newSurf.holes().size() ) == newSurf.geometry().holes().size());

			// we only modify our selected sub surface
			VICUS::SubSurface &subS = newSubSurfs[i];

			// if the window is not selected we skip it
			if (!subS.m_selected || !subS.m_visible)
				continue;

			// temporarily store our new sub-surface points
			std::vector<IBKMK::Vector2D> newSubSurfVertexes(subS.m_polygon2D.vertexes().size());
			// get the transformation matrix
			QMatrix4x4 transMat = SVViewStateHandler::instance().m_selectedGeometryObject->transform().toMatrix();

			for (unsigned int j=0; j<subS.m_polygon2D.vertexes().size(); ++j) {
				const IBKMK::Vector2D &v2D = subS.m_polygon2D.vertexes()[j];

				// we now calculate the 3D points of the sub surface
				IBKMK::Vector3D v3D = offset3d + localX * v2D.m_x + localY * v2D.m_y;

				v3D = QVector2IBKVector( transMat * IBKVector2QVector(v3D) );

				// reconstruct the polygon with new vertexes
				// we have to take the offset of our new scaled polygon
				IBKMK::planeCoordinates(offset3d, localX, localY, v3D, newSubSurfVertexes[j].m_x, newSubSurfVertexes[j].m_y);
			}

			newSubSurfs[i].m_polygon2D = newSubSurfVertexes;
		}

		handledSurfaces.insert(parentSurf);

		// we update the 2D polyline
		newSurf.setSubSurfaces(newSubSurfs);
		newSurf.updateGeometryHoles();
		modifiedSurfaces.push_back(newSurf);
	}

	for (const VICUS::Drawing *d : m_selDrawings) {
		VICUS::Drawing newDrawing(*d);
		// QVector3D origin = IBKVector2QVector(newDrawing.m_origin);

		if (rotation != QQuaternion(1, 0, 0, 0)) {
			// Translation of LCS
			IBKMK::Vector3D newOrigin = newDrawing.m_origin;

			const QVector3D &trans = m_lcsTransform.translation();

			newOrigin -= QVector2IBKVector(trans);
			QMatrix4x4 transform;
			transform.rotate(rotation);

			newOrigin = QVector2IBKVector(transform * IBKVector2QVector(newOrigin));
			newOrigin += QVector2IBKVector(trans);
			// rotation
			QQuaternion quaternion = rotation * newDrawing.m_rotationMatrix.toQuaternion();
			newDrawing.m_rotationMatrix.setQuaternion(quaternion);

			newDrawing.m_origin = newOrigin;
		}
		else
			newDrawing.m_origin += QVector2IBKVector(translation);

		modifiedDrawings.push_back(newDrawing);
	}

	// TODO : Netzwerk zeugs

	// in case operation was executed without any selected objects - should be prevented
	if (modifiedSurfaces.empty() && modifiedDrawings.empty())
		return;

	SVUndoModifySurfaceGeometry * undo = new SVUndoModifySurfaceGeometry(tr("Geometry modified"), modifiedSurfaces, modifiedDrawings );
	undo->push();

	// also disable apply and cancel buttons
	m_ui->pushButtonApply->setEnabled(false);
	m_ui->pushButtonCancel->setEnabled(false);
	SVViewStateHandler::instance().m_selectedGeometryObject->resetTransformation();
	// and update our inputs again
	updateUi(false);
}


void SVPropEditGeometry::on_pushButtonCopySurface_clicked() {
	SVUndoCopyBuildingGeometry * undo = SVUndoCopyBuildingGeometry::createUndoCopySurfaces(
				m_selSurfaces, localCopyTranslationVector());
	undo->push();
}


void SVPropEditGeometry::on_pushButtonCopySubsurface_clicked() {
	SVUndoCopyBuildingGeometry * undo = SVUndoCopyBuildingGeometry::createUndoCopySubSurfaces(
				m_selSubSurfaces, localCopyTranslationVector());
	undo->push();
}


void SVPropEditGeometry::on_pushButtonCopyRoom_clicked() {
	SVUndoCopyBuildingGeometry * undo = SVUndoCopyBuildingGeometry::createUndoCopyRooms(
				m_selRooms, localCopyTranslationVector());
	undo->push();
}


void SVPropEditGeometry::on_pushButtonCopyBuildingLevel_clicked() {
	SVUndoCopyBuildingGeometry * undo = SVUndoCopyBuildingGeometry::createUndoCopyBuildingLevels(
				m_selBuildingLevels, localCopyTranslationVector());
	undo->push();
}


void SVPropEditGeometry::on_pushButtonCopyBuilding_clicked() {
	SVUndoCopyBuildingGeometry * undo = SVUndoCopyBuildingGeometry::createUndoCopyBuildings(
				m_selBuildings, std::vector<const VICUS::Surface*>(), localCopyTranslationVector());
	undo->push();
}

void SVPropEditGeometry::on_pushButtonTrimGridXY_clicked() {
	m_ui->lineEditRotateXTrimming->setValue(0);
	m_ui->lineEditRotateYTrimming->setValue(0);
	m_ui->lineEditRotateZTrimming->setValue(0);

	Vic3D::TrimmingObject &to = *SVViewStateHandler::instance().m_trimmingObject;
	to.setTrimmingPlaneNormal(IBKMK::Vector3D(0,0,1));
	to.updateTrimmingPlane();

	const_cast<Vic3D::SceneView*>(SVViewStateHandler::instance().m_geometryView->sceneView())->renderLater();
}


void SVPropEditGeometry::on_pushButtonTrimGridYZ_clicked() {
	m_ui->lineEditRotateXTrimming->setValue(0);
	m_ui->lineEditRotateYTrimming->setValue(0);
	m_ui->lineEditRotateZTrimming->setValue(0);

	Vic3D::TrimmingObject &to = *SVViewStateHandler::instance().m_trimmingObject;
	to.setTrimmingPlaneNormal(IBKMK::Vector3D(1,0,0));
	to.updateTrimmingPlane();

	const_cast<Vic3D::SceneView*>(SVViewStateHandler::instance().m_geometryView->sceneView())->renderLater();
}


void SVPropEditGeometry::on_pushButtonTrimGridXZ_clicked() {
	m_ui->lineEditRotateXTrimming->setValue(0);
	m_ui->lineEditRotateYTrimming->setValue(0);
	m_ui->lineEditRotateZTrimming->setValue(0);

	Vic3D::TrimmingObject &to = *SVViewStateHandler::instance().m_trimmingObject;
	to.setTrimmingPlaneNormal(IBKMK::Vector3D(0,1,0));
	to.updateTrimmingPlane();

	const_cast<Vic3D::SceneView*>(SVViewStateHandler::instance().m_geometryView->sceneView())->renderLater();
}

void SVPropEditGeometry::on_pushButtonTrimGridLocalXY_clicked() {
	m_ui->lineEditRotateXTrimming->setValue(0);
	m_ui->lineEditRotateYTrimming->setValue(0);
	m_ui->lineEditRotateZTrimming->setValue(0);

	Vic3D::CoordinateSystemObject *cso = SVViewStateHandler::instance().m_coordinateSystemObject;
	Vic3D::TrimmingObject &to = *SVViewStateHandler::instance().m_trimmingObject;
	to.setTrimmingPlaneNormal(QVector2IBKVector(cso->localZAxis()));
	to.updateTrimmingPlane();

	const_cast<Vic3D::SceneView*>(SVViewStateHandler::instance().m_geometryView->sceneView())->renderLater();
}


void SVPropEditGeometry::on_pushButtonTrimGridLocalYZ_clicked() {
	m_ui->lineEditRotateXTrimming->setValue(0);
	m_ui->lineEditRotateYTrimming->setValue(0);
	m_ui->lineEditRotateZTrimming->setValue(0);

	Vic3D::CoordinateSystemObject *cso = SVViewStateHandler::instance().m_coordinateSystemObject;
	Vic3D::TrimmingObject &to = *SVViewStateHandler::instance().m_trimmingObject;
	to.setTrimmingPlaneNormal(QVector2IBKVector(cso->localXAxis()));
	to.updateTrimmingPlane();

	const_cast<Vic3D::SceneView*>(SVViewStateHandler::instance().m_geometryView->sceneView())->renderLater();
}


void SVPropEditGeometry::on_pushButtonTrimGridLocalXZ_clicked() {

	/// --- Temporary UI embedding of polygon merge --- /// TODO Stephan remove

		std::set<const VICUS::Object *> sel;
		SVProjectHandler::instance().project().selectObjects(sel, VICUS::Project::SelectionGroups(VICUS::Project::SG_Building | VICUS::Project::SG_Obstacle), true, true);
		std::vector<const VICUS::Surface*> surfs;
		for (const VICUS::Object* o : sel) {
			const VICUS::Surface * surf = dynamic_cast<const VICUS::Surface*>(o);
			if (surf == nullptr) continue; // skip all other objects
			surfs.push_back(surf);
		}
		if (surfs.size() != 2) return;
		const VICUS::Surface * surfA = surfs.at(0);
		const VICUS::Surface * surfB = surfs.at(1);
		IBKMK::Polygon3D polyA = surfA->polygon3D();
		const IBKMK::Polygon3D polyB = surfB->polygon3D();
		std::vector<std::vector<IBKMK::Vector2D>> holes;
		bool merged = polyA.mergeWithPolygon(polyB, holes);
		if (merged) {
			VICUS::Surface newSurf;
			newSurf.m_id = project().nextUnusedID();
			newSurf.m_displayName = surfA->m_displayName;
			newSurf.m_color = surfA->m_displayColor;
			newSurf.m_displayColor = surfA->m_displayColor;
			newSurf.setPolygon3D(polyA);
			std::vector<VICUS::Hole> vicusHoles = surfA->holes();
			vicusHoles.insert( vicusHoles.end(), surfB->holes().begin(), surfB->holes().end() );
			for (std::vector<IBKMK::Vector2D> hole : holes) {
				vicusHoles.push_back(VICUS::Hole(hole));
			}
			newSurf.setHoles(vicusHoles);
			newSurf.updateGeometryHoles();
			SVUndoAddSurface * undo = new SVUndoAddSurface("Merged.", newSurf, 0);
			undo->push();
		}
		return;

	/// ------------------------------------------------------------------ ///



	m_ui->lineEditRotateXTrimming->setValue(0);
	m_ui->lineEditRotateYTrimming->setValue(0);
	m_ui->lineEditRotateZTrimming->setValue(0);

	Vic3D::CoordinateSystemObject *cso = SVViewStateHandler::instance().m_coordinateSystemObject;
	Vic3D::TrimmingObject &to = *SVViewStateHandler::instance().m_trimmingObject;
	to.setTrimmingPlaneNormal(QVector2IBKVector(cso->localYAxis()));
	to.updateTrimmingPlane();

	const_cast<Vic3D::SceneView*>(SVViewStateHandler::instance().m_geometryView->sceneView())->renderLater();
}


void SVPropEditGeometry::on_pushButtonTrimPolygons_clicked() {

	/// TRIMMING SUB SURFACES
	/// 1) Convert all 2D points with axes, offest of parent surfaces
	/// 2) Trim all sub-surfaces and parent surface
	/// 3) Find correct parent surface, since we might have 2 or more now by
	///		doing point in polygon function etc.
	/// 4) Translate 3D points back to 2D point by IBKMK::planeCoordinates
	/// 5) Set sub-surfaces in parent polygon

	TrimmingProgress progressNotifyer;
	progressNotifyer.m_prgDlg = new QProgressDialog(tr("Trimming"), tr("Cancel"), 0, 100, this);
	progressNotifyer.m_prgDlg->setMinimumDuration(500);

	std::vector<IBKMK::Vector3D> trimmingPolygon;
	Vic3D::TrimmingObject &to = *SVViewStateHandler::instance().m_trimmingObject;

	std::set<const VICUS::Object *> sel;
	SVProjectHandler::instance().project().selectObjects(sel, VICUS::Project::SelectionGroups(VICUS::Project::SG_Building | VICUS::Project::SG_Obstacle), true, true);
	std::string failedTrims = "";
	int successfulTrims = 0;

	VICUS::ComponentInstance compInstance;
	std::map<unsigned int, std::vector<IBKMK::Polygon3D>> trimmedSurfacePolygons;
	std::map<unsigned int, std::vector<IBKMK::Polygon3D>> trimmedSubSurfacePolygons;
	std::map<unsigned int, std::map<unsigned int, std::vector<VICUS::Hole>>> trimmedSurfaceHoles;

	// *** selected surfaces ***
	for (const VICUS::Object* o : sel) {
		const VICUS::Surface * surf = dynamic_cast<const VICUS::Surface*>(o);
		if (surf == nullptr)
			continue; // skip all other objects

		// we just take a copy to be sure
		IBKMK::Polygon3D surfacePolygon = surf->polygon3D();
		std::vector<IBKMK::Polygon3D> trimmedPolygons;

		// *** TRIMMING OF POLYGONS HANDLED HERE ***
		bool trimmingSuccessful = surfacePolygon.trimByPlane(to.trimmingPolygon(), trimmedPolygons);
		// *****************************************

		if (!trimmingSuccessful) {
			qDebug() << "Could not trim polygon of surface '" << surf->m_displayName << "' with ID #" << surf->m_id;
			continue;
		}

		// Iterate over all holes in polygon, divide them into two vectors:
		// holes that will be relocated to their new parent surface, and
		// holes that got trimmed along the surface and will be base for new polyline calculation,
		// as they're now sharing a polygon border with the new polygon
		std::vector<IBKMK::Polygon3D> resultingHoles;
		std::vector<IBKMK::Polygon3D> holesToBeRemoved;
		const std::vector<VICUS::Hole> & polyHoles = surf->holes();
		for (const VICUS::Hole & trimPolyHole : polyHoles) {
			const IBKMK::Polygon3D polyHole3D = surf->generatePolygon3D(trimPolyHole.m_holePolygon);
			std::vector<IBKMK::Polygon3D> trimmedHoles;
			bool holeTrimSuccess = polyHole3D.trimByPlane(to.trimmingPolygon(), trimmedHoles);
			if (holeTrimSuccess) {
				// Hole intersected plane, has to be removed after
				for (const IBKMK::Polygon3D & trimmedHole : trimmedHoles) {
					if (trimmedHole.isValid())
						holesToBeRemoved.push_back(trimmedHole);
				}
			} else {
				// Hole not intersecting plane, add to corresponding polygon
				resultingHoles.push_back(polyHole3D);
			}
		}

		// Detect Holes that didn't get trimmed due to sharing a border with the trimming plane,
		// however these have to be fixed as they're now part of an outside border of the resulting polygon
		// Iterating backwards so removal can be performed without messing up the indices
		IBKMK::Vector3D trimVector1 = to.trimmingPolygon().vertexes().at(1) - to.trimmingPolygon().vertexes().at(0);
		IBKMK::Vector3D trimVector2 = to.trimmingPolygon().vertexes().at(2) - to.trimmingPolygon().vertexes().at(0);
		trimVector1 = trimVector1 * (10/trimVector1.magnitude());
		trimVector2 = trimVector2 * (10/trimVector2.magnitude());
		const IBKMK::Vector3D trimNormalVector = trimVector1.crossProduct(trimVector2);
		const int trimOffset = trimNormalVector.scalarProduct(to.trimmingPolygon().vertexes().at(0));

		for (int i = resultingHoles.size()-1; i >= 0; --i) {
			const std::vector<IBKMK::Vector3D> & holeVerts = resultingHoles.at(i).vertexes();
			double prev_dist = trimNormalVector.scalarProduct(holeVerts.back())-trimOffset;;
			double dist;
			for (const IBKMK::Vector3D & point : holeVerts) {
				dist = trimNormalVector.scalarProduct(point)-trimOffset;
				if (IBK::near_zero(dist) && IBK::near_zero(prev_dist)) {
					holesToBeRemoved.push_back(resultingHoles.at(i));
					resultingHoles.erase(resultingHoles.begin() + i);
					break;
				} else {
					prev_dist = dist;
				}
			}
		}
		//qDebug() << "HolesToBeRemoved: " << holesToBeRemoved.size() << " / resultingHoles: " << resultingHoles.size();

		// Attribute holes to their parent surfaces, adjust the parent geometry vertices to effectively remove the hole by shaping a new outline
		for (const IBKMK::Polygon3D & holePoly : holesToBeRemoved) {
			// Find parent polygon
			bool found = false;
			for (unsigned int i = 0; i < trimmedPolygons.size(); ++i) {
				IBKMK::Polygon3D & poly = trimmedPolygons.at(i);

				// make sure we're on the same side of the trimming plane
				double holeCenterDist = trimNormalVector.scalarProduct(holePoly.centerPoint())-trimOffset;
				double polyCenterDist = trimNormalVector.scalarProduct(poly.centerPoint())-trimOffset;
				if (holeCenterDist * polyCenterDist < 0) continue;

				for (const IBKMK::Vector3D & vert : holePoly.vertexes()) {

					int pointInPoly = IBKMK::coplanarPointInPolygon3D(poly.vertexes(), vert);
					if (pointInPoly == 1) {
						found = true;

						std::vector<IBKMK::Vector3D> polyVerts = poly.vertexes();
						std::vector<IBKMK::Vector3D> holeVerts = holePoly.vertexes();

						// algorithm robustness: if ALL hole or poly verts are near_zero: discard now,
						// otherwise we're facing an endless loop later
						unsigned int polyVertsNotOnTrimLine = 0;
						unsigned int holeVertsNotOnTrimLine = 0;
						for (const IBKMK::Vector3D & polyVert : polyVerts) if (!IBK::near_zero(trimNormalVector.scalarProduct(polyVert)-trimOffset)) polyVertsNotOnTrimLine++;
						for (const IBKMK::Vector3D & holeVert : holeVerts) if (!IBK::near_zero(trimNormalVector.scalarProduct(holeVert)-trimOffset)) holeVertsNotOnTrimLine++;
						if (polyVertsNotOnTrimLine == 0 || holeVertsNotOnTrimLine == 0) break;

						// Find all polygon / hole edges that lie on the trimming line
						std::vector<std::pair<int, int>> polyVertsOnTrimLine;
						std::vector<std::pair<int, int>> holeVertsOnTrimLine;

						// Find all hole edges that lie on the trimming line
						int k;
						for (int j = 0; j < (int)holeVerts.size(); ++j) {
							k = (j+holeVerts.size()-1) % holeVerts.size();
							if (IBK::near_zero(trimNormalVector.scalarProduct(holeVerts.at(j))-trimOffset) &&
								IBK::near_zero(trimNormalVector.scalarProduct(holeVerts.at(k))-trimOffset)) {
								holeVertsOnTrimLine.push_back(std::pair<int, int>(k,j));
							}
						}

						// If hole has multiple contact edges with trimming line,
						// to prevent recursion, we will move this hole slightly into the polygon, instead of cutting it out.
						if (holeVertsOnTrimLine.size() > 1) {

							IBKMK::Vector3D trimNormalVectorSmall = trimNormalVector.normalized();
							trimNormalVectorSmall /= 9.9e3;
							// this has to be smaller than 1e4 because otherwise the verts can get joined
							// after an additional diagonal trim, and the polygon shape may become invalid.


							// Adjust trimNormalVectorSmall to point in the right direction
							for (const IBKMK::Vector3D & holeVert : holeVerts) {
								double dist = trimNormalVector.scalarProduct(holeVert)-trimOffset;
								if (!IBK::near_zero(dist)) {
									if (dist < 0) trimNormalVectorSmall *= -1;
									break;
								}
							}

							// Move border verts into poly
							for (IBKMK::Vector3D & holeVert : holeVerts) {
								double dist = trimNormalVector.scalarProduct(holeVert)-trimOffset;
								if (IBK::near_zero(dist)) {
									holeVert += trimNormalVectorSmall;
								}
							}
							resultingHoles.push_back(VICUS::Polygon3D(holeVerts));
							break;
						}

						// Find all polygon edges that lie on the trimming line
						for (int j = 0; j < (int)polyVerts.size(); ++j) {
							k = (j+polyVerts.size()-1) % polyVerts.size();
							if (IBK::near_zero(trimNormalVector.scalarProduct(polyVerts.at(j))-trimOffset) &&
								IBK::near_zero(trimNormalVector.scalarProduct(polyVerts.at(k))-trimOffset)) {

								// Extend j and k to find border points near_zero.
								// This is only necessary to prevent malfunction in the rare case, that a vertex happened to be in near_zero distance to the
								// trimming line already before trimming. Otherwise this would result in adding the hole vertices at the wrong index.
								while (IBK::near_zero(trimNormalVector.scalarProduct(polyVerts.at((j+1)%polyVerts.size()))-trimOffset)) j++;
								while (IBK::near_zero(trimNormalVector.scalarProduct(polyVerts.at((k+polyVerts.size()-1)%polyVerts.size()))-trimOffset)) k--;
								polyVertsOnTrimLine.push_back(std::pair<int, int>(k,j));
							}
						}

						// Remove the detected redundant vertices and adjust the indices
						for (unsigned int j = 0; j < polyVertsOnTrimLine.size(); ++j) {
							std::pair<int, int> & polyPair = polyVertsOnTrimLine.at(j);
							int pair_difference = (polyVerts.size() + polyPair.second - polyPair.first) % polyVerts.size();
							if (pair_difference > 1) {
								for (int k = 1; k < pair_difference; ++k) {
									// Delete the vert following the first vert, as many times as there are verts inbetween beginning and end
									polyVerts.erase(polyVerts.begin() + ((polyPair.first + 1) % polyVerts.size()));
								}
								for (std::pair<int, int> & polyPair2 : polyVertsOnTrimLine) {
									// reduce every higher index by the amount of verts we removed, i.e the amount the
									// difference exceeds the default difference of 1
									if (polyPair2.first > polyPair.first) { // value above removed index
										polyPair2.first -= pair_difference-1;
									}
									if (polyPair2.second > polyPair.first) {
										polyPair2.second -= pair_difference-1;
									}
								}
							}
						}

						// Find vertpair that surrounds hole and insert hole into polygon line
						std::pair<unsigned int, unsigned int> holeVertsOnTrimLinePair = holeVertsOnTrimLine.front();
						for (const std::pair<unsigned int, unsigned int> vertPair : polyVertsOnTrimLine) {
							if (pointBetweenPoints(holeVerts.at(holeVertsOnTrimLinePair.first), polyVerts.at(vertPair.first), polyVerts.at(vertPair.second)) &&
								pointBetweenPoints(holeVerts.at(holeVertsOnTrimLinePair.second), polyVerts.at(vertPair.first), polyVerts.at(vertPair.second))) {
								// Find out in which direction the two polygons (hole and trimPoly) turn

								std::pair<IBKMK::Vector3D, IBKMK::Vector3D> polyVertsAB(polyVerts.at(vertPair.first),polyVerts.at(vertPair.second));
								std::pair<IBKMK::Vector3D, IBKMK::Vector3D> holeVertsAB(holeVerts.at(holeVertsOnTrimLinePair.first),holeVerts.at(holeVertsOnTrimLinePair.second));

								bool flipVertDir =(holeVertsAB.first - polyVertsAB.first).magnitude() < (holeVertsAB.second - polyVertsAB.first).magnitude();

								if (flipVertDir) {
									for (unsigned int j = 0; j < holeVerts.size(); ++j) {
										polyVerts.insert(polyVerts.begin() + vertPair.second, holeVerts.at((holeVertsOnTrimLinePair.second + j)%holeVerts.size()));
										// holeverts from second to first, long way round
									}
								} else {
									for (unsigned int j = 0; j < holeVerts.size(); ++j) {
										polyVerts.insert(polyVerts.begin() + vertPair.second, holeVerts.at((holeVertsOnTrimLinePair.first + holeVerts.size() - j)%holeVerts.size()));
										// holeverts from first to second, long way round
									}
								}
								break;
							}
						}

						poly.setVertexes(polyVerts);
						break;
					}
				}
				if (found) break;
			}
		}

		std::vector<IBKMK::Polygon3D> validTrimmedPolys;
		for (const IBKMK::Polygon3D &trimmedPoly : trimmedPolygons) {
			if (!trimmedPoly.isValid()) continue; // skip broken polygons
			validTrimmedPolys.push_back(trimmedPoly);
		}
		trimmedSurfacePolygons[surf->m_id] = validTrimmedPolys;

		// Transform holes back to 2d and attach them to corresponding surface and corresponding id of post-trim-surfaces
		IBKMK::Vector2D point;		// initialize for planeCoordinates()
		for (const IBKMK::Polygon3D & holeToBeInserted3D : resultingHoles) {
			if (holeToBeInserted3D.vertexes().size() < 3) break; // malformated
			for (unsigned int i = 0; i < validTrimmedPolys.size(); ++i) {
				const IBKMK::Polygon3D & polyAtIndex = validTrimmedPolys.at(i);
				// vertices can lie ON poly line (==0) but among two neighbouring one has to be inside the polygon
				if (IBKMK::coplanarPointInPolygon3D(polyAtIndex.vertexes(), holeToBeInserted3D.vertexes().front()) > 0 ||
					IBKMK::coplanarPointInPolygon3D(polyAtIndex.vertexes(), holeToBeInserted3D.vertexes().at(1)) > 0) {
					// Matching surface found, transforming hole back into 2d
					// Insert it into map accordingly and break loop to process next hole
					std::vector<IBKMK::Vector2D> holeToBeInserted2D(holeToBeInserted3D.vertexes().size());
					for (unsigned int j = 0; j < holeToBeInserted3D.vertexes().size(); ++j) {
						IBKMK::planeCoordinates(polyAtIndex.offset(), polyAtIndex.localX(), polyAtIndex.localY(), holeToBeInserted3D.vertexes()[j], point.m_x, point.m_y);
						holeToBeInserted2D.at(j) = point;
					}
					VICUS::Hole holeToBeInserted(holeToBeInserted2D);
					trimmedSurfaceHoles[surf->m_id][i].push_back(holeToBeInserted);
					break;
				}
			}
		}

		//		qDebug() << QString("Trimming of surface %1 successful.").arg(surf->info());
		++successfulTrims;
	}

	// *** selected subsurfaces ***
	for (const VICUS::Object* o : sel) {
		const VICUS::SubSurface * subSurf = dynamic_cast<const VICUS::SubSurface*>(o);
		if (subSurf == nullptr)
			continue; // skip all other objects

		VICUS::Surface *surf = dynamic_cast<VICUS::Surface*>(subSurf->m_parent);
		Q_ASSERT(surf != nullptr);

		//qDebug() << "has subsurface" << subS.m_id;
		const IBKMK::Vector3D &offset3D = surf->polygon3D().offset();
		const std::vector<IBKMK::Vector2D> &verts = subSurf->m_polygon2D.vertexes();

		// Transforming 2d SubSurface into 3d surface
		// ToDo Moritz: Can this be done with generatePolygon3D ?
		std::vector<IBKMK::Vector3D> verts3D(verts.size());

		for (unsigned int i = 0; i < verts.size(); ++i) {
			const IBKMK::Vector2D & point2d = verts[i];
			verts3D[i] = offset3D + surf->polygon3D().localX() * point2d.m_x +
					surf->polygon3D().localY() * point2d.m_y;
		}

		IBKMK::Polygon3D subSurfacePolygon(verts3D);
		std::vector<IBKMK::Polygon3D> trimmedSubSurfacePolys;

		// *** TRIMMING OF SUB SURFACE POLYGONS HANDLED HERE ***
		bool subSurfaceTrimmingSuccessful = subSurfacePolygon.trimByPlane(to.trimmingPolygon(), trimmedSubSurfacePolys);
		// *****************************************************

		if (!subSurfaceTrimmingSuccessful) {
			qDebug() << "Could not trim polygon of sub-surface '" << subSurf->m_displayName << "' with ID #" << subSurf->m_id;

			// Push back entire sub-surface without trimming
			trimmedSubSurfacePolygons[subSurf->m_id].push_back(IBKMK::Polygon3D(verts3D));

			// handle next sub-surface
			continue;
		}

		// subSurface trimmed, add results to corresponding parent surfaces
		std::vector<IBKMK::Polygon3D> validTrimmedSubSurfacePolygons;
		for (const IBKMK::Polygon3D &subSurfacePolygon : trimmedSubSurfacePolys) {
			if (!subSurfacePolygon.isValid())
				continue;

			// Add back valid polygon
			validTrimmedSubSurfacePolygons.push_back(subSurfacePolygon);
		}
		// Add back trimmes sub surfaces
		trimmedSubSurfacePolygons[subSurf->m_id] = validTrimmedSubSurfacePolygons;

		// Readd old polygon
		if (trimmedSurfacePolygons.find(surf->m_id) == trimmedSurfacePolygons.end())
			trimmedSurfacePolygons[surf->m_id].push_back(surf->polygon3D());

		// Readd original surface polygon, if it hasn't been trimmed before
		++successfulTrims;
	}

	if (successfulTrims == 0) {
		qDebug() << "No trimming was performed.";
		return;
	}

	// create a copy of the whole project
	VICUS::Project projectCopy = SVProjectHandler::instance().project();
	SVUndoTrimObjects * undo = new SVUndoTrimObjects(tr("Trimming performed."), trimmedSurfacePolygons, trimmedSubSurfacePolygons, trimmedSurfaceHoles, projectCopy, &progressNotifyer);
	undo->push();

}


void SVPropEditGeometry::on_pushButtonApplyRotation_clicked() {
	m_ui->lineEditRotateXTrimming->setValue(0);
	m_ui->lineEditRotateYTrimming->setValue(0);
	m_ui->lineEditRotateZTrimming->setValue(0);
}


void SVPropEditGeometry::on_pushButtonApplyTrimmingRotation_clicked() {
	Q_ASSERT(SVViewStateHandler::instance().m_trimmingObject != nullptr);
	SVViewStateHandler::instance().m_trimmingObject->setTrimmingPlaneNormal(m_trimingPlaneNormal);
}

void SVPropEditGeometry::on_comboBoxUnit_currentIndexChanged(int /*index*/) {
	enableTransformation();
}

void SVPropEditGeometry::on_pushButtonFixSurfaceOrientation_clicked() {
	FUNCID(on_pushButtonFixSurfaceOrientation_clicked);

	/// 1) We take all surfaces from each room
	/// 2) We calculate the surface weight point by points
	/// 3) We take its normal from the middle point
	/// 4) We construct a long ray (e.g. 1000m)
	/// 5) We check if we cut other surfaces of the room
	/// 6) If surface cutting count is 0 or even the normal points into correct direction
	/// 7) If surface cutting count is uneven the normal should be inverted

	VICUS::Project prj = SVProjectHandler::instance().project();

	std::vector<VICUS::Surface> modifiedSurfaces;

	for (const VICUS::Building &b : prj.m_buildings) {
		for (const VICUS::BuildingLevel &bl : b.m_buildingLevels) {
			for (const VICUS::Room &r : bl.m_rooms) {
				for (const VICUS::Surface &s : r.m_surfaces) {

					if (!s.geometry().isValid())
						continue;

					if (!s.m_visible || !s.m_selected)
						continue;

					unsigned int intersectionCount = 0;

					// Find Intersection
					IBKMK::Vector3D center;

					const IBKMK::Vector3D &offset = s.geometry().offset();
					const IBKMK::Vector3D &localX = s.geometry().localX();
					const IBKMK::Vector3D &localY = s.geometry().localY();

					for (unsigned int i=0; i<s.geometry().polygon3D().vertexes().size(); ++i) {
						for(unsigned int j=0; j<3; ++j) {
							unsigned int idx = (i+j)%s.geometry().polygon3D().vertexes().size();
							const IBKMK::Vector3D &v3D = s.geometry().polygon3D().vertexes()[idx];

							center += v3D;
						}

						center /= 3.;

						IBKMK::Vector2D p;

						// Check if point lies within polygon
						if (!IBKMK::planeCoordinates(offset, localX, localY, center, p.m_x, p.m_y))
							continue;

						if(IBKMK::pointInPolygon(s.geometry().polygon2D().vertexes(), p) != -1)
							break;

						center = IBKMK::Vector3D();
					}

					const IBKMK::Vector3D &normal = s.geometry().normal();

					for (const VICUS::Surface &sTest : r.m_surfaces) {

						if (s.m_id == sTest.m_id)
							continue;

						if(!sTest.geometry().isValid())
							continue;

						const IBKMK::Vector3D &offset = sTest.geometry().offset();
						const IBKMK::Vector3D &localX = sTest.geometry().localX();
						const IBKMK::Vector3D &localY = sTest.geometry().localY();
						const IBKMK::Vector3D &normalTest = sTest.geometry().normal();

						IBKMK::Vector3D v;
						IBKMK::Vector2D p;
						double dist;

						if (!IBKMK::linePlaneIntersectionWithNormalCheck(offset, normalTest, center, normal, v, dist, false))
							continue;

						if (dist < 1E-3)
							continue;

						if (!IBKMK::planeCoordinates(offset, localX, localY, v, p.m_x, p.m_y))
							continue;

						if(IBKMK::pointInPolygon(sTest.geometry().polygon2D().vertexes(), p) == -1)
							continue;

						++intersectionCount;
					}

					if (intersectionCount > 0 && intersectionCount % 2 == 1) {
						IBK::IBK_Message(IBK::FormatString("Surface #%2 %1 is beeing flipped.").arg(s.m_displayName.toStdString()).arg(s.m_id), IBK::MSG_WARNING, FUNC_ID);

						const_cast<VICUS::Surface &>(s).flip();
						const_cast<VICUS::Surface &>(s).initializeColorBasedOnInclination(); // reset color
						modifiedSurfaces.push_back(s);
					}
				}
			}
		}
	}

	// in case operation was executed without any selected objects - should be prevented
	if (modifiedSurfaces.empty())
		return;

	std::vector<VICUS::Drawing> drawings;
	SVUndoModifySurfaceGeometry * undo = new SVUndoModifySurfaceGeometry(tr("Surface normal flipped"), modifiedSurfaces, drawings );
	undo->push();

	// also disable apply and cancel buttons
	m_ui->pushButtonApply->setEnabled(false);
	m_ui->pushButtonCancel->setEnabled(false);
	SVViewStateHandler::instance().m_selectedGeometryObject->resetTransformation();
	// and update our inputs again
	updateUi();

}

