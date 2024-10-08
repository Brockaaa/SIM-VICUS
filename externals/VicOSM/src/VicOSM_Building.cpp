#include "VicOSM_Building.h"

namespace VicOSM {

void OSMBuilding::calculateHeight(AbstractOSMElement & element) {
	std::string valueLevel = element.getValueFromKey("building:levels");
	if (valueLevel != "") {
		try {
			double valueLevelDouble = std::stod(valueLevel);
			if (valueLevelDouble > 0) m_height = valueLevelDouble * m_levelHeight;
		} catch (const std::invalid_argument& e) {
			// Handle invalid argument exception
		} catch (const std::out_of_range& e) {
			// Handle out of range exception
		}
	}

	std::string valueRoof = element.getValueFromKey("roof:levels");
	if (valueRoof != "") {
		try {
			double valueRoofDouble = std::stod(valueRoof);
			if (valueRoofDouble > 0) m_height += valueRoofDouble * m_roofHeight;
		} catch (const std::invalid_argument& e) {
			// Handle invalid argument exception
		} catch (const std::out_of_range& e) {
			// Handle out of range exception
		}
	}

	std::string valueHeight = element.getValueFromKey("height");
	if (valueHeight != "") {
		try {
			double valueHeightDouble = std::stod(valueHeight);
			m_height = valueHeightDouble;
		} catch (const std::invalid_argument& e) {
			// Handle invalid argument exception
		} catch (const std::out_of_range& e) {
			// Handle out of range exception
		}
	}

	std::string valueMinLevel = element.getValueFromKey("building:min_level");
	if (valueMinLevel != "") {
		try {
			double valueMinLevelDouble = std::stod(valueMinLevel);
			if (valueMinLevelDouble > 0) m_minHeight = valueMinLevelDouble * m_levelHeight;
		} catch (const std::invalid_argument& e) {
			// Handle invalid argument exception
		} catch (const std::out_of_range& e) {
			// Handle out of range exception
		}
	}

	std::string valueMinHeight = element.getValueFromKey("min_height");
	if (valueMinHeight != "") {
		try {
			double valueMinHeightDouble = std::stod(valueMinHeight);
			m_minHeight = valueMinHeightDouble;
		} catch (const std::invalid_argument& e) {
			// Handle invalid argument exception
		} catch (const std::out_of_range& e) {
			// Handle out of range exception
		}
	}
}

bool OSMBuilding::createBuilding(Way & way, OSMBuilding &building, bool enable3D) {
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

bool OSMBuilding::createBuilding(Relation & relation, OSMBuilding &building, bool enable3D) {
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
