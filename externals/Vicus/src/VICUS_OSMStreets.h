#ifndef VICUS_OSMSTREETS_H
#define VICUS_OSMSTREETS_H

#include "VICUS_Object.h"

namespace VICUS {

class OSMStreets : public Object
{
public:
	OSMStreets();

	const char * typeinfo() const {return "OSM Streets";}
};

}

#endif // VICUS_OSMSTREETS_H
