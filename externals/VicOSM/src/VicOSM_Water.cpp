#include "VicOSM_Water.h"

namespace VicOSM {

bool Water::createWater(Way & way) {
	bool containsWater = way.containsKey("water");
	if (containsWater)
		m_key = "water";
	else
		m_key = "waterway";
	if (!initialize(way)) return false;

	if (containsWater) {
		m_key = "water";
		Area area;
		area.m_color = QColor("#aad3df");
		m_areas.push_back(area);

	} else {
		m_key = "waterway";
		LineFromPlanes lineFromPlanes;
		lineFromPlanes.m_lineThickness = 1;
		m_linesFromPlanes.push_back(lineFromPlanes);
	}
	return true;
}

bool Water::createWater(Relation & relation)
{
	if(!(relation.containsKeyValue("type", "multipolygon"))) return false;
	bool containsWater = relation.containsKey("water");
	if (containsWater)
		m_key = "water";
	else
		m_key = "waterway";
	if (!initialize(relation)) return false;

	Area area;
	area.m_color = QColor("#aad3df");
	m_areas.push_back(area);

	return true;
}

} // namespace VicOSM
