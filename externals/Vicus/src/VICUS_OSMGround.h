#ifndef VICUS_OSMGROUND_H
#define VICUS_OSMGROUND_H

#include "VICUS_Object.h"
#include "VICUS_CodeGenMacros.h"

namespace VICUS {

class OSMGround : public Object
{
public:
	OSMGround();
	const char * typeinfo() const {return "OSM Ground";}

	// *** PUBLIC MEMBER FUNCTIONS ***

	VICUS_READWRITE
	VICUS_COMPARE_WITH_ID

	// *** PUBLIC MEMBER VARIABLES ***

	//:inherited	unsigned int		m_id = INVALID_ID;			// XML:A:required
	//:inherited	bool				m_visible = true;			// XML:A
};

}

#endif // VICUS_OSMGROUND_H
