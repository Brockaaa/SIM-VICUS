#ifndef VicOSM_PLACE_H
#define VicOSM_PLACE_H

#include "VicOSM_AbstractOSMObject.h"
#include "VicOSM_Way.h"
#include "VicOSM_Relation.h"

namespace VicOSM {

struct Place : AbstractOSMObject {

	static bool createPlace(Way &way, Place& place);
	static bool createPlace(Relation &relation, Place& place);

};

} // namespace VicOSM

#endif // VicOSM_PLACE_H
