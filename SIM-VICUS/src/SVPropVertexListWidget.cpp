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

#include "SVPropVertexListWidget.h"
#include "ui_SVPropVertexListWidget.h"

#include <QMessageBox>
#include <QInputDialog>

#include <IBK_physics.h>

#include <IBKMK_Vector3D.h>
#include <IBKMK_Triangulation.h>

#include <QtExt_LanguageHandler.h>
#include <QtExt_Conversions.h>

#include <VICUS_Project.h>
#include <VICUS_KeywordList.h>
#include <VICUS_ComponentInstance.h>
#include <VICUS_Polygon3D.h>

#include "SVProjectHandler.h"
#include "SVViewStateHandler.h"
#include "SVUndoAddSurface.h"
#include "SVGeometryView.h"
#include "SVSettings.h"
#include "SVMainWindow.h"
#include "SVUndoAddBuilding.h"
#include "SVUndoAddBuildingLevel.h"
#include "SVUndoAddZone.h"

#include "Vic3DNewGeometryObject.h"
#include "Vic3DCoordinateSystemObject.h"


SVPropVertexListWidget::SVPropVertexListWidget(QWidget *parent) :
	QWidget(parent),
	m_ui(new Ui::SVPropVertexListWidget)
{
	m_ui->setupUi(this);
	m_ui->verticalLayout->setMargin(0);
	for (int i=0; i<4; ++i)
		m_ui->stackedWidget->widget(i)->layout()->setMargin(0);

	m_ui->lineEditZoneHeight->setup(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max(),
									tr("Zone height in [m]."),true, true);

	SVViewStateHandler::instance().m_propVertexListWidget = this;

	on_radioButtonRoofHeight_toggled(m_ui->radioButtonRoofHeight->isChecked());
	on_checkBoxFlapTile_toggled(m_ui->checkBoxFlapTile->isChecked());

	connect(&SVProjectHandler::instance(), &SVProjectHandler::modified,
			this, &SVPropVertexListWidget::onModified);

	connect(m_ui->pushButtonCancel1, &QPushButton::clicked, this, &SVPropVertexListWidget::onCancel);
	connect(m_ui->pushButtonCancel2, &QPushButton::clicked, this, &SVPropVertexListWidget::onCancel);
	connect(m_ui->pushButtonCancel3, &QPushButton::clicked, this, &SVPropVertexListWidget::onCancel);
	connect(m_ui->pushButtonCancel4, &QPushButton::clicked, this, &SVPropVertexListWidget::onCancel);

	connect(m_ui->toolButtonAddBuilding2, &QToolButton::clicked, this, &SVPropVertexListWidget::on_toolButtonAddBuilding_clicked);
	connect(m_ui->toolButtonAddBuilding3, &QToolButton::clicked, this, &SVPropVertexListWidget::on_toolButtonAddBuilding_clicked);

	connect(m_ui->toolButtonAddBuildingLevel2, &QToolButton::clicked, this, &SVPropVertexListWidget::on_toolButtonAddBuildingLevel_clicked);
	connect(m_ui->toolButtonAddBuildingLevel3, &QToolButton::clicked, this, &SVPropVertexListWidget::on_toolButtonAddBuildingLevel_clicked);

	connect(m_ui->toolButtonEditComponents1, &QToolButton::clicked, this, &SVPropVertexListWidget::onEditComponents);
	connect(m_ui->toolButtonEditComponents2, &QToolButton::clicked, this, &SVPropVertexListWidget::onEditComponents);
	connect(m_ui->toolButtonEditComponents3, &QToolButton::clicked, this, &SVPropVertexListWidget::onEditComponents);
	connect(m_ui->toolButtonEditComponents4, &QToolButton::clicked, this, &SVPropVertexListWidget::onEditComponents);
	connect(m_ui->toolButtonEditComponents5, &QToolButton::clicked, this, &SVPropVertexListWidget::onEditComponents);
	connect(m_ui->toolButtonEditComponents7, &QToolButton::clicked, this, &SVPropVertexListWidget::onEditComponents);
	connect(m_ui->toolButtonEditComponents8, &QToolButton::clicked, this, &SVPropVertexListWidget::onEditComponents);
}


SVPropVertexListWidget::~SVPropVertexListWidget() {
	delete m_ui;
}


void SVPropVertexListWidget::setup(int newGeometryType) {
	// switch to vertex list widget
	m_ui->stackedWidget->setCurrentIndex(0);
	// clear vertex table widget and disable "delete" and "finish" buttons
	m_ui->tableWidgetVertexes->setRowCount(0);
	m_ui->pushButtonCompletePolygon->setEnabled(false);
	m_ui->pushButtonDeleteLast->setEnabled(false);
	m_ui->pushButtonDeleteSelected->setEnabled(false);

	// initialize new geometry object
	switch ((Vic3D::NewGeometryObject::NewGeometryMode)newGeometryType) {
		case Vic3D::NewGeometryObject::NGM_Rect :
			SVViewStateHandler::instance().m_newGeometryObject->startNewGeometry(Vic3D::NewGeometryObject::NGM_Rect);
		break;

		case Vic3D::NewGeometryObject::NGM_Polygon :
		case Vic3D::NewGeometryObject::NGM_Zone :
		case Vic3D::NewGeometryObject::NGM_Roof :
			SVViewStateHandler::instance().m_newGeometryObject->startNewGeometry(Vic3D::NewGeometryObject::NGM_Polygon);
		break;

		case Vic3D::NewGeometryObject::NUM_NGM: ; // just for the compiler
	}
	m_geometryMode = newGeometryType;
}




void SVPropVertexListWidget::updateComponentComboBoxes() {
	updateComponentComboBox(m_ui->comboBoxComponent, -1);
	updateComponentComboBox(m_ui->comboBoxComponentWalls, 0);
	updateComponentComboBox(m_ui->comboBoxComponentFloor, 1);
	updateComponentComboBox(m_ui->comboBoxComponentCeiling, 2);

	updateComponentComboBox(m_ui->comboBoxComponentWall3, 0);
	updateComponentComboBox(m_ui->comboBoxComponentFloor3, 1);
	updateComponentComboBox(m_ui->comboBoxComponentRoof3, 2);
}


void SVPropVertexListWidget::addVertex(const IBKMK::Vector3D & p) {
	// Note: the vertex is already in the NewGeometryObject, we only
	//       modify the table widget and update the button enabled states
	int row = m_ui->tableWidgetVertexes->rowCount();
	m_ui->tableWidgetVertexes->setRowCount(row + 1);
	QTableWidgetItem * item = new QTableWidgetItem(QString("%1").arg(row+1));
	item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	m_ui->tableWidgetVertexes->setItem(row,0,item);
	item = new QTableWidgetItem(QString("%L1,%L2,%L3").arg(p.m_x).arg(p.m_y).arg(p.m_z));
	item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	m_ui->tableWidgetVertexes->setItem(row,1,item);

	m_ui->pushButtonDeleteLast->setEnabled(true);

	// we may now switch to another mode
	m_ui->pushButtonCompletePolygon->setEnabled(SVViewStateHandler::instance().m_newGeometryObject->canComplete());
}


void SVPropVertexListWidget::removeVertex(unsigned int idx) {
	// Note: the vertex has already been removed in the NewGeometryObject, we only
	//       modify the table widget and update the button enabled states
	int rows = m_ui->tableWidgetVertexes->rowCount();
	Q_ASSERT(rows > 0);
	Q_ASSERT((int)idx < m_ui->tableWidgetVertexes->rowCount());
	// now remove selected row from table widget
	m_ui->tableWidgetVertexes->removeRow((int)idx);
	m_ui->pushButtonDeleteLast->setEnabled(rows > 1);

	// disable/enable "Complete polygon" button, depending on wether the surface is complete
	m_ui->pushButtonCompletePolygon->setEnabled(SVViewStateHandler::instance().m_newGeometryObject->canComplete());

	// repaint the scene
	SVViewStateHandler::instance().m_geometryView->refreshSceneView();
}


void SVPropVertexListWidget::setZoneHeight(double dist) {
	m_ui->lineEditZoneHeight->blockSignals(true);
	m_ui->lineEditZoneHeight->setText(QString("%L1").arg(dist));
	m_ui->lineEditZoneHeight->blockSignals(false);
	if (!SVViewStateHandler::instance().m_newGeometryObject->m_interactiveZoneExtrusionMode)
		m_ui->pushButtonPickZoneHeight->setChecked(false);
}


bool SVPropVertexListWidget::completePolygonIfPossible() {
	switch (m_ui->stackedWidget->currentIndex()) {
		case 0 :
			if (m_ui->pushButtonCompletePolygon->isEnabled()) {
				m_ui->pushButtonCompletePolygon->click();
				return true;
			}
		break;

		case 1 :
			m_ui->pushButtonCreateSurface->click();
			return true;

		case 2 :
			m_ui->pushButtonCreateZone->click();
			return true;

		case 3 :
			m_ui->pushButtonCreateRoof->click();
			return true;
	}
	return false;
}


// *** SLOTS ***

void SVPropVertexListWidget::onModified(int modificationType, ModificationInfo * /*data*/) {
	SVProjectHandler::ModificationTypes mod = (SVProjectHandler::ModificationTypes)modificationType;
	switch (mod) {
		// We only need to handle changes of the building topology, in all other cases
		// the "create new geometry" action is aborted and the widget will be hidden.
		case SVProjectHandler::BuildingTopologyChanged:
			updateBuildingComboBox(m_ui->comboBoxBuilding);
			updateBuildingLevelsComboBox(m_ui->comboBoxBuildingLevel, m_ui->comboBoxBuilding);
			updateZoneComboBox(m_ui->comboBoxZone, m_ui->comboBoxBuildingLevel);

			updateBuildingComboBox(m_ui->comboBoxBuilding2);
			updateBuildingLevelsComboBox(m_ui->comboBoxBuildingLevel2, m_ui->comboBoxBuilding2);

			updateBuildingComboBox(m_ui->comboBoxBuilding3);
			updateBuildingLevelsComboBox(m_ui->comboBoxBuildingLevel3, m_ui->comboBoxBuilding3);
		break;

		default: {
			// clear the new geometry object
			SVViewStateHandler::instance().m_newGeometryObject->clear();
			// and reset view state, if we are still in vertex list mode
			SVViewState vs = SVViewStateHandler::instance().viewState();
			if (vs.m_propertyWidgetMode == SVViewState::PM_VertexList) {
				vs.m_sceneOperationMode = SVViewState::NUM_OM;
				vs.m_propertyWidgetMode = SVViewState::PM_AddEditGeometry;
				// reset locks
				vs.m_locks = SVViewState::NUM_L;

				// take xy plane out of snap option mask
				vs.m_snapEnabled = true;
				// now tell all UI components to toggle their view state
				SVViewStateHandler::instance().setViewState(vs);
			}
		}
	}
}


void SVPropVertexListWidget::on_pushButtonDeleteLast_clicked() {
	// remove last vertex from polygon
	Vic3D::NewGeometryObject * po = SVViewStateHandler::instance().m_newGeometryObject;
	po->removeLastVertex();
}


void SVPropVertexListWidget::on_tableWidgetVertexes_itemSelectionChanged() {
	m_ui->pushButtonDeleteSelected->setEnabled( m_ui->tableWidgetVertexes->currentRow() != -1);
}


void SVPropVertexListWidget::on_pushButtonDeleteSelected_clicked() {
	int currentRow = m_ui->tableWidgetVertexes->currentRow();
	Q_ASSERT(currentRow != -1);
	// remove selected vertex from polygon
	Vic3D::NewGeometryObject * po = SVViewStateHandler::instance().m_newGeometryObject;
	po->removeVertex((unsigned int)currentRow); // this will in turn call removeVertex() above
}


void SVPropVertexListWidget::on_pushButtonCompletePolygon_clicked() {
	Vic3D::NewGeometryObject * po = SVViewStateHandler::instance().m_newGeometryObject;
	// switch to different stacked widget, depending on geometry to be created
	switch ((Vic3D::NewGeometryObject::NewGeometryMode)m_geometryMode) {
		case Vic3D::NewGeometryObject::NGM_Rect:
		case Vic3D::NewGeometryObject::NGM_Polygon:
			m_ui->stackedWidget->setCurrentIndex(1);
			updateBuildingComboBox(m_ui->comboBoxBuilding);
			updateBuildingLevelsComboBox(m_ui->comboBoxBuildingLevel, m_ui->comboBoxBuilding);
			updateZoneComboBox(m_ui->comboBoxZone, m_ui->comboBoxBuildingLevel);
			updateComponentComboBoxes(); // update all component combo boxes in surface page
			m_ui->lineEditName->setText(tr("Surface"));
			po->m_passiveMode = true; // disallow changes to surface geometry
		break;

		case Vic3D::NewGeometryObject::NGM_Zone:
			m_ui->stackedWidget->setCurrentIndex(2);
			updateBuildingComboBox(m_ui->comboBoxBuilding2);
			updateBuildingLevelsComboBox(m_ui->comboBoxBuildingLevel2, m_ui->comboBoxBuilding2);

			updateComponentComboBoxes(); // update all component combo boxes in zone page
			po->setNewGeometryMode(Vic3D::NewGeometryObject::NGM_Zone);
			// transfer zone height into line edit, if we have already a building level defined
			on_comboBoxBuildingLevel2_currentIndexChanged(0); // index argument does not matter, not used
			on_lineEditZoneHeight_editingFinishedSuccessfully();
			m_ui->lineEditNameZone->setText(tr("Room"));
		break;

		case Vic3D::NewGeometryObject::NGM_Roof: {
			m_ui->stackedWidget->setCurrentIndex(3);
			updateBuildingComboBox(m_ui->comboBoxBuilding3);
			updateBuildingLevelsComboBox(m_ui->comboBoxBuildingLevel3, m_ui->comboBoxBuilding3);
			updateComponentComboBoxes(); // update all component combo boxes in roof page
			const VICUS::PlaneGeometry & pg = po->planeGeometry();
			if (pg.polygon().type() != IBKMK::Polygon3D::T_Rectangle)
				m_ui->comboBoxRoofType->setCurrentIndex(4); // not a rectangle, select complex roof
			po->setNewGeometryMode(Vic3D::NewGeometryObject::NGM_Roof);
			m_ui->lineEditNameRoof->setText(tr("Roof"));

			updateRoofGeometry();
		}
		break;
		case Vic3D::NewGeometryObject::NUM_NGM: ; // just for the compiler
	}

}


void SVPropVertexListWidget::onCancel() {
	// reset new polygon object, so that it won't be drawn anylonger
	SVViewStateHandler::instance().m_newGeometryObject->clear();
	// signal, that we are no longer in "add vertex" mode
	SVViewState vs = SVViewStateHandler::instance().viewState();
	vs.m_sceneOperationMode = SVViewState::NUM_OM;
	vs.m_propertyWidgetMode = SVViewState::PM_AddEditGeometry;
	// reset locks
	vs.m_locks = SVViewState::NUM_L;

	// take xy plane out of snap option mask
	vs.m_snapEnabled = true;
	// now tell all UI components to toggle their view state
	SVViewStateHandler::instance().setViewState(vs);
}


void SVPropVertexListWidget::onEditComponents() {
	// ask main window to show database dialog, afterwards update component combos
	SVMainWindow::instance().on_actionDBComponents_triggered();
	// Note: SVMainWindow::instance().on_actionDBComponents_triggered() calls updateComponentCombos() itself, so
	//       no need to call this here
}


void SVPropVertexListWidget::on_toolButtonAddBuilding_clicked() {
	std::set<QString> existingNames;
	for (const VICUS::Building & b : project().m_buildings)
		existingNames.insert(b.m_displayName);
	QString defaultName = VICUS::Project::uniqueName(tr("Building"), existingNames);
	QString text = QInputDialog::getText(this, tr("Add building"), tr("New building name:"), QLineEdit::Normal, defaultName).trimmed();
	if (text.isEmpty()) return;
	// modify project
	VICUS::Building b;
	b.m_id = VICUS::Project::uniqueId(project().m_buildings);
	b.m_displayName = text;
	SVUndoAddBuilding * undo = new SVUndoAddBuilding(tr("Adding building '%1'").arg(b.m_displayName), b, true);
	undo->push(); // this will update our combo boxes

	// now also select the matching item
	if (sender() == m_ui->toolButtonAddBuilding)
		reselectById(m_ui->comboBoxBuilding, (int)b.uniqueID());
	else if (sender() == m_ui->toolButtonAddBuilding2)
		reselectById(m_ui->comboBoxBuilding2, (int)b.uniqueID());
	else if (sender() == m_ui->toolButtonAddBuilding3)
		reselectById(m_ui->comboBoxBuilding3, (int)b.uniqueID());
	else {
		Q_ASSERT(false);
	}
}


void SVPropVertexListWidget::on_toolButtonAddBuildingLevel_clicked() {
	QComboBox * buildingCombo;
	QComboBox * buildingLevelCombo;
	if (sender() == m_ui->toolButtonAddBuildingLevel) {
		buildingCombo = m_ui->comboBoxBuilding;
		buildingLevelCombo = m_ui->comboBoxBuildingLevel;
	}
	else if (sender() == m_ui->toolButtonAddBuildingLevel2) {
		buildingCombo = m_ui->comboBoxBuilding2;
		buildingLevelCombo = m_ui->comboBoxBuildingLevel2;
	}
	else if (sender() == m_ui->toolButtonAddBuildingLevel3) {
		buildingCombo = m_ui->comboBoxBuilding3;
		buildingLevelCombo = m_ui->comboBoxBuildingLevel3;
	}
	else {
		Q_ASSERT(false);
	}

	// get currently selected building
	unsigned int buildingUniqueID = buildingCombo->currentData().toUInt();
	const VICUS::Building * b = dynamic_cast<const VICUS::Building*>(project().objectById(buildingUniqueID));
	Q_ASSERT(b != nullptr);

	std::set<QString> existingNames;
	for (const VICUS::BuildingLevel & bl : b->m_buildingLevels)
		existingNames.insert(bl.m_displayName);
	QString defaultName = VICUS::Project::uniqueName(tr("Level"), existingNames);
	QString text = QInputDialog::getText(this, tr("Add building level"), tr("New building level/floor name:"), QLineEdit::Normal, defaultName).trimmed();
	if (text.isEmpty()) return;

	// modify project
	VICUS::BuildingLevel bl;
	bl.m_id = VICUS::Project::uniqueId(b->m_buildingLevels);
	bl.m_displayName = text;
	SVUndoAddBuildingLevel * undo = new SVUndoAddBuildingLevel(tr("Adding building level '%1'").arg(bl.m_displayName), buildingUniqueID, bl, true);
	undo->push(); // this will update our combo boxes

	// now also select the matching item
	reselectById(buildingLevelCombo, (int)bl.uniqueID());
}


void SVPropVertexListWidget::on_toolButtonAddZone_clicked() {
	// get currently selected building
	unsigned int buildingLevelUniqueID = m_ui->comboBoxBuildingLevel->currentData().toUInt();
	const VICUS::BuildingLevel * bl = dynamic_cast<const VICUS::BuildingLevel*>(project().objectById(buildingLevelUniqueID));
	Q_ASSERT(bl != nullptr);

	std::set<QString> existingNames;
	for (const VICUS::Room & r : bl->m_rooms)
		existingNames.insert(r.m_displayName);
	QString defaultName = VICUS::Project::uniqueName(tr("Room"), existingNames);
	QString text = QInputDialog::getText(this, tr("Add room/zone"), tr("New room/zone name:"), QLineEdit::Normal, defaultName).trimmed();
	if (text.isEmpty()) return;

	// modify project
	VICUS::Room r;
	r.m_id = VICUS::Project::uniqueId(bl->m_rooms);
	r.m_displayName = text;
	SVUndoAddZone * undo = new SVUndoAddZone(tr("Adding building zone '%1'").arg(r.m_displayName), buildingLevelUniqueID, r, true);
	undo->push(); // this will update our combo boxes

	// now also select the matching item
	reselectById(m_ui->comboBoxZone, (int)r.uniqueID());
}


void SVPropVertexListWidget::on_checkBoxAnnonymousGeometry_stateChanged(int /*arg1*/) {
	updateSurfacePageState();
}


void SVPropVertexListWidget::on_comboBoxBuilding_currentIndexChanged(int /*index*/) {
	updateBuildingLevelsComboBox(m_ui->comboBoxBuildingLevel, m_ui->comboBoxBuilding);
	updateZoneComboBox(m_ui->comboBoxZone, m_ui->comboBoxBuildingLevel);
}


void SVPropVertexListWidget::on_comboBoxBuildingLevel_currentIndexChanged(int /*index*/) {
	updateZoneComboBox(m_ui->comboBoxZone, m_ui->comboBoxBuildingLevel);
	if (m_ui->comboBoxBuildingLevel->count() == 0)
		return;
	unsigned int buildingLevelUniqueID = m_ui->comboBoxBuildingLevel->currentData().toUInt();
	const VICUS::BuildingLevel * bl = dynamic_cast<const VICUS::BuildingLevel*>(project().objectById(buildingLevelUniqueID));
	// also transfer nominal height into zone-height line edit
	if (bl != nullptr) {
		m_ui->lineEditZoneHeight->setValue(bl->m_height);
		// only trigger zone height editing finished, when we are in new vertex mode
		// Mind: widget may be hidden
		SVViewState vs = SVViewStateHandler::instance().viewState();
		if (vs.m_sceneOperationMode == SVViewState::OM_PlaceVertex)
			on_lineEditZoneHeight_editingFinishedSuccessfully();
	}
}


void SVPropVertexListWidget::on_pushButtonCreateSurface_clicked() {
	if (m_ui->lineEditName->text().trimmed().isEmpty()) {
		QMessageBox::critical(this, QString(), tr("Please enter a descriptive name!"));
		m_ui->lineEditName->selectAll();
		m_ui->lineEditName->setFocus();
		return;
	}
	// depending on the type of geometry that's being created,
	// perform additional checks
	Vic3D::NewGeometryObject * po = SVViewStateHandler::instance().m_newGeometryObject;
	IBK_ASSERT(po->m_passiveMode == true);
	IBK_ASSERT(po->newGeometryMode() == Vic3D::NewGeometryObject::NGM_Rect ||
			   po->newGeometryMode() == Vic3D::NewGeometryObject::NGM_Polygon);

	// compose a surface object based on the current content of the new polygon object
	VICUS::Surface s;
	s.m_displayName = m_ui->lineEditName->text().trimmed();
	s.setPolygon3D( po->planeGeometry().polygon() );

	// we need all properties, unless we create annonymous geometry
	if (m_ui->checkBoxAnnonymousGeometry->isChecked()) {
		s.m_color = QColor("#206000");
		s.m_id = VICUS::Project::uniqueId(project().m_plainGeometry);
		// modify project
		SVUndoAddSurface * undo = new SVUndoAddSurface(tr("Added surface '%1'").arg(s.m_displayName), s, 0);
		undo->push();
	}
	else {
		// we need inputs for room (if there is a room, there is also a building and level)
		if (m_ui->comboBoxZone->currentIndex() == -1) {
			QMessageBox::critical(this, QString(), tr("First select a zone to add the surface to!"));
			return;
		}
		unsigned int zoneUUID = m_ui->comboBoxZone->currentData().toUInt();
		Q_ASSERT(zoneUUID != 0);

		s.initializeColorBasedOnInclination(); // set color based on orientation
		// the surface will get the unique ID as persistant ID
		s.m_id = s.uniqueID();
		// also store component information
		VICUS::ComponentInstance compInstance;
		compInstance.m_id = VICUS::Project::uniqueId(project().m_componentInstances);
		compInstance.m_componentID = m_ui->comboBoxComponent->currentData().toUInt();
		// for now we assume that the zone's surface is connected to the b-side of the component
		compInstance.m_sideBSurfaceID = s.m_id;
		// modify project
		SVUndoAddSurface * undo = new SVUndoAddSurface(tr("Added surface '%1'").arg(s.m_displayName), s, zoneUUID, &compInstance);
		undo->push();
	}
}


void SVPropVertexListWidget::on_lineEditZoneHeight_editingFinishedSuccessfully() {
	// Guard against call when aborting/focus is lost during undo!
	Vic3D::NewGeometryObject * po = SVViewStateHandler::instance().m_newGeometryObject;
	if (po->newGeometryMode() != Vic3D::NewGeometryObject::NGM_Zone)
		return;

	// read entered line height and if valid set new height in scene view (and move local coordinate system accordingly)
	double val = m_ui->lineEditZoneHeight->value();
	po->setZoneHeight(val);
	// we need to trigger a redraw here
	SVViewStateHandler::instance().m_geometryView->refreshSceneView();
}


void SVPropVertexListWidget::on_pushButtonPickZoneHeight_clicked() {
	// enable interactive zone extrusion mode
	Vic3D::NewGeometryObject * po = SVViewStateHandler::instance().m_newGeometryObject;
	// check if interactive mode is already enabled
	po->m_interactiveZoneExtrusionMode = !po->m_interactiveZoneExtrusionMode;
}


void SVPropVertexListWidget::on_comboBoxBuilding2_currentIndexChanged(int /*index*/) {
	updateBuildingLevelsComboBox(m_ui->comboBoxBuildingLevel2, m_ui->comboBoxBuilding2);
}


void SVPropVertexListWidget::on_comboBoxBuildingLevel2_currentIndexChanged(int /*index*/) {
	if (m_ui->comboBoxBuildingLevel2->count() == 0)
		return;
	unsigned int buildingLevelUniqueID = m_ui->comboBoxBuildingLevel2->currentData().toUInt();
	const VICUS::BuildingLevel * bl = dynamic_cast<const VICUS::BuildingLevel*>(project().objectById(buildingLevelUniqueID));
	// also transfer nominal height into zone-height line edit
	if (bl != nullptr) {
		m_ui->lineEditZoneHeight->setValue(bl->m_height);
		// only trigger zone height editing finished, when we are in new vertex mode
		// Mind: widget may be hidden
		SVViewState vs = SVViewStateHandler::instance().viewState();
		if (vs.m_sceneOperationMode == SVViewState::OM_PlaceVertex)
			on_lineEditZoneHeight_editingFinishedSuccessfully();
	}
}


void SVPropVertexListWidget::on_pushButtonCreateZone_clicked() {
	// we need a building level
	if (m_ui->comboBoxBuildingLevel2->currentIndex() == -1) {
		QMessageBox::critical(this, QString(), tr("First select a building level to add the zone/room to!"));
		return;
	}
	// tricky part starts now
	// 1. we need to get a list of surfaces and make their normal vectors point outwards
	// 2. we need to assign colors to the surfaces and default components based on
	//    inclination
	// 3. we need to create an undo-action

	// get floor and ceiling polygons from geometry object

	// take the polygon
	Vic3D::NewGeometryObject * po = SVViewStateHandler::instance().m_newGeometryObject;
	VICUS::Polygon3D floor = po->planeGeometry().polygon();
	IBK_ASSERT(po->generatedGeometry().size() == 1);
	VICUS::Polygon3D ceiling = po->generatedGeometry()[0].polygon();
	// Note: both polygons still have the same normal vector!

	// compute offset vector
	IBKMK::Vector3D offset = ceiling.vertexes()[0] - floor.vertexes()[0];
	// now check if ceiling is offset in same direction as normal vector of floor plane?
	double dotProduct = offset.scalarProduct(floor.normal());
	if (dotProduct > 0) {
		// same direction, we need to reverse floor polygon
		floor.flip();
	}
	else {
		// opposite direction, we need to reverse the ceiling polygon
		ceiling.flip();
	}

	std::vector<VICUS::ComponentInstance> componentInstances;
	VICUS::Room r;
	r.m_displayName = m_ui->lineEditNameZone->text().trimmed();
	// now we can create the surfaces for top and bottom
	// compose a surface object based on the current content of the new polygon object
	VICUS::Surface sFloor;
	sFloor.m_displayName = tr("Floor");
	sFloor.m_id = sFloor.uniqueID();
	VICUS::Surface sCeiling;
	sCeiling.m_displayName = tr("Ceiling");
	sCeiling.m_id = sCeiling.uniqueID();
	// if the ceiling has a normal vector pointing up, we take it as ceiling, otherwise it's going to be the floor
	if (IBKMK::Vector3D(0,0,1).scalarProduct(ceiling.normal()) > 0) {
		sCeiling.setPolygon3D(ceiling);
		sFloor.setPolygon3D(floor);
	}
	else {
		sCeiling.setPolygon3D(floor);
		sFloor.setPolygon3D(ceiling);
	}

	sFloor.initializeColorBasedOnInclination();
	// get the smallest yet free ID for component instances/construction instances
	unsigned int conInstID = VICUS::Project::largestUniqueId(project().m_componentInstances);
	// Note: surface is attached to "Side A"
	componentInstances.push_back(VICUS::ComponentInstance(++conInstID,
		 m_ui->comboBoxComponentFloor->currentData().toUInt(), sFloor.m_id, VICUS::INVALID_ID));

	sCeiling.initializeColorBasedOnInclination();
	// Note: surface is attached to "Side A"
	componentInstances.push_back(VICUS::ComponentInstance(++conInstID,
		 m_ui->comboBoxComponentCeiling->currentData().toUInt(), sCeiling.m_id, VICUS::INVALID_ID));

	r.m_id = r.uniqueID();
	r.m_surfaces.push_back(sFloor);
	r.m_surfaces.push_back(sCeiling);

	// now loop around the circle and create planes for wall segments
	// we take the floor polygon

	unsigned int nVert = floor.vertexes().size();
	unsigned int wallComponentID = m_ui->comboBoxComponentWalls->currentData().toUInt();
	for (unsigned int i=0; i<nVert; ++i) {
		// mind the winding order
		// when looked from above, floor vertexes go clock-wise,
		// and ceiling vertices go anti-clockwise
		unsigned int vIdx2 = (i+1) % nVert;

		IBKMK::Vector3D p0 = floor.vertexes()[ vIdx2 ];
		IBKMK::Vector3D p1 = floor.vertexes()[ i ];
		IBKMK::Vector3D p2 = floor.vertexes()[ vIdx2 ] + offset;	//take offset as last point for rectangle; rounding errors by vector-sum?

		VICUS::Surface sWall;
		sWall.m_id = sWall.uniqueID();
		sWall.m_displayName = tr("Wall %1").arg(i+1);
		sWall.setPolygon3D( VICUS::Polygon3D(VICUS::Polygon3D::T_Rectangle, p0, p1, p2) );
		sWall.initializeColorBasedOnInclination();
		// wall surface is attached to "Side A"
		componentInstances.push_back(VICUS::ComponentInstance(++conInstID,
													  wallComponentID, sWall.m_id, VICUS::INVALID_ID));

		r.m_surfaces.push_back(sWall);
	}

	double area = sFloor.geometry().area();
	VICUS::KeywordList::setParameter(r.m_para, "Room::para_t", VICUS::Room::P_Area, area);
	VICUS::KeywordList::setParameter(r.m_para, "Room::para_t", VICUS::Room::P_Volume, area*offset.magnitude());

	// transfer default colors
	for (VICUS::Surface & s : r.m_surfaces)
		s.m_color = s.m_displayColor;

	// now create the undo action
	unsigned int buildingLevelUid = m_ui->comboBoxBuildingLevel2->currentData().toUInt();
	Q_ASSERT(buildingLevelUid != 0);
	SVUndoAddZone * undo = new SVUndoAddZone(tr("Adding new zone '%1'").arg(r.m_displayName),
											 buildingLevelUid,
											 r, false, &componentInstances);
	undo->push();
}


void SVPropVertexListWidget::on_comboBoxBuilding3_currentIndexChanged(int /*index*/) {
	updateBuildingLevelsComboBox(m_ui->comboBoxBuildingLevel3, m_ui->comboBoxBuilding3);
}


void SVPropVertexListWidget::on_comboBoxBuildingLevel3_currentIndexChanged(int /*index*/) {
	if (m_ui->comboBoxBuildingLevel3->count() == 0)
		return;
	unsigned int buildingLevelUniqueID = m_ui->comboBoxBuildingLevel3->currentData().toUInt();
	const VICUS::BuildingLevel * bl = dynamic_cast<const VICUS::BuildingLevel*>(project().objectById(buildingLevelUniqueID));
	// also transfer nominal height into zone-height line edit
	if (bl != nullptr) {
		m_ui->lineEditRoofHeight->setValue(bl->m_height);
		// only trigger zone height editing finished, when we are in new vertex mode
		// Mind: widget may be hidden
		SVViewState vs = SVViewStateHandler::instance().viewState();
		if (vs.m_sceneOperationMode == SVViewState::OM_PlaceVertex)
			on_lineEditRoofHeight_editingFinishedSuccessfully();
	}
}


void SVPropVertexListWidget::on_lineEditRoofHeight_editingFinishedSuccessfully() {
	// Guard against call when aborting/focus is lost during undo!
	Vic3D::NewGeometryObject * po = SVViewStateHandler::instance().m_newGeometryObject;
	if (po->newGeometryMode() != Vic3D::NewGeometryObject::NGM_Roof)
		return;

	updateRoofGeometry();
	//TODO hole geometrie
}


void SVPropVertexListWidget::on_comboBoxRoofType_currentIndexChanged(int /*index*/) {
	updateRoofGeometry();
}


void SVPropVertexListWidget::on_radioButtonRoofHeight_toggled(bool checked) {
	m_ui->lineEditRoofHeight->setEnabled(checked);
	m_ui->lineEditRoofInclination->setEnabled(!checked);
	updateRoofGeometry();
}


void SVPropVertexListWidget::on_checkBoxFlapTile_toggled(bool checked) {
	m_ui->lineEditFlapTileHeight->setEnabled(checked);
	updateRoofGeometry();
}


void SVPropVertexListWidget::on_pushButtonCreateRoof_clicked() {
	// we need a building level
	if (m_ui->comboBoxBuildingLevel3->currentIndex() == -1) {
		QMessageBox::critical(this, QString(), tr("First select a building level to add the roof zone to!"));
		return;
	}

	// get floor polygon from geometry object
	Vic3D::NewGeometryObject * po = SVViewStateHandler::instance().m_newGeometryObject;
	const VICUS::Polygon3D & floor = po->planeGeometry().polygon();

	// generate floor surface (no component assigned!)
	VICUS::Room r;
	r.m_displayName = m_ui->lineEditNameRoof->text().trimmed();
	// now we can create the surfaces for top and bottom
	// compose a surface object based on the current content of the new polygon object
	VICUS::Surface sFloor;
	sFloor.m_displayName = tr("Floor");
	sFloor.m_id = sFloor.uniqueID();
	sFloor.setPolygon3D(floor);
	sFloor.m_displayColor = QColor(150,50,20,255);	//for floor

	r.m_id = r.uniqueID();
	r.m_surfaces.push_back(sFloor);

	std::vector<VICUS::ComponentInstance> componentInstances;
	unsigned int compInstID = VICUS::Project::largestUniqueId(project().m_componentInstances);
	// now process all other generated surfaces and create roof surfaces
	unsigned int roofSurfaceCount = 0;
	unsigned int wallCount = 0;
	for (unsigned int i=0; i<po->generatedGeometry().size(); ++i) {
		VICUS::Surface sRoof;
		sRoof.m_displayName = tr("Wall surface");//.arg(++roofSurfaceCount);
		sRoof.m_id = sRoof.uniqueID();
		sRoof.setPolygon3D(po->generatedGeometry()[i].polygon());
		sRoof.m_displayColor = QColor(200,200,140,255);	//for walls

		unsigned int componentID = VICUS::INVALID_ID;
		if (m_ui->comboBoxComponentRoof3->count() > 0)
			componentID = m_ui->comboBoxComponentRoof3->currentData().toUInt();
		// special handling for flap tile
		//if (m_ui->checkBoxFlapTile->isChecked()) {
			// TODO Dirk: for flap-tile surfaces adjust sRoof.m_displayName and componentID
		switch ((Vic3D::NewGeometryObject::RoofInputData::RoofType)m_ui->comboBoxRoofType->currentIndex()) {
			case Vic3D::NewGeometryObject::RoofInputData::SinglePitchRoof:{
				unsigned int roofElements = 1;
				if (i< roofElements) {
					sRoof.m_displayName =  tr("Roof surface %1").arg(++roofSurfaceCount);
					if (m_ui->comboBoxComponentRoof3->count() == 0)
						componentID = VICUS::INVALID_ID;
					else
						componentID = m_ui->comboBoxComponentRoof3->currentData().toUInt();
					sRoof.m_displayColor = QColor("#566094");	//for roofs
				}
				else {
					sRoof.m_displayName =  tr("Wall surface %1").arg(++wallCount);
					if (m_ui->comboBoxComponentWall3->count() == 0)
						componentID = VICUS::INVALID_ID;
					else
						componentID = m_ui->comboBoxComponentWall3->currentData().toUInt();
				}
			}
			break;
			case Vic3D::NewGeometryObject::RoofInputData::DoublePitchRoof:{
				unsigned int roofElements = 2;
				if (i< roofElements) {
					sRoof.m_displayName =  tr("Roof surface %1").arg(++roofSurfaceCount);
					if (m_ui->comboBoxComponentRoof3->count() == 0)
						componentID = VICUS::INVALID_ID;
					else
						componentID = m_ui->comboBoxComponentRoof3->currentData().toUInt();
					sRoof.m_displayColor = QColor("#566094");	//for roofs
				}
				else{
					sRoof.m_displayName =  tr("Wall surface %1").arg(++wallCount);
					if (m_ui->comboBoxComponentWall3->count() == 0)
						componentID = VICUS::INVALID_ID;
					else
						componentID = m_ui->comboBoxComponentWall3->currentData().toUInt();
				}
			}
			break;
			case Vic3D::NewGeometryObject::RoofInputData::MansardRoof:{
				unsigned int roofElements = 4;
				if (i< roofElements) {
					sRoof.m_displayName =  tr("Roof surface %1").arg(++roofSurfaceCount);
					if (m_ui->comboBoxComponentRoof3->count() == 0)
						componentID = VICUS::INVALID_ID;
					else
						componentID = m_ui->comboBoxComponentRoof3->currentData().toUInt();
					sRoof.m_displayColor = QColor("#566094");	//for roofs
				}
				else {
					sRoof.m_displayName =  tr("Wall surface %1").arg(++wallCount);
					if (m_ui->comboBoxComponentWall3->count() == 0)
						componentID = VICUS::INVALID_ID;
					else
						componentID = m_ui->comboBoxComponentWall3->currentData().toUInt();
				}
			}
			break;
			case Vic3D::NewGeometryObject::RoofInputData::HipRoof:{
				unsigned int roofElements = 4;
				if (i< roofElements) {
					sRoof.m_displayName =  tr("Roof surface %1").arg(++roofSurfaceCount);
					if (m_ui->comboBoxComponentRoof3->count() == 0)
						componentID = VICUS::INVALID_ID;
					else
						componentID = m_ui->comboBoxComponentRoof3->currentData().toUInt();
					sRoof.m_displayColor = QColor("#566094");	//for roofs
				}
				else {
					sRoof.m_displayName =  tr("Wall surface %1").arg(++wallCount);
					if (m_ui->comboBoxComponentWall3->count() == 0)
						componentID = VICUS::INVALID_ID;
					else
						componentID = m_ui->comboBoxComponentWall3->currentData().toUInt();
				}
			}
			break;
			case Vic3D::NewGeometryObject::RoofInputData::Complex:{
				//TODO: Dirk später noch den Kniestock beachten
				if (true) {
					sRoof.m_displayName =  tr("Roof surface %1").arg(++roofSurfaceCount);
					if (m_ui->comboBoxComponentRoof3->count() == 0)
						componentID = VICUS::INVALID_ID;
					else
						componentID = m_ui->comboBoxComponentRoof3->currentData().toUInt();
					sRoof.m_displayColor = QColor("#566094");	//for roofs
				}
//				else if(i>0){
//					sRoof.m_displayName =  tr("Wall surface %1").arg(++wallCount);
//					if (m_ui->comboBoxComponentWall3->count() == 0)
//						componentID = VICUS::INVALID_ID;
//					else
//						componentID = m_ui->comboBoxComponentWall3->currentData().toUInt();
//				}
			}
			break;
		}
		//}

		if (componentID != VICUS::INVALID_ID) {
			// new surfaces are attached to "Side A"
			componentInstances.push_back(
						VICUS::ComponentInstance(++compInstID, componentID, sRoof.m_id, VICUS::INVALID_ID));
		}

		// add surface to roof zone
		r.m_surfaces.push_back(sRoof);
	}

	//TODO Dirk hier muss noch die Floor Schaltfläche rein sobald Andreas die nachgerüstet hat
	if (m_ui->comboBoxComponentWall3->count() == 0)
		componentInstances.push_back(
				VICUS::ComponentInstance(++compInstID, VICUS::INVALID_ID, sFloor.m_id, VICUS::INVALID_ID));
	else
		componentInstances.push_back(
				VICUS::ComponentInstance(++compInstID, m_ui->comboBoxComponentWall3->currentData().toUInt(), sFloor.m_id, VICUS::INVALID_ID));

	double area = sFloor.geometry().area();
	VICUS::KeywordList::setParameter(r.m_para, "Room::para_t", VICUS::Room::P_Area, area);

	// TODO Dirk: compute roof volume, this should be done by NewGeometryObject
	double volume = 10;
	VICUS::KeywordList::setParameter(r.m_para, "Room::para_t", VICUS::Room::P_Volume, volume);

	// transfer default colors
	for (VICUS::Surface & s : r.m_surfaces)
		s.m_color = s.m_displayColor;

	// now create the undo action
	unsigned int buildingLevelUid = m_ui->comboBoxBuildingLevel3->currentData().toUInt();
	Q_ASSERT(buildingLevelUid != 0);
	SVUndoAddZone * undo = new SVUndoAddZone(tr("Adding roof zone '%1'").arg(r.m_displayName),
											 buildingLevelUid,
											 r, false, &componentInstances);
	undo->push();
}


// *** PRIVATE MEMBERS ***





void SVPropVertexListWidget::updateBuildingComboBox(QComboBox * combo) {
	// populate the combo boxes
	combo->blockSignals(true);
	unsigned int currentUniqueId = combo->currentData().toUInt();
	combo->clear();

	const VICUS::Project & prj = project();
	int rowOfCurrent = -1;
	for (unsigned int i=0; i<prj.m_buildings.size(); ++i) {
		const VICUS::Building & b = prj.m_buildings[i];
		combo->addItem(b.m_displayName, b.uniqueID());
		if (b.uniqueID() == currentUniqueId)
			rowOfCurrent = (int)i;
	}

	if (rowOfCurrent != -1) {
		combo->setCurrentIndex(rowOfCurrent);
	}
	else {
		combo->setCurrentIndex(combo->count()-1); // Note: if no buildings, nothing will be selected
	}
	combo->blockSignals(false);
}


void SVPropVertexListWidget::updateBuildingLevelsComboBox(QComboBox * combo, const QComboBox * buildingCombo) {
	combo->blockSignals(true);
	unsigned int currentUniqueId = combo->currentData().toUInt();
	combo->clear();
	// only add items if we have a building selected
	if (buildingCombo->count() != 0) {
		const VICUS::Project & prj = project();
		unsigned int buildingUniqueID = buildingCombo->currentData().toUInt();
		const VICUS::Building * b = dynamic_cast<const VICUS::Building*>(prj.objectById(buildingUniqueID));
		Q_ASSERT(b != nullptr);
		int rowOfCurrent = -1;
		for (unsigned int i=0; i<b->m_buildingLevels.size(); ++i) {
			const VICUS::BuildingLevel & bl = b->m_buildingLevels[i];
			combo->addItem(bl.m_displayName, bl.uniqueID());
			if (bl.uniqueID() == currentUniqueId)
				rowOfCurrent = (int)i;
		}
		if (rowOfCurrent != -1) {
			combo->setCurrentIndex(rowOfCurrent);
		}
		else {
			combo->setCurrentIndex(combo->count()-1); // Note: if none, nothing will be selected
		}

	}
	combo->blockSignals(false);
}


void SVPropVertexListWidget::updateZoneComboBox(QComboBox * combo, const QComboBox * buildingLevelCombo) {
	combo->blockSignals(true);
	unsigned int currentUniqueId = combo->currentData().toUInt();
	combo->clear();
	// only add items if we have a building level selected
	if (buildingLevelCombo->count() != 0) {
		const VICUS::Project & prj = project();
		unsigned int buildingLevelUniqueID = buildingLevelCombo->currentData().toUInt();
		const VICUS::BuildingLevel * bl = dynamic_cast<const VICUS::BuildingLevel*>(prj.objectById(buildingLevelUniqueID));
		Q_ASSERT(bl != nullptr);
		int rowOfCurrent = -1;
		for (unsigned int i=0; i<bl->m_rooms.size(); ++i) {
			const VICUS::Room & r = bl->m_rooms[i];
			combo->addItem(r.m_displayName, r.uniqueID());
			if (r.uniqueID() == currentUniqueId)
				rowOfCurrent = (int)i;
		}
		if (rowOfCurrent != -1) {
			combo->setCurrentIndex(rowOfCurrent);
		}
		else {
			combo->setCurrentIndex(combo->count()-1); // Note: if none, nothing will be selected
		}
	}
	combo->blockSignals(false);
	updateSurfacePageState();
}


bool SVPropVertexListWidget::reselectById(QComboBox * combo, int id) const {
	combo->setEnabled(true);
	if (id != -1) {
		id = combo->findData(id);
		if (id != -1) {
			combo->setCurrentIndex(id);
			return true;
		}
	}
	if (combo->count() != 0)
		combo->setCurrentIndex(0);
	else {
		combo->setEnabled(false);
	}
	return false;
}


bool SVPropVertexListWidget::createAnnonymousGeometry() const {
	return (m_ui->checkBoxAnnonymousGeometry->isVisibleTo(this) && m_ui->checkBoxAnnonymousGeometry->isChecked());
}


void SVPropVertexListWidget::updateSurfacePageState() {
	// update states of "Create surface" page

	// if checkbox is visible, we adjust the enabled state of other inputs
	bool annonymousGeometry = createAnnonymousGeometry();
	if (annonymousGeometry) {
		m_ui->labelBuilding->setEnabled(false);
		m_ui->comboBoxBuilding->setEnabled(false);
		m_ui->toolButtonAddBuilding->setEnabled(false);

		m_ui->labelBuildingLevel->setEnabled(false);
		m_ui->comboBoxBuildingLevel->setEnabled(false);
		m_ui->toolButtonAddBuildingLevel->setEnabled(false);

		m_ui->labelZone->setEnabled(false);
		m_ui->comboBoxZone->setEnabled(false);
		m_ui->toolButtonAddZone->setEnabled(false);

		m_ui->labelCompont->setEnabled(false);
		m_ui->comboBoxComponent->setEnabled(false);
		m_ui->toolButtonEditComponents1->setEnabled(false);
	}
	else {
		m_ui->labelCompont->setEnabled(true);
		m_ui->comboBoxComponent->setEnabled(true);
		m_ui->toolButtonEditComponents1->setEnabled(true);

		// building controls
		if (m_ui->comboBoxBuilding->count() == 0) {
			m_ui->comboBoxBuilding->setEnabled(false);
		}
		else {
			m_ui->comboBoxBuilding->setEnabled(true);
		}
		m_ui->labelBuilding->setEnabled(true);
		m_ui->toolButtonAddBuilding->setEnabled(true);


		// building level controls
		if (m_ui->comboBoxBuildingLevel->count() == 0) {
			m_ui->comboBoxBuildingLevel->setEnabled(false);
		}
		else {
			m_ui->comboBoxBuildingLevel->setEnabled(true);
		}
		// enable tool button to add new levels
		m_ui->toolButtonAddBuildingLevel->setEnabled(m_ui->comboBoxBuilding->count() != 0);
		m_ui->labelBuildingLevel->setEnabled(m_ui->comboBoxBuilding->count() != 0);
	}
}

void SVPropVertexListWidget::updateComponentComboBox(QComboBox * combo, int type) {
	// remember currently selected component IDs
	int compID = -1;
	if (combo->currentIndex() != -1)
		compID = combo->currentData().toInt();

	combo->clear();

	std::string langID = QtExt::LanguageHandler::instance().langId().toStdString();
	for (auto & c : SVSettings::instance().m_db.m_components) {
		switch (c.second.m_type) {
			case VICUS::Component::CT_OutsideWall :
			case VICUS::Component::CT_OutsideWallToGround :
			case VICUS::Component::CT_InsideWall :
				if (type == -1 || type == 0)
					combo->addItem( QtExt::MultiLangString2QString(c.second.m_displayName), c.first);
			break;

			case VICUS::Component::CT_FloorToCellar :
			case VICUS::Component::CT_FloorToAir :
			case VICUS::Component::CT_FloorToGround :
				if (type == -1 || type == 1)
					combo->addItem( QtExt::MultiLangString2QString(c.second.m_displayName), c.first);
			break;

			case VICUS::Component::CT_Ceiling :
			case VICUS::Component::CT_SlopedRoof :
			case VICUS::Component::CT_FlatRoof :
			case VICUS::Component::CT_ColdRoof :
			case VICUS::Component::CT_WarmRoof :
				if (type == -1 || type == 2)
					combo->addItem( QtExt::MultiLangString2QString(c.second.m_displayName), c.first);
			break;

			case VICUS::Component::CT_Miscellaneous :
			case VICUS::Component::NUM_CT:
				combo->addItem( QtExt::MultiLangString2QString(c.second.m_displayName), c.first);
			break;
		}
	}

	// reselect previously selected components
	reselectById(combo, compID);
}




void SVPropVertexListWidget::updateRoofGeometry() {
	// Guard against call when aborting/focus is lost during undo!
	Vic3D::NewGeometryObject * po = SVViewStateHandler::instance().m_newGeometryObject;
	if (po->newGeometryMode() != Vic3D::NewGeometryObject::NGM_Roof)
		return;

	Vic3D::NewGeometryObject::RoofInputData roofData;

	// get all data from UI
	roofData.m_type = (Vic3D::NewGeometryObject::RoofInputData::RoofType)m_ui->comboBoxRoofType->currentIndex();
	roofData.m_angle = m_ui->lineEditRoofInclination->value(); // in Deg
	roofData.m_height = m_ui->lineEditRoofHeight->value(); // in m
	roofData.m_flapTileHeight = m_ui->lineEditFlapTileHeight->value(); // in m
	roofData.m_hasFlapTile = m_ui->checkBoxFlapTile->isChecked();
	roofData.m_isHeightPredefined = m_ui->radioButtonRoofHeight->isChecked();
	roofData.m_rotate = m_polygonRotation;

	m_polygonRotation = false; // reset flag until next click

	po->setRoofGeometry(roofData);

	// we need to trigger a redraw here
	SVViewStateHandler::instance().m_geometryView->refreshSceneView();
}


void SVPropVertexListWidget::on_pushButtonRotateFloorPolygon_clicked() {
	m_polygonRotation = true; // set temporarily to true
	updateRoofGeometry();
}
