#ifndef VicOSM_BRIDGE_H
#define VicOSM_BRIDGE_H

#include "VicOSM_AbstractOSMObject.h"
#include "VicOSM_Way.h"

namespace VicOSM {

struct Bridge : AbstractOSMObject {

	static bool createBridge(Way &way, Bridge &bridge);

};

} // namespace VicOSM

#endif // VicOSM_BRIDGE_H
