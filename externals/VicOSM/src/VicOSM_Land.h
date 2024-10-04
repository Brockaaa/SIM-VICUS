#ifndef VicOSM_LAND_H
#define VicOSM_LAND_H

#include "VicOSM_AbstractOSMObject.h"
#include "VicOSM_Way.h"
#include "VicOSM_Relation.h"

namespace VicOSM {

struct Land : AbstractOSMObject {

	QColor	setColor();
	static bool createLand(Way &way, Land& land);
	static bool createLand(Relation &relation, Land& land);

};

} // namespace VicOSM

#endif // VicOSM_LAND_H
