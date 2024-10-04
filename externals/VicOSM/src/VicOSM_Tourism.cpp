#include "VicOSM_Tourism.h"

namespace VicOSM {

bool Tourism::createTourism(Way & way, Tourism & tourism) {
	tourism.m_key = "tourism";
	if (!tourism.initialize(way)) return false;

	Area area;
	area.m_color = QColor("#f2efe9");

	tourism.m_areas.push_back(area);
	return true;
}

} // namespace VicOSM
