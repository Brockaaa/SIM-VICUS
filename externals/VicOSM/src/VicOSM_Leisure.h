#ifndef VicOSM_LEISURE_H
#define VicOSM_LEISURE_H

#include "VicOSM_AbstractOSMObject.h"
#include "VicOSM_Way.h"

namespace VicOSM {

struct Leisure : AbstractOSMObject {

	static bool createLeisure(Way &way, Leisure& leisure);

};

} // namespace VicOSM

#endif // VicOSM_LEISURE_H
