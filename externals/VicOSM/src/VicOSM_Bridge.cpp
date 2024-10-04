#include "VicOSM_Bridge.h"

namespace VicOSM {

bool Bridge::createBridge(Way & way, Bridge &bridge) {
	bridge.m_key = "bridge";
	if (!bridge.initialize(way)) return false;

	Area area;
	area.m_color = QColor("#dddde8");

	bridge.m_areas.push_back(area);
	return true;
}

} // namespace VicOSM
