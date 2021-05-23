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

#ifndef SVUndoAddBuildingLevelH
#define SVUndoAddBuildingLevelH

#include <VICUS_BuildingLevel.h>

#include "SVUndoCommandBase.h"

/*! Undo action for adding a new or copied building level to an existing building. */
class SVUndoAddBuildingLevel : public SVUndoCommandBase {
	Q_DECLARE_TR_FUNCTIONS(SVUndoAddBuildingLevel)
public:
	SVUndoAddBuildingLevel(const QString & label, unsigned int buildingUUID, const VICUS::BuildingLevel & addedLevel, bool topologyOnly);

	virtual void undo();
	virtual void redo();

private:

	/*! Cache for added item. */
	VICUS::BuildingLevel	m_addedLevel;

	/*! If true, the change event sent is BuildingTopologyChanged, otherwise BuildingGeometryChanged. */
	bool					m_topologyOnly;

	unsigned int			m_buildingUUID;
};


#endif // SVUndoAddBuildingLevelH
