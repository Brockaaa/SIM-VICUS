#ifndef VICUS_OSMBUILDINGOBJECT_H
#define VICUS_OSMBUILDINGOBJECT_H

#include "VICUS_Object.h"
#include "VicOSM_Building.h"
#include "VICUS_CodeGenMacros.h"
namespace VICUS {

class OSMBuildingObject : public Object {
public:
	OSMBuildingObject();

	const char * typeinfo() const {return "OSM Building";}

	// *** PUBLIC MEMBER FUNCTIONS ***

	VICUS_READWRITE
	VICUS_COMPARE_WITH_ID

	// *** PUBLIC MEMBER VARIABLES ***

	//:inherited	unsigned int		m_id = INVALID_ID;			// XML:A:required
	//:inherited	QString				m_displayName;				// XML:A
	//:inherited	bool				m_visible = true;			// XML:A

	VicOSM::OSMBuilding*				m_osmBuilding = nullptr;
};

}

#endif // VICUS_OSMBUILDINGOBJECT_H
