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
#include "IBKMK_3DCalculations.h"
#include "IBKMK_2DCalculations.h"

#include <VICUS_Project.h>

#include <RC_VicusClipping.h>

SVUndoTrimObjects::SVUndoTrimObjects(const QString & label,
									 std::map<unsigned int, std::vector<IBKMK::Polygon3D> > trimmedPolygons,
									 // trimSurfaces is a vector of tuples, each containing a reference to the selected surface of one trim, and the polyInput vector
									 // which was handed over to the polyTrim method, and therefore contains the trim result surfaces
									 std::map<unsigned int, std::vector<IBKMK::Polygon3D> > trimmedSubsurfaces,
									 const VICUS::Project & oldProject):
	m_trimmedPolygons(trimmedPolygons),
	m_trimmedSubsurfaces(trimmedSubsurfaces),
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
	//	std::map<unsigned int, const VICUS::ComponentInstance *> cisA, cisB;

	for (std::map<unsigned int, std::vector<IBKMK::Polygon3D>>::iterator it = m_trimmedPolygons.begin();
		 it != m_trimmedPolygons.end(); ++it )
	{
		// new surface ids
		std::set<unsigned int>							newSurfaceIds;
		// new subsurface ids
		std::map<unsigned int, std::set<unsigned int>>	newSubSurfaceIds;

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

		std::vector<IBKMK::Polygon3D> &polys = it->second;

		// copy these because the properties of surfToBeDeleted are unaccessible after pushing the first object into m_surfaces
		std::string surfDisplayName = s->m_displayName.toStdString();

		// initialize for planeCoordinates()
		double xCoord;
		double yCoord;

		// iterate over different trim result surfaces (of one trim / one original surface)
		for (unsigned int i = 0; i < polys.size(); ++i) {
			const IBKMK::Polygon3D &surfPoly = polys[i];

			qDebug() << "Surface #" << id << " replaced by Surface #" << nextId;

			newSurf.m_id = nextId;
			newSurfaceIds.insert(nextId++);
			newSurf.m_displayName = QString::fromStdString(surfDisplayName + "[" + std::to_string(i+1) + "]");
			newSurf.setPolygon3D(surfPoly);
			std::vector<VICUS::SubSurface> tempSubsurfaces;

			// iterate over all subsurfaces that were trimmed
			for (std::map<unsigned int, std::vector<IBKMK::Polygon3D>>::iterator ssit = m_trimmedSubsurfaces.begin();
				 ssit != m_trimmedSubsurfaces.end(); ++ssit )
			{
				const VICUS::Object *oo = m_project.objectById(ssit->first);
				if (oo == nullptr)
					continue;

				const VICUS::SubSurface *ss = dynamic_cast<const VICUS::SubSurface *>(oo);
				if (ss == nullptr)
					continue;

				// If this subsurface was located in this parent surface before trim
				if (ss->m_parent->m_id == it->first) {

					// transform the trimmed polygon to 2d for testing pointInPolygon with each former subsurface's centerpoint later
					std::vector<IBKMK::Vector2D> aux2DPolygon(surfPoly.vertexes().size());
					for (unsigned int j = 0; j < surfPoly.vertexes().size(); ++j) {
						IBKMK::planeCoordinates(surfPoly.offset(), surfPoly.localX(), surfPoly.localY(), surfPoly.vertexes()[j], xCoord, yCoord);
						aux2DPolygon.push_back(IBKMK::Vector2D(xCoord, yCoord));
					}

					// Add all trimresults of this subsurface, whose centerpoint is contained in this surfacePoly
					for (unsigned int k = 0; k < m_trimmedSubsurfaces[ssit->first].size(); ++k) {
						const IBKMK::Polygon3D &subSurfPoly = m_trimmedSubsurfaces[ssit->first][k];

						IBKMK::Vector3D subPolyCenter = subSurfPoly.centerPoint();

						// if any of the former surface's (trimmed) subsurfaces have their center point within this trimresult surface
						IBKMK::Vector2D subPolyCenter2D;
						IBKMK::planeCoordinates(surfPoly.offset(), surfPoly.localX(), surfPoly.localY(), subPolyCenter, subPolyCenter2D.m_x, subPolyCenter2D.m_y);

						if (IBKMK::pointInPolygon(aux2DPolygon, subPolyCenter2D) == 1) {

							// *** FIX SUB-SURFACES ***

							/// Sub-Surfaces need to produce a real hole in the parent surface.
							/// If points of the trimmed sub-surface lie directly on a edge of the parent polygon
							/// the CDT encounters errors und planes are not visible anymore since triangulation is
							/// error-prone. We need to fix the trimmed sub-surfaces so that points laying on the edge
							/// are moved inside the polygon. For now we assume that we move the point 1 cm inwards.
							///
							/// Steps:
							/// 1) Go through all edges of parent polygon
							/// 2) Check if one of sub-surface polygon's points is on edge of parent
							/// 3) If point is on edge, take normal of parent and edge vector and construct rectangular vector
							///	   relative to edge vector
							/// 4) Take point laying on edge add vector in both possible directions with e.g. 1cm and check if point is in parent-polygon

							fixSubSurfacePolygon(surfPoly, const_cast<IBKMK::Polygon3D&>(subSurfPoly));

							// ************************


							// Transform subsurface back to 2D
							std::vector<IBKMK::Vector2D> aux2DPolygon;

							// iterate over vertices of 3d subsurface
							for (unsigned int l = 0; l < m_trimmedSubsurfaces[ssit->first][k].vertexes().size(); ++l) {
								IBKMK::planeCoordinates(surfPoly.offset(), surfPoly.localX(), surfPoly.localY(), m_trimmedSubsurfaces[ssit->first][k].vertexes()[l], xCoord, yCoord);
								aux2DPolygon.push_back(IBKMK::Vector2D(xCoord, yCoord));
							}
							VICUS::SubSurface newSubsurface(*ss);
							newSubsurface.m_polygon2D = aux2DPolygon;
							newSubsurface.m_displayName = m_project.newUniqueSurfaceName(newSubsurface.m_displayName);
							newSubsurface.m_id = nextId;
							tempSubsurfaces.push_back(newSubsurface);

							// Store new IDs for subsurface component instance swapping
							newSubSurfaceIds[ss->m_id].insert(nextId++);
							break;
						}
					}
				}
			}

			std::vector<VICUS::Surface> cs = newSurf.childSurfaces();
			newSurf.setChildAndSubSurfaces(tempSubsurfaces, cs);

			if (room != nullptr) {
				// add surface to room surfaces
				const_cast<VICUS::Room*>(room)->m_surfaces.push_back(newSurf);
				m_project.updatePointers();

			} else {
				// add to anonymous geometry
				m_project.m_plainGeometry.m_surfaces.push_back(newSurf);
				m_project.updatePointers();
			}
		}

		if(room != nullptr) {

			// Remove old component id
			unsigned int idx = 0;
			std::vector<VICUS::ComponentInstance>			&cis    = m_project.m_componentInstances;
			std::vector<VICUS::SubSurfaceComponentInstance> &subCis = m_project.m_subSurfaceComponentInstances;
			bool foundComponent = false;
			for (; idx < m_project.m_componentInstances.size(); ++idx) {
				if (cis[idx].m_idSideASurface == id || cis[idx].m_idSideBSurface == id) {
					foundComponent = true;
					break;
				}
			}
			for (unsigned int i = 0; i < room->m_surfaces.size(); ++i) {
				if (id == room->m_surfaces[i].m_id) {
					qDebug() << "Removing surface with ID %1" << s->m_id;
					const_cast<VICUS::Room *>(room)->m_surfaces.erase(room->m_surfaces.begin() + i);
					break;
				}
			}

			if (foundComponent) {
				for (unsigned newId : newSurfaceIds) {
					VICUS::ComponentInstance newCi = cis[idx];
					newCi.m_id = nextId++;
					if (newCi.m_idSideASurface == id) {
						newCi.m_idSideASurface = newId;
						newCi.m_idSideBSurface = VICUS::INVALID_ID;
						cis.push_back(newCi);
					}
					else if (newCi.m_idSideBSurface == id) {
						newCi.m_idSideASurface = VICUS::INVALID_ID;
						newCi.m_idSideBSurface = newId;
						cis.push_back(newCi);
					}
					// Add new sub surface component instances
				}
				cis.erase(cis.begin() + idx);
			}

			idx = 0;
			std::vector<unsigned int> idxToDelete;
			for (const std::pair<unsigned int, std::set<unsigned int>> subIdSwap : newSubSurfaceIds) {
				for (;idx < subCis.size(); ++idx) {
					if (subIdSwap.first == subCis[idx].m_idSideASurface ||
							subIdSwap.first == subCis[idx].m_idSideBSurface)
						break;
				}
				idxToDelete.push_back(idx);
				// Add new sub-surface component instance
				for (unsigned int newId : subIdSwap.second) {
					VICUS::SubSurfaceComponentInstance newSubCi = subCis[idx];
					newSubCi.m_id = nextId++;
					if (newSubCi.m_idSideASurface == subIdSwap.first)
						newSubCi.m_idSideASurface = newId;
					if (newSubCi.m_idSideBSurface == subIdSwap.first)
						newSubCi.m_idSideBSurface = newId;
					// Add new sub surface component instances
					subCis.push_back(newSubCi);
				}
			}

			for (unsigned int i = idxToDelete.size(); i > 0; --i) {
				subCis.erase(subCis.begin() + idxToDelete[i - 1]);
			}
		}
		else {
			for (unsigned int i=0; i<m_project.m_plainGeometry.m_surfaces.size(); ++i) {
				if (id == m_project.m_plainGeometry.m_surfaces[i].m_id) {
					qDebug() << "Removing surface with ID %1" << s->m_id;
					m_project.m_plainGeometry.m_surfaces.erase(m_project.m_plainGeometry.m_surfaces.begin() + i);
					break;
				}
			}
		}

		m_project.updatePointers();
	}


	RC::VicusClipper vicusClipper(m_project.m_buildings, m_project.m_componentInstances, 5, 1, m_project.nextUnusedID(), true);
//	vicusClipper.clipSurfaces(nullptr);
	vicusClipper.createComponentInstances(nullptr);
	m_project.m_buildings = vicusClipper.vicusBuildings();
	m_project.m_componentInstances = *vicusClipper.vicusCompInstances();

	std::swap(theProject(), m_project);
	theProject().updatePointers();
	SVProjectHandler::instance().setModified( SVProjectHandler::BuildingGeometryChanged );
	SVProjectHandler::instance().setModified( SVProjectHandler::BuildingTopologyChanged );

}

void SVUndoTrimObjects::fixSubSurfacePolygon(const IBKMK::Polygon3D &parentPoly,
											 IBKMK::Polygon3D &subSurfacePoly) {

	const double TOL		= 1E-3;
	const double FIX_WIDTH	= 1E-4;

	unsigned int size = parentPoly.vertexes().size();
	for (unsigned int i = 0; i < size; ++i) {
		const IBKMK::Vector3D &v1 = parentPoly.vertexes()[ i			];
		const IBKMK::Vector3D &v2 = parentPoly.vertexes()[(i + 1) % size];

		std::vector<IBKMK::Vector3D> newVerts = subSurfacePoly.vertexes();

		for (unsigned int j = 0; j < subSurfacePoly.vertexes().size(); ++j) {
			const IBKMK::Vector3D &v = subSurfacePoly.vertexes()[j];

			double lineFactor;
			IBKMK::Vector3D p;
			double distance = IBKMK::lineToPointDistance(v1, v2-v1, v, lineFactor, p);

			if (distance < TOL) {
				IBKMK::Vector3D perpVec = (v2 - v1).crossProduct(parentPoly.normal()).normalized();

				double directions[2] = {-1., 1.};
				IBKMK::Vector3D newPoint;
				bool foundPoint = false;
				for (double dir : directions) {
					newPoint = v + dir * FIX_WIDTH * perpVec;

					IBKMK::Vector2D point;
					IBKMK::planeCoordinates(parentPoly.offset(), parentPoly.localX(), parentPoly.localY(), newPoint, point.m_x, point.m_y);

					if (IBKMK::pointInPolygon(parentPoly.polyline().vertexes(), point) == 1) {
						foundPoint = true;
						break;
					}
				}

				if (foundPoint)
					newVerts[j] = newPoint;
			}
		}

		IBKMK::Polygon3D newPoly(newVerts);
		std::swap(subSurfacePoly, newPoly);
	}
}

