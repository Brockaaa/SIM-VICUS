#ifndef VicOSM_NATURAL_H
#define VicOSM_NATURAL_H

#include "VicOSM_AbstractOSMObject.h"
#include "VicOSM_Node.h"
#include "VicOSM_Way.h"

namespace VicOSM {

struct Natural : AbstractOSMObject {

	static bool createNatural(Node &node, Natural& natural);
	static bool createNatural(Way &way, Natural& natural);

};

} // namespace VicOSM

#endif // VicOSM_NATURAL_H
