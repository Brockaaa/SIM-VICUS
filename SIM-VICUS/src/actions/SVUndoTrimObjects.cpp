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

#include "SVUndoTrimObjects.h"
#include "SVProjectHandler.h"

#include <IBK_assert.h>
#include "IBKMK_Polygon3D.h"

#include <VICUS_Project.h>

SVUndoTrimObjects::SVUndoTrimObjects(const QString & label,
									 std::vector<std::tuple<const VICUS::Surface*, std::vector<std::vector<IBKMK::Vector3D>>>> & trimSurfaces,
									 // trimSurfaces is a vector of tuples, each containing a reference to the selected surface of one trim, and the polyInput vector
									 // which was handed over to the polyTrim method, and therefore contains the trim result surfaces
									 const VICUS::Project & oldProject):
									/// Kann ich hier wirklich einen pointer nutzen? Wenn ich surface* lösche, geht ja kein undo mehr
	m_trimSurfaces(trimSurfaces),
	m_project(oldProject)

{
	setText( label );
}

void SVUndoTrimObjects::undo() {

}


void SVUndoTrimObjects::redo() {
	// iterate over different trims
	for (unsigned int i=0; i<m_trimSurfaces.size(); ++i) {

		const VICUS::Surface* surfToBeDeleted = std::get<0>(m_trimSurfaces[i]);
		std::vector<std::vector<IBKMK::Vector3D>> geometryToBeAdded = std::get<1>(m_trimSurfaces[i]);

		bool parentRoom = false;
		const VICUS::Room* room = dynamic_cast<const VICUS::Room*>(surfToBeDeleted->m_parent);
		if (room != nullptr) parentRoom = true;

		unsigned int nextId = theProject().nextUnusedID();

		// copy these because the properties of surfToBeDeleted are unaccessible after pushing the first object into m_surfaces
		std::string surfDisplayName = surfToBeDeleted->m_displayName.toStdString();
		QColor surfDisplayColor = surfToBeDeleted->m_displayColor;
		QColor surfColor = surfToBeDeleted->m_color;

		// iterate over different trim result surfaces
		for (unsigned int i=0; i<geometryToBeAdded.size(); ++i) {

			std::vector<IBKMK::Vector3D> poly = geometryToBeAdded[i];
			VICUS::Surface s;

			s.m_id = nextId++;
			s.m_displayName = QString::fromStdString(surfDisplayName + "[" + std::to_string(i+1) + "]");
			s.setPolygon3D(IBKMK::Polygon3D(poly));
			s.m_displayColor = surfDisplayColor;
			s.m_color = surfColor;

			if (parentRoom) {
				// add surface to room surfaces
				const_cast<VICUS::Room*>(room)->m_surfaces.push_back(s);
				theProject().updatePointers();

			} else {
				// add to anonymous geometry
				theProject().m_plainGeometry.m_surfaces.push_back(s);
				theProject().updatePointers();
			}
		}

	}

	theProject().updatePointers();

	for (unsigned int i=0; i<m_trimSurfaces.size(); ++i) {

		const VICUS::Surface* surfToBeDeleted = std::get<0>(m_trimSurfaces[i]);
		bool parentRoom = false;
		const VICUS::Room* room = dynamic_cast<const VICUS::Room*>(surfToBeDeleted->m_parent);
		if (room != nullptr) parentRoom = true;

		if (parentRoom) {
			//IBK::IBK_Message("abcdef", IBK::MSG_WARNING);
			//! TODO: Effizienter machen, ohne dass dabei ein SegFault auftritt
			for (unsigned int bIdx = 0; bIdx < theProject().m_buildings.size(); ++bIdx) {
				VICUS::Building & b = theProject().m_buildings[bIdx];
				for (unsigned int blIdx = 0; blIdx < b.m_buildingLevels.size(); ++blIdx) {
					VICUS::BuildingLevel & bl = b.m_buildingLevels[blIdx];
					for (unsigned int rIdx = 0; rIdx < bl.m_rooms.size(); ++rIdx) {
						VICUS::Room & r = bl.m_rooms[rIdx];
						for (unsigned int sIdx = 0; sIdx < r.m_surfaces.size(); ++sIdx) {
							// is surface selected for deletion?
							if (surfToBeDeleted->m_id == r.m_surfaces[sIdx].m_id) {
								r.m_surfaces.erase(r.m_surfaces.begin() + sIdx);
								IBK::IBK_Message("DELETED ONE", IBK::MSG_WARNING);
								theProject().updatePointers();
							}
						}
					}
				}
			}
			//theProject().updatePointers();

		} else {
			//!.
		}

	}



	/// Lösche alle surfaces
	/// Checke wieder ob raum oder plain
	///

	//for (;;/* Deleted Surfaces*/) {

	//}

	/// Modified suface component instances

	// also modified sub-surface components, if needed
	//if (m_modifySubSurfaceComponentInstances) {
	//	m_subSurfaceComponentInstances.swap(theProject().m_subSurfaceComponentInstances);
	//}

	theProject().updatePointers();
	SVProjectHandler::instance().setModified( SVProjectHandler::BuildingGeometryChanged );


	//! TODO Brauche ich auch SubSurfaceComponentInstances?
	/*m_oldCompInstances.reserve(project().m_componentInstances.size()); //! TODO brauche ich hier theProject() ? was ist der unterschied? wozu brauche ich reserve überhaupt?
	for (const VICUS::ComponentInstance & ci : project().m_componentInstances) {

		if (ci.m_sideASurface != nullptr &&
				ci.m_sideASurface == surfToBeDeleted) { //! TODO kann ich den nullptr check weglassen?

			m_tempCompInstancesA.push_back(ci);

			VICUS::ComponentInstance comp = ci;
			m_oldCompInstances.push_back(comp);

		}
		// same for side B
		if (ci.m_sideBSurface != nullptr &&
				ci.m_sideBSurface == surfToBeDeleted) {
			m_tempCompInstancesB.push_back(ci);

			VICUS::ComponentInstance comp = ci;
			m_oldCompInstances.push_back(comp);
		}
	}*/


}

