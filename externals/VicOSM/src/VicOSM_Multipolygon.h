#ifndef VicOSM_MULTIPOLYGON_H
#define VicOSM_MULTIPOLYGON_H

#include <vector>
#include <IBKMK_Vector2D.h>

namespace VicOSM {

struct Multipolygon {
	std::vector<IBKMK::Vector2D> m_outerPolyline;
	std::vector<std::vector<IBKMK::Vector2D>> m_innerPolylines;
};

} // namespace VicOSM

#endif // VicOSM_MULTIPOLYGON_H
