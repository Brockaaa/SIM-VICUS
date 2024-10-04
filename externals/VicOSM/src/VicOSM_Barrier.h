#ifndef VicOSM_BARRIER_H
#define VicOSM_BARRIER_H

#include "VicOSM_AbstractOSMObject.h"
#include "VicOSM_Way.h"

namespace VicOSM {

struct Barrier : AbstractOSMObject {

	static bool createBarrier(Way &way, Barrier &barrier);

};

} // namespace VicOSM

#endif // VicOSM_BARRIER_H
