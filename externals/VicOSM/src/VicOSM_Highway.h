#ifndef VicOSM_HIGHWAY_H
#define VicOSM_HIGHWAY_H

#include "VicOSM_AbstractOSMObject.h"
#include "VicOSM_Way.h"
#include "VicOSM_Relation.h"

namespace VicOSM {

struct Highway : AbstractOSMObject {

	static bool createHighway(Way &way, Highway& highway);
	// should be deprecated. All highways that are areas should be some form of place, landuse etc.
	static bool createHighway(Relation &relation, Highway& highway);

};

} // namespace VicOSM

#endif // VicOSM_HIGHWAY_H
