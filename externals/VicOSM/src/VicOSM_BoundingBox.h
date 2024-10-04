#ifndef VicOSM_BOUNDINGBOX_H
#define VicOSM_BOUNDINGBOX_H

#include "VicOSM_AbstractOSMObject.h"

namespace VicOSM {

struct BoundingBox {
	double minlat;
	double maxlat;
	double minlon;
	double maxlon;

	double								m_zPosition = 0;
};

} // namespace VicOSM

#endif // VicOSM_BOUNDINGBOX_H
