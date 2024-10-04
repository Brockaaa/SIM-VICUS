#include "VicOSM_Water.h"

namespace VicOSM {

bool Water::createWater(Way & way, Water & water) {
	bool containsWater = way.containsKey("water");
	if (containsWater)
		water.m_key = "water";
	else
		water.m_key = "waterway";
	if (!water.initialize(way)) return false;

	if (containsWater) {
		water.m_key = "water";
		Area area;
		area.m_color = QColor("#aad3df");
		water.m_areas.push_back(area);

	} else {
		water.m_key = "waterway";
		LineFromPlanes lineFromPlanes;
		lineFromPlanes.m_lineThickness = 1;
		water.m_linesFromPlanes.push_back(lineFromPlanes);
	}
	return true;
}

bool Water::createWater(Relation & relation, Water & water)
{
	if(!(relation.containsKeyValue("type", "multipolygon"))) return false;
	bool containsWater = relation.containsKey("water");
	if (containsWater)
		water.m_key = "water";
	else
		water.m_key = "waterway";
	if (!water.initialize(relation)) return false;

	Area area;
	area.m_color = QColor("#aad3df");
	water.m_areas.push_back(area);

	return true;
}

} // namespace VicOSM
