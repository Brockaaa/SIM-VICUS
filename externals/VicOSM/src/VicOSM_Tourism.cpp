#include "VicOSM_Tourism.h"

namespace VicOSM {

bool Tourism::createTourism(Way & way) {
	m_key = "tourism";
	if (!initialize(way)) return false;

	Area area;
	area.m_color = QColor("#f2efe9");

	m_areas.push_back(area);
	return true;
}

} // namespace VicOSM
