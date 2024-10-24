#include "VicOSM_Bridge.h"

namespace VicOSM {

bool Bridge::createBridge(Way & way) {
	m_key = "bridge";
	if (!initialize(way)) return false;

	Area area;
	area.m_color = QColor("#dddde8");

	m_areas.push_back(area);
	return true;
}

bool Bridge::createBridge(Relation & relation)
{
	m_key = "bridge";
	if (!initialize(relation)) return false;
	if (relation.containsKeyValue("type", "bridge")) {
		m_key = "type";
		m_value = "bridge";
	}
	if (relation.containsKeyValue("man_made", "bridge")) {
		m_key = "man_made";
		m_value = "bridge";
	}

	Area area;
	area.m_color = QColor("#dddde8");

	m_areas.push_back(area);
	return true;
}

} // namespace VicOSM
