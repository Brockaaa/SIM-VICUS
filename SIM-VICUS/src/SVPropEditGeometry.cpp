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


/*! helper function to compare two IBKMK vectors */
template <int digits>
bool vectors_equal(const IBKMK::Vector3D &v1, const IBKMK::Vector3D &v2 ) {
	return ( IBK::nearly_equal<digits>(v1.m_x, v2.m_x) &&
			 IBK::nearly_equal<digits>(v1.m_y, v2.m_y) &&
			 IBK::nearly_equal<digits>(v1.m_z, v2.m_z) );
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

	m_ui->lineEditRotateX_2->setFormatter(new LineEditFormater);
	m_ui->lineEditRotateY_2->setFormatter(new LineEditFormater);
	m_ui->lineEditRotateZ_2->setFormatter(new LineEditFormater);
	m_ui->lineEditRotateX_2->installEventFilter(this);
	m_ui->lineEditRotateY_2->installEventFilter(this);
	m_ui->lineEditRotateZ_2->installEventFilter(this);

	m_ui->lineEditScaleX->setFormatter(new LineEditFormater);
	m_ui->lineEditScaleY->setFormatter(new LineEditFormater);
	m_ui->lineEditScaleZ->setFormatter(new LineEditFormater);

	m_ui->lineEditScaleX->installEventFilter(this);
	m_ui->lineEditScaleY->installEventFilter(this);
	m_ui->lineEditScaleZ->installEventFilter(this);

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

	connect(m_ui->lineEditRotateX_2, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditRotateY_2, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditRotateZ_2, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);

	connect(m_ui->lineEditScaleX, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditScaleY, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditScaleZ, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);

	connect(m_ui->lineEditTranslateX, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditTranslateY, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
	connect(m_ui->lineEditTranslateZ, &QLineEdit::textChanged, this, &SVPropEditGeometry::onLineEditTextEdited);
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
	// only adjust local coordinate system, if this widget is visible
	if (this->isVisibleTo(qobject_cast<QWidget*>(parent())) ) {
		// Note: setting new coordinates to the local coordinate system object will in turn call setCoordinates()
		//       and indirectly also updateInputs()
		updateCoordinateSystemLook();
		updateTrimmingGrid();
		adjustLocalCoordinateSystemForRotateToAngle();
	}
}


void SVPropEditGeometry::setCoordinates(const Vic3D::Transform3D &t) {
	Vic3D::CoordinateSystemObject *cso = SVViewStateHandler::instance().m_coordinateSystemObject;

	// is being called from local coordinate system object, whenever this has changed location (regardless of
	// its own visibility)
	m_lcsTransform =  t;

	// compute dimensions of bounding box (dx, dy, dz) and center point of all selected surfaces
	m_bbDim[OM_Local] = project().boundingBox(m_selSurfaces, m_selSubSurfaces, m_bbCenter[OM_Local],
											  QVector2IBKVector(cso->translation() ),
											  QVector2IBKVector(cso->localXAxis() ),
											  QVector2IBKVector(cso->localYAxis() ),
											  QVector2IBKVector(cso->localZAxis() ) );
	m_bbDim[OM_Global] = project().boundingBox(m_selSurfaces, m_selSubSurfaces, m_bbCenter[OM_Global]);


	m_normal = QVector2IBKVector(cso->localZAxis());
	updateInputs();
	updateTrimmingGridLcs();
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



// *** PROTECTED FUNCTIONS ***

bool SVPropEditGeometry::eventFilter(QObject * target, QEvent * event) {

	if ( event->type() == QEvent::Wheel ) {
		// we listen to scroll wheel turns only for some line edits
		if (target == m_ui->lineEditTranslateX ||
				target == m_ui->lineEditTranslateY ||
				target == m_ui->lineEditTranslateZ ||
				target == m_ui->lineEditRotateInclination ||
				target == m_ui->lineEditRotateOrientation ||
				target == m_ui->lineEditRotateX ||
				target == m_ui->lineEditRotateY ||
				target == m_ui->lineEditRotateZ ||
				target == m_ui->lineEditRotateX_2 ||
				target == m_ui->lineEditRotateY_2 ||
				target == m_ui->lineEditRotateZ_2 ||
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
				case MT_Rotate					: delta = 1; break;
				case NUM_MT : ; // just to make compiler happy
			}

			QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
			// offset are changed in 0.01 steps
			double offset = (wheelEvent->delta()>0) ? delta : -delta;
			onWheelTurned(offset, qobject_cast<QtExt::ValidatingLineEdit*>(target)); // we know that target points to a ValidatingLineEdit
		}
	}
	return false;
}

// *** PRIVATE SLOTS***

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

void SVPropEditGeometry::on_lineEditRotateX_2_editingFinishedSuccessfully() {
	m_ui->lineEditRotateY_2->setValue(0);
	m_ui->lineEditRotateZ_2->setValue(0);
	updateTrimGridRotationPreview();
}


void SVPropEditGeometry::on_lineEditRotateY_2_editingFinishedSuccessfully() {
	m_ui->lineEditRotateX_2->setValue(0);
	m_ui->lineEditRotateZ_2->setValue(0);
	updateTrimGridRotationPreview();
}


void SVPropEditGeometry::on_lineEditRotateZ_2_editingFinishedSuccessfully() {
	m_ui->lineEditRotateY_2->setValue(0);
	m_ui->lineEditRotateX_2->setValue(0);
	updateTrimGridRotationPreview();
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
	for (const VICUS::Surface* s : m_selSurfaces) {
		// create a copy of the surface
		VICUS::Surface modS(*s);
		modS.flip();
		modifiedSurfaces.push_back(modS);
	}
	// in case operation was executed without any selected objects - should be prevented
	if (modifiedSurfaces.empty())
		return;

	SVUndoModifySurfaceGeometry * undo = new SVUndoModifySurfaceGeometry(tr("Surface normal flipped"), modifiedSurfaces );
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
	}

	// compute dimensions of bounding box (dx, dy, dz) and center point of all selected surfaces
	m_bbDim[OM_Local] = project().boundingBox(m_selSurfaces, m_selSubSurfaces, m_bbCenter[OM_Local],
											  QVector2IBKVector(cso->translation() ),
											  QVector2IBKVector(cso->localXAxis() ),
											  QVector2IBKVector(cso->localYAxis() ),
											  QVector2IBKVector(cso->localZAxis() ) );
	m_bbDim[OM_Global] = project().boundingBox(m_selSurfaces, m_selSubSurfaces, m_bbCenter[OM_Global]);

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

	bool noSelection = m_selSurfaces.empty() && m_selSubSurfaces.empty() &&
			m_selRooms.empty() && m_selBuildingLevels.empty() && m_selBuildings.empty();

	setEnabled(!noSelection);
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
		if (!vectors_equal<4>( m_normal, newNormal ) ) {

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

void SVPropEditGeometry::updateTrimGridRotationPreview() {
	if (m_trimGrid != nullptr) {
		Vic3D::Transform3D rot;
		Vic3D::CoordinateSystemObject *cso = SVViewStateHandler::instance().m_coordinateSystemObject;
		Q_ASSERT(cso != nullptr);

		if (m_ui->lineEditRotateX_2->isValid() && m_ui->lineEditRotateX_2->value() != 0.)
			rot.setRotation((float)m_ui->lineEditRotateX_2->value(), cso->localXAxis());
		if (m_ui->lineEditRotateY_2->isValid() && m_ui->lineEditRotateY_2->value() != 0.)
			rot.setRotation((float)m_ui->lineEditRotateY_2->value(), cso->localYAxis());
		if (m_ui->lineEditRotateZ_2->isValid() && m_ui->lineEditRotateZ_2->value() != 0.)
			rot.setRotation((float)m_ui->lineEditRotateZ_2->value(), cso->localZAxis());

		//reset to old values before rotation
		m_trimGrid->m_localX = m_previousRotation.m_localX;
		m_trimGrid->m_normal = m_previousRotation.m_normal;
		m_trimGrid->updateLocalY();

		m_trimGrid->m_localX = QVector2IBKVector(rot.rotation().rotatedVector(IBKVector2QVector(m_trimGrid->m_localX))).normalized();
		m_trimGrid->m_normal = QVector2IBKVector(rot.rotation().rotatedVector(IBKVector2QVector(m_trimGrid->m_normal))).normalized();

		m_trimGrid->updateLocalY();
		SVProjectHandler::instance().setModified(SVProjectHandler::GridModified);
	}
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
	else if (lineEdit == m_ui->lineEditRotateX_2)
		on_lineEditRotateX_2_editingFinishedSuccessfully();
	else if (lineEdit == m_ui->lineEditRotateY_2)
		on_lineEditRotateY_2_editingFinishedSuccessfully();
	else if (lineEdit == m_ui->lineEditRotateZ_2)
		on_lineEditRotateZ_2_editingFinishedSuccessfully();
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
				if (!vectors_equal<4>(normal, surf->geometry().normal())) {
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
	if (m_ui->stackedWidget->currentIndex() == MT_Align) {
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
				if (cso->m_geometryTransformMode != Vic3D::CoordinateSystemObject::TM_None) {
					cso->m_geometryTransformMode = Vic3D::CoordinateSystemObject::TM_None;
					SVViewStateHandler::instance().m_geometryView->refreshSceneView();
				}
				break;

			case NUM_MT : ; // just to make compiler happy
		}
	}
}

void SVPropEditGeometry::updateTrimmingGrid() {
	if (m_ui->stackedWidget->currentIndex() == MT_Trim && m_trimGrid == nullptr) { //if no trimmingGrid is shown yet
		m_ui->lineEditRotateX_2->setValue(0);
		m_ui->lineEditRotateY_2->setValue(0);
		m_ui->lineEditRotateZ_2->setValue(0);

		std::vector<VICUS::GridPlane> &gridPlanes = SVProjectHandler::instance().viewSettings().m_gridPlanes;
		VICUS::GridPlane gridPlane;
		gridPlane.m_offset = QVector2IBKVector(m_lcsTransform.translation());
		gridPlane.m_localX = QVector2IBKVector(m_lcsTransform.rotation().rotatedVector(IBKVector2QVector(IBKMK::Vector3D(1, 0, 0 )))).normalized();
		gridPlane.m_normal = QVector2IBKVector(m_lcsTransform.rotation().rotatedVector(IBKVector2QVector(IBKMK::Vector3D(0, 1, 0 )))).normalized();
		gridPlane.updateLocalY();
		gridPlanes.push_back(gridPlane);
		m_trimGrid = &gridPlanes.back();
		m_previousRotation = VICUS::GridPlane(*m_trimGrid);

		SVProjectHandler::instance().setModified(SVProjectHandler::GridModified);

	} else if (m_ui->stackedWidget->currentIndex() != MT_Trim && m_trimGrid != nullptr) {
		std::vector<VICUS::GridPlane> &gridPlanes = SVProjectHandler::instance().viewSettings().m_gridPlanes;
		gridPlanes.erase(std::remove(gridPlanes.begin(), gridPlanes.end(), *m_trimGrid), gridPlanes.end());
		m_trimGrid = nullptr;

		SVProjectHandler::instance().setModified(SVProjectHandler::GridModified);
	}
}

void SVPropEditGeometry::updateTrimmingGridLcs() {
	if (m_trimGrid != nullptr) {
		m_trimGrid->m_offset = QVector2IBKVector(m_lcsTransform.translation());
		m_trimGrid->updateLocalY();
		SVProjectHandler::instance().setModified(SVProjectHandler::GridModified);
	}
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

			modS.setPolygon3D((VICUS::Polygon3D)poly);
			modS.setSubSurfaces(modSubs);
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
			Q_ASSERT(newSurf.subSurfaces().size() == newSurf.geometry().holes().size());

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
		modifiedSurfaces.push_back(newSurf);
	}


	// TODO : Netzwerk zeugs

	// in case operation was executed without any selected objects - should be prevented
	if (modifiedSurfaces.empty())
		return;

	SVUndoModifySurfaceGeometry * undo = new SVUndoModifySurfaceGeometry(tr("Geometry modified"), modifiedSurfaces );
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
	m_trimGrid->m_localX = IBKMK::Vector3D(1, 0, 0 );
	m_trimGrid->m_normal = IBKMK::Vector3D(0, 0, 1 );
	m_trimGrid->updateLocalY();
	SVProjectHandler::instance().setModified(SVProjectHandler::GridModified);
}


void SVPropEditGeometry::on_pushButtonTrimGridYZ_clicked() {
	m_trimGrid->m_localX = IBKMK::Vector3D(0, 1, 0 );
	m_trimGrid->m_normal = IBKMK::Vector3D(1, 0, 0 );
	m_trimGrid->updateLocalY();
	SVProjectHandler::instance().setModified(SVProjectHandler::GridModified);
}


void SVPropEditGeometry::on_pushButtonTrimGridXZ_clicked() {
	m_trimGrid->m_localX = IBKMK::Vector3D(1, 0, 0 );
	m_trimGrid->m_normal = IBKMK::Vector3D(0, 1, 0 );
	m_trimGrid->updateLocalY();
	SVProjectHandler::instance().setModified(SVProjectHandler::GridModified);
}

void SVPropEditGeometry::on_pushButtonTrimGridLocalXY_clicked() {
	m_ui->lineEditRotateX_2->setValue(0);
	m_ui->lineEditRotateY_2->setValue(0);
	m_ui->lineEditRotateZ_2->setValue(0);
	m_trimGrid->m_localX = QVector2IBKVector(m_lcsTransform.rotation().rotatedVector(IBKVector2QVector(IBKMK::Vector3D(1, 0, 0 )))).normalized();
	m_trimGrid->m_normal = QVector2IBKVector(m_lcsTransform.rotation().rotatedVector(IBKVector2QVector(IBKMK::Vector3D(0, 0, 1 )))).normalized();
	m_trimGrid->updateLocalY();
	m_previousRotation = VICUS::GridPlane(*m_trimGrid);
	SVProjectHandler::instance().setModified(SVProjectHandler::GridModified);
}


void SVPropEditGeometry::on_pushButtonTrimGridLocalYZ_clicked() {
	m_ui->lineEditRotateX_2->setValue(0);
	m_ui->lineEditRotateY_2->setValue(0);
	m_ui->lineEditRotateZ_2->setValue(0);
	m_trimGrid->m_localX = QVector2IBKVector(m_lcsTransform.rotation().rotatedVector(IBKVector2QVector(IBKMK::Vector3D(0, 1, 0 )))).normalized();
	m_trimGrid->m_normal = QVector2IBKVector(m_lcsTransform.rotation().rotatedVector(IBKVector2QVector(IBKMK::Vector3D(1, 0, 0 )))).normalized();
	m_trimGrid->updateLocalY();
	m_previousRotation = VICUS::GridPlane(*m_trimGrid);
	SVProjectHandler::instance().setModified(SVProjectHandler::GridModified);
}


void SVPropEditGeometry::on_pushButtonTrimGridLocalXZ_clicked() {
	m_ui->lineEditRotateX_2->setValue(0);
	m_ui->lineEditRotateY_2->setValue(0);
	m_ui->lineEditRotateZ_2->setValue(0);
	m_trimGrid->m_localX = QVector2IBKVector(m_lcsTransform.rotation().rotatedVector(IBKVector2QVector(IBKMK::Vector3D(1, 0, 0 )))).normalized();
	m_trimGrid->m_normal = QVector2IBKVector(m_lcsTransform.rotation().rotatedVector(IBKVector2QVector(IBKMK::Vector3D(0, 1, 0 )))).normalized();
	m_trimGrid->updateLocalY();
	m_previousRotation = VICUS::GridPlane(*m_trimGrid);
	SVProjectHandler::instance().setModified(SVProjectHandler::GridModified);
}


void SVPropEditGeometry::on_pushButtonTrimPolygons_clicked() {
	if (m_trimGrid != nullptr) {

		std::vector<IBKMK::Vector3D> trimGridPoly;
		trimGridPoly.push_back(m_trimGrid->m_offset);
		trimGridPoly.push_back(m_trimGrid->m_offset + m_trimGrid->m_localX);
		trimGridPoly.push_back(m_trimGrid->m_offset + m_trimGrid->localY());

		std::set<const VICUS::Object*> sel;
		project().selectObjects(sel, VICUS::Project::SelectionGroups(0x005), true, true);
		for (const VICUS::Object* o : sel) {
			if (dynamic_cast<const VICUS::Surface*>(o) != nullptr) {


				std::vector<IBKMK::Vector3D> polyOne = dynamic_cast<const VICUS::Surface*>(o)->polygon3D().vertexes();
				std::vector<IBKMK::Vector3D> polyTwo = trimGridPoly;

				std::vector<std::vector<IBKMK::Vector3D>> polyInput;
				polyInput.push_back(polyOne);

				bool t = IBKMK::polyTrim(polyInput, polyTwo);


				VICUS::Surface s;
				for (std::vector<IBKMK::Vector3D> entry : polyInput) {

					unsigned int nextId = project().nextUnusedID();
					s.m_id = nextId;
					s.m_displayName = "test";
					s.setPolygon3D(IBKMK::Polygon3D(entry));

					s.m_displayColor = s.m_color = QColor("#206000");
					// modify project
					SVUndoAddSurface * undo = new SVUndoAddSurface(tr("Added surface '%1'").arg(s.m_displayName), s, 0);
					undo->push();
				}
				qInfo() << (t ? "trueTrim7" : "falseTrim");



				continue;
			}
		}





	} else IBK::IBK_Message("Invalid mode to perform trimming!", IBK::MSG_ERROR);
}


void SVPropEditGeometry::on_pushButtonApplyRotation_clicked() {
	m_previousRotation = VICUS::GridPlane(*m_trimGrid);
	m_ui->lineEditRotateX_2->setValue(0);
	m_ui->lineEditRotateY_2->setValue(0);
	m_ui->lineEditRotateZ_2->setValue(0);
}

