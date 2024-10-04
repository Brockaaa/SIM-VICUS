#include "VicOSM_Leisure.h"

namespace VicOSM {

bool Leisure::createLeisure(Way & way, Leisure& leisure) {
	if (!leisure.initialize(way)) return false;

	Area area;
	area.m_color = QColor("#c8facc");

	if (leisure.m_value == "park"){
		area.m_color = QColor("#c8facc");
	}

	leisure.m_areas.push_back(area);
	return true;
}

} // namespace VicOSM
