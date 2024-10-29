#ifndef VICUS_OSMBUILDINGOBJECT_H
#define VICUS_OSMBUILDINGOBJECT_H

#include "VICUS_Object.h"
#include "VicOSM_Building.h"
namespace VICUS {

class OSMBuildingObject : public Object {
public:
	OSMBuildingObject();

	const char * typeinfo() const {return "OSM Building";}

	VicOSM::OSMBuilding*				m_osmBuilding = nullptr;
};

}

#endif // VICUS_OSMBUILDINGOBJECT_H
