#include "VicOSM_Place.h"

namespace VicOSM {

bool Place::createPlace(Way & way) {
	if (way.containsKey("place"))
		m_key = "place";
	else
		m_key = "heritage";
	if (!initialize(way)) return false;

	Area area;
	area.m_color = QColor("#dddde8");

	m_areas.push_back(area);
	return true;
}

bool Place::createPlace(Relation & relation) {
	if (!relation.containsKeyValue("type", "multipolygon")) return false;
	m_key = "place";
	if (!initialize(relation)) return false;


	Area area;
	area.m_color = QColor("#dddde8");
	m_areas.push_back(area);

	return true;
}

} // namespace VicOSM
