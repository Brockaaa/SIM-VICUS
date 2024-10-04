#ifndef VicOSM_TOURISM_H
#define VicOSM_TOURISM_H

#include "VicOSM_AbstractOSMObject.h"
#include "VicOSM_Way.h"

namespace VicOSM {

struct Tourism : AbstractOSMObject {

	static bool createTourism(Way &way, Tourism& tourism);

};

} // namespace VicOSM

#endif // VicOSM_TOURISM_H
