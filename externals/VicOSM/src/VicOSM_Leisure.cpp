#include "VicOSM_Leisure.h"

namespace VicOSM {

bool Leisure::createLeisure(Way & way) {
	if (!initialize(way)) return false;

	Area area;
	area.m_color = QColor("#c8facc");

	if (m_value == "park"){
		area.m_color = QColor("#c8facc");
	}

	m_areas.push_back(area);
	return true;
}

} // namespace VicOSM
