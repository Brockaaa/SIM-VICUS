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

#include "SVUndoModifySurfaceGeometry.h"
#include "SVProjectHandler.h"

#include <VICUS_Project.h>

#include "SVViewStateHandler.h"
#include "Vic3DWireFrameObject.h"

SVUndoModifySurfaceGeometry::SVUndoModifySurfaceGeometry(const QString & label,
														 const std::vector<VICUS::Surface> & surfaces)
	: m_surfaces(surfaces)
{
	setText( label );
}


void SVUndoModifySurfaceGeometry::undo() {

	std::vector<const VICUS::Surface*> surfacesProject;

	// since selection change is also an undo property, we can rely on having the same selection
	// here as when the surface properties were modified
	theProject().selectedSurfaces(surfacesProject, VICUS::Project::SG_All);

	for (const VICUS::Surface *sOld : surfacesProject ) {
		for ( VICUS::Surface &sNew : m_surfaces ) {
			if ( sOld->uniqueID() == sNew.uniqueID() ) {
				// we swap the surface's polygon and the subsurfaces polygons
				// and then update the geometry object
				VICUS::Surface * oldS = const_cast<VICUS::Surface *>(sOld);

				// TODO : This is slow! Not only polygon memory is copied around, but also the triangulation
				//        is done with every setXXX call, so 4 times in total. While this code is safe and ensures
				//        consistency, it might scale badly for large geometries.
				VICUS::Polygon3D oldPolygon = oldS->polygon3D();
				oldS->setPolygon3D(sNew.polygon3D());
				sNew.setPolygon3D(oldPolygon);
				std::vector<VICUS::SubSurface> oldSubSurfaces = oldS->subSurfaces();
				oldS->setSubSurfaces(sNew.subSurfaces());
				sNew.setSubSurfaces(oldSubSurfaces);
				break;
			}
		}
	}

	// reset local transformation matrix
	SVViewStateHandler::instance().m_selectedGeometryObject->m_transform = Vic3D::Transform3D();

	// tell project that geometry has changed
	// NOTE: this may be slow for larger geometries...
	SVProjectHandler::instance().setModified( SVProjectHandler::BuildingGeometryChanged );
}


void SVUndoModifySurfaceGeometry::redo() {
	undo();
}

