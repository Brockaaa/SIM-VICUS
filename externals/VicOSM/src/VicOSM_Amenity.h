#ifndef VicOSM_AMENITY_H
#define VicOSM_AMENITY_H

#include "VicOSM_AbstractOSMObject.h"
#include "VicOSM_Way.h"

namespace VicOSM {

struct Amenity : AbstractOSMObject {

	static bool createAmenity(Way &way, Amenity& amenity);

};

} // namespace VicOSM

#endif // VicOSM_AMENITY_H
