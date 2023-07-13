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

#include <IBK_assert.h>

#include <VICUS_Project.h>

#include "SVViewStateHandler.h"
#include "Vic3DWireFrameObject.h"

SVUndoTrimObjects::SVUndoTrimObjects(const QString & label,
														 const std::vector<VICUS::Surface> & surfaces,
														 const std::vector<VICUS::SurfaceComponentInstance> *subSurfaceComponentInstances)
	: m_surfaces(surfaces)
{
	setText( label );
	if (subSurfaceComponentInstances != nullptr) {
		m_modifySubSurfaceComponentInstances = true;
		m_subSurfaceComponentInstances = *subSurfaceComponentInstances;
	}
}


void SVUndoTrimObjects::undo() {

	/// Im project selber


	// process all of our stored surfaces in the project
	for (unsigned int i=0; i<m_surfaces.size(); ++i) {
		// find surface by ID in current project
//		VICUS::Object * o = theProject().objectById(m_surfaces[i].m_id);
//		IBK_ASSERT(o != nullptr);
//		VICUS::Surface * s = dynamic_cast<VICUS::Surface *>(o);
//		Q_ASSERT(s != nullptr);
//		// exchange data between surfaces
//		std::swap(m_surfaces[i], *s);

		/// Füge hinzu neue surfaces
		/// Dabei checke ob parent ein raum sonst plain
		///
		///
	}

	/// Lösche alle surfaces
	/// Checke wieder ob raum oder plain
	///

	for (;;/* Deleted Surfaces*/) {

	}

	/// Modified suface component instances

	// also modified sub-surface components, if needed
	if (m_modifySubSurfaceComponentInstances) {
		m_subSurfaceComponentInstances.swap(theProject().m_subSurfaceComponentInstances);
	}

	theProject().updatePointers();

	// tell project that geometry has changed
	// NOTE: this may be slow for larger geometries...
	SVProjectHandler::instance().setModified( SVProjectHandler::BuildingGeometryChanged );
}


void SVUndoTrimObjects::redo() {
	undo();
}

