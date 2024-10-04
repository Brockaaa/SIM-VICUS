#ifndef VicOSM_BUILDING_H
#define VicOSM_BUILDING_H

#include "VicOSM_AbstractOSMObject.h"
#include "VicOSM_Way.h"
#include "VicOSM_Relation.h"

namespace VicOSM {

struct Building : AbstractOSMObject {

	void calculateHeight(AbstractOSMElement& element);

	static bool createBuilding(Way &way, Building &building, bool enable3D = false);
	static bool createBuilding(Relation &relation, Building &building, bool enable3D = false);

	double								m_height = 3;

	double								m_minHeight = 0;

	double								m_levelHeight = 3;

	double								m_roofHeight = 3;
};

} // namespace VicOSM

#endif // VicOSM_BUILDING_H
