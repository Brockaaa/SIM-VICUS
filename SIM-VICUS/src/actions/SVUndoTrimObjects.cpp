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
									 std::map<unsigned int, std::vector<VICUS::Polygon3D> > trimmedPolygons,
									 // trimSurfaces is a vector of tuples, each containing a reference to the selected surface of one trim, and the polyInput vector
									 // which was handed over to the polyTrim method, and therefore contains the trim result surfaces
									 const VICUS::Project & oldProject):
									/// Kann ich hier wirklich einen pointer nutzen? Wenn ich surface* lösche, geht ja kein undo mehr
	m_trimmedPolygons(trimmedPolygons),
	m_project(oldProject)

{
	setText( label );
	m_project.updatePointers();
}

void SVUndoTrimObjects::undo() {
	std::swap(theProject(), m_project);
	theProject().updatePointers();
	SVProjectHandler::instance().setModified( SVProjectHandler::BuildingGeometryChanged );
}


void SVUndoTrimObjects::redo() {
	// iterate over different trims
	for (std::map<unsigned int, std::vector<VICUS::Polygon3D>>::iterator it = m_trimmedPolygons.begin();
		 it != m_trimmedPolygons.end(); ++it )
	{

		const VICUS::Object *o = m_project.objectById(it->first);
		if (o == nullptr)
			continue;

		const VICUS::Surface *s = dynamic_cast<const VICUS::Surface *>(o);
		if (s == nullptr)
			continue;

		VICUS::Surface newSurf(*s);
		unsigned int id = s->m_id; // needed since pointer will be broken after surfaces are added in room
		const VICUS::Room* room = dynamic_cast<const VICUS::Room*>(s->m_parent);
		unsigned int nextId = m_project.nextUnusedID();

		std::vector<VICUS::Polygon3D> &polys = it->second;

		// copy these because the properties of surfToBeDeleted are unaccessible after pushing the first object into m_surfaces
		std::string surfDisplayName = s->m_displayName.toStdString();

		// iterate over different trim result surfaces
		for (unsigned int i=0; i<polys.size(); ++i) {

			newSurf.m_id = nextId++;
			newSurf.m_displayName = QString::fromStdString(surfDisplayName + "[" + std::to_string(i+1) + "]");
			newSurf.setPolygon3D(polys[i]);
			newSurf.setSubSurfaces(std::vector<VICUS::SubSurface>());

			if (room != nullptr) {
				// add surface to room surfaces
				const_cast<VICUS::Room*>(room)->m_surfaces.push_back(newSurf);

			} else {
				// add to anonymous geometry
				m_project.m_plainGeometry.m_surfaces.push_back(newSurf);
			}
		}

		if(room != nullptr) {
			for (unsigned int i=0; i<room->m_surfaces.size(); ++i) {
				if (id == room->m_surfaces[i].m_id) {
					qDebug() << "Removing surface with ID #%1" << s->m_id;
					const_cast<VICUS::Room *>(room)->m_surfaces.erase(room->m_surfaces.begin() + i);
					break;
				}
			}
		}
		else {
			for (unsigned int i=0; i<m_project.m_plainGeometry.m_surfaces.size(); ++i) {
				if (id == m_project.m_plainGeometry.m_surfaces[i].m_id) {
					qDebug() << "Removing surface with ID #%1" << s->m_id;
					m_project.m_plainGeometry.m_surfaces.erase(m_project.m_plainGeometry.m_surfaces.begin() + i);
					break;
				}
			}
		}

		m_project.updatePointers();
	}

	std::swap(theProject(), m_project);
	theProject().updatePointers();
	SVProjectHandler::instance().setModified( SVProjectHandler::BuildingGeometryChanged );
	SVProjectHandler::instance().setModified( SVProjectHandler::BuildingTopologyChanged );

}

