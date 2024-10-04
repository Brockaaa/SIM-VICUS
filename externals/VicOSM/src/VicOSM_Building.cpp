#include "VicOSM_Building.h"

namespace VicOSM {

void Building::calculateHeight(AbstractOSMElement & element) {
	std::string valueLevel = element.getValueFromKey("building:levels");
	if (valueLevel != "") {
		double valueLevelDouble = std::stoi(valueLevel);
		if (valueLevelDouble > 0) m_height = valueLevelDouble * m_levelHeight;
	}

	std::string valueRoof = element.getValueFromKey("roof:levels");
	if (valueRoof != "") {
		double valueRoofDouble = std::stoi(valueRoof);
		if (valueRoofDouble > 0) m_height += valueRoofDouble * m_roofHeight;
	}

	std::string valueHeight = element.getValueFromKey("height");
	if (valueHeight != "") {
		double valueHeightDouble = std::stoi(valueHeight);
		m_height = valueHeightDouble;
	}

	std::string valueMinLevel = element.getValueFromKey("building:min_level");
	if (valueMinLevel != "") {
		double valueMinLevelDouble = std::stoi(valueMinLevel);
		if (valueMinLevelDouble > 0) m_minHeight = valueMinLevelDouble * m_levelHeight;
	}

	std::string valueMinHeight = element.getValueFromKey("min_height");
	if (valueMinHeight != "") {
		double valueMinHeightDouble = std::stoi(valueMinHeight);
		m_minHeight = valueMinHeightDouble;
	}

}

bool Building::createBuilding(Way & way, Building &building, bool enable3D) {
	if (way.containsKeyValue("building", "cellar")) return false;
	if (way.containsKeyValue("building", "roof") && !enable3D) return false;
	building.m_key = "building";
	if (!building.initialize(way)) return false;
	building.calculateHeight(way);

	Area area;
	area.m_extrudingPolygon = enable3D;
	area.m_height = building.m_height;
	area.m_minHeight = building.m_minHeight;

	area.m_color = QColor("#b3a294");

	building.m_areas.push_back(area);
	return true;
}

bool Building::createBuilding(Relation & relation, Building &building, bool enable3D) {
	if (!relation.containsKeyValue("type", "multipolygon")) return false;
	if (relation.containsKeyValue("building", "cellar")) return false;
	if (relation.containsKeyValue("building", "roof") && !enable3D) return false;
	building.m_key = "building";
	if (!building.initialize(relation)) return false;
	building.calculateHeight(relation);

	Area area;
	area.m_extrudingPolygon = enable3D;
	area.m_height = building.m_height;
	area.m_minHeight = building.m_minHeight;
	area.m_color = QColor("#b3a294");
	building.m_areas.push_back(area);

	return true;
}

} // namespace VicOSM
