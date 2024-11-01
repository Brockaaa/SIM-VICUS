#ifndef VICUS_OSMSTREETS_H
#define VICUS_OSMSTREETS_H

#include "VICUS_Object.h"
#include "VICUS_CodeGenMacros.h"

namespace VICUS {

class OSMStreets : public Object
{
public:
	OSMStreets();

	const char * typeinfo() const {return "OSM Streets";}

	// *** PUBLIC MEMBER FUNCTIONS ***

	VICUS_READWRITE
		VICUS_COMPARE_WITH_ID

	// *** PUBLIC MEMBER VARIABLES ***

	//:inherited	unsigned int		m_id = INVALID_ID;			// XML:A:required
	//:inherited	bool				m_visible = true;			// XML:A
};

}

#endif // VICUS_OSMSTREETS_H
