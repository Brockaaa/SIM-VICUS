#include "SVUndoAddDrawingOSM.h"
#include "SVProjectHandler.h"
#include "SVSettings.h"

#include <VICUS_OSMBuildingObject.h>

SVUndoAddDrawingOSM::SVUndoAddDrawingOSM(const QString & label, const VICUS::DrawingOSM & addedDrawing) :
	m_addedDrawing(addedDrawing)
{
	setText( label );
}


void SVUndoAddDrawingOSM::undo() {
	// remove drawing
	Q_ASSERT(!theProject().m_drawingsOSM.empty());

	theProject().m_drawingsOSM.pop_back();
	theProject().m_osmBuildingObjects.clear();

	theProject().m_osmBuildingObjectRoot = VICUS::OSMBuildingObject();
	theProject().m_osmGroundLayer = VICUS::OSMGround();
	theProject().m_osmStreetLayer = VICUS::OSMStreets();

	theProject().updatePointers();

	SVProjectHandler::instance().setModified( SVProjectHandler::DrawingOSMModified);
}


void SVUndoAddDrawingOSM::redo() {
	// append drawing

	unsigned int newId = theProject().nextUnusedID();
	m_addedDrawing.m_id = newId;
	newId++;

	theProject().m_osmGroundLayer.m_id = newId;
	newId++;

	theProject().m_osmStreetLayer.m_id = newId;
	newId++;

	theProject().m_osmBuildingObjectRoot.m_id = newId;
	newId++;
	theProject().m_drawingsOSM.push_back(m_addedDrawing);

	theProject().m_osmBuildingObjects.reserve(m_addedDrawing.m_buildings.size());
	for (auto& OSMBuilding : theProject().m_drawingsOSM.back().m_buildings) {
		VICUS::OSMBuildingObject newBuilding;
		newBuilding.m_id = newId;
		newId++;
		newBuilding.m_osmBuilding = &OSMBuilding;
		newBuilding.m_displayName = QString::fromStdString(OSMBuilding.m_displayName);
		theProject().m_osmBuildingObjects.push_back(newBuilding);
	}

	theProject().updatePointers();

	SVProjectHandler::instance().setModified( SVProjectHandler::DrawingOSMModified);
}

