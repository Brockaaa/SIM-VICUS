#ifndef VicOSM_WATER_H
#define VicOSM_WATER_H

#include "VicOSM_AbstractOSMObject.h"
#include "VicOSM_Way.h"
#include "VicOSM_Relation.h"


namespace VicOSM {

struct Water : AbstractOSMObject {

	static bool createWater(Way &way, Water& water);
	static bool createWater(Relation &relation, Water& water);

};

} // namespace VicOSM

#endif // VicOSM_WATER_H
