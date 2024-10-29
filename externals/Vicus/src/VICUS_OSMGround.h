#ifndef VICUS_OSMGROUND_H
#define VICUS_OSMGROUND_H

#include "VICUS_Object.h"

namespace VICUS {

class OSMGround : public Object
{
public:
	OSMGround();
	const char * typeinfo() const {return "OSM Ground";}
};

}

#endif // VICUS_OSMGROUND_H
