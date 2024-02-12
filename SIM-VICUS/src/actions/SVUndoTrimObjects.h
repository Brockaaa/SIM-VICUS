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

#ifndef SVUndoTrimObjectsH
#define SVUndoTrimObjectsH

#include <VICUS_Surface.h>
#include <VICUS_Project.h>

#include "SVUndoCommandBase.h"

/*! Action for applying trimmed surfaces and/or sub-surfaces
	\note Trimmed sub-surfaces/surfaces are stored with their id as key inside
		  the maps m_trimmedSurfaces | m_trimmedSubSurfaces and their resulting
		  new 3D-Polygons in a vector as value.
		  The undo action searches for the old
*/
class SVUndoTrimObjects : public SVUndoCommandBase {
	Q_DECLARE_TR_FUNCTIONS(SVUndoTrimObjects)
public:

	/*! Creates the undo-action.
	*/
	SVUndoTrimObjects(const QString & label,
					  std::map<unsigned int, std::vector<IBKMK::Polygon3D>>	trimmedSurfaces,
					  std::map<unsigned int, std::vector<IBKMK::Polygon3D>>	trimmedSubSurfaces,
					  const VICUS::Project & newProject);

	virtual void undo();
	virtual void redo();

private:

	/*! Fixes sub-surfaces after trimming, so that all points lay inside the parent polygon and
		triangulation is working properly. Writes a Warning, if sub-surface could not be fixed.
		\param parenPoly Parent polygon of sub-surface
		\param normal	 Normal of parent plane
		\param subSurfacePoly Polygon of sub-surface - is going to be fixed, if possible
	*/
	void fixSubSurfacePolygon(const IBKMK::Polygon3D &parentPoly, IBKMK::Polygon3D &subSurfacePoly);

	/*! Object copies of surfaces to be deleted and added.
		key id of surface that has been trimmed
		value vector with newly produced 3D polygons of surfaces
	*/
	std::map<unsigned int, std::vector<IBKMK::Polygon3D>>	m_trimmedSurfaces;

	/*! Object copies of sub-surfaces to be deleted and added.
		key id of sub-surface that has been trimmed
		value vector with newly produced 3D polygons of sub-surfaces
	*/
	std::map<unsigned int, std::vector<IBKMK::Polygon3D>>	m_trimmedSubSurfaces;

	/*! Cache for entire project data. */
	VICUS::Project	m_project;

};


#endif // SVUndoTrimObjectsH
