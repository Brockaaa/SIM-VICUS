#include "VicOSM_Place.h"

namespace VicOSM {

bool Place::createPlace(Way & way, Place & place) {
	if (way.containsKey("place"))
		place.m_key = "place";
	else
		place.m_key = "heritage";
	if (!place.initialize(way)) return false;

	Area area;
	area.m_color = QColor("#dddde8");

	place.m_areas.push_back(area);
	return true;
}

bool Place::createPlace(Relation & relation, Place & place) {
	if (!relation.containsKeyValue("type", "multipolygon")) return false;
	place.m_key = "place";
	if (!place.initialize(relation)) return false;


	Area area;
	area.m_color = QColor("#dddde8");
	place.m_areas.push_back(area);

	return true;
}

} // namespace VicOSM
