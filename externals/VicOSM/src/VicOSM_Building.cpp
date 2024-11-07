#include "VicOSM_Building.h"
#include <algorithm>
#include <QDebug>

namespace VicOSM {

void OSMBuilding::calculateHeight(const AbstractOSMElement & element, Area& area) const{
	std::string valueLevel = element.getValueFromKey("building:levels");
	if (valueLevel != "") {
		try {
			double valueLevelDouble = std::stod(valueLevel);
			if (valueLevelDouble > 0) area.m_height = valueLevelDouble * m_levelHeight;
		} catch (const std::invalid_argument& e) {
		} catch (const std::out_of_range& e) {
		}
	}

	std::string valueRoof = element.getValueFromKey("roof:levels");
	if (valueRoof != "") {
		try {
			double valueRoofDouble = std::stod(valueRoof);
			if (valueRoofDouble > 0) area.m_height += valueRoofDouble * m_roofHeight;
		} catch (const std::invalid_argument& e) {
		} catch (const std::out_of_range& e) {
		}
	}

	std::string valueEstHeight = element.getValueFromKey("est_height");
	if (valueEstHeight != "") {
		try {
			double valueHeightDouble = std::stod(valueEstHeight);
			area.m_height = valueHeightDouble;
		} catch (const std::invalid_argument& e) {
		} catch (const std::out_of_range& e) {
		}
	}

	std::string valueHeight = element.getValueFromKey("height");
	if (valueHeight != "") {
		try {
			double valueHeightDouble = std::stod(valueHeight);
			area.m_height = valueHeightDouble;
		} catch (const std::invalid_argument& e) {
		} catch (const std::out_of_range& e) {
		}
	}

	std::string valueMinLevel = element.getValueFromKey("building:min_level");
	if (valueMinLevel != "") {
		try {
			double valueMinLevelDouble = std::stod(valueMinLevel);
			if (valueMinLevelDouble > 0) area.m_minHeight = valueMinLevelDouble * m_levelHeight;
		} catch (const std::invalid_argument& e) {
		} catch (const std::out_of_range& e) {
		}
	}

	std::string valueMinHeight = element.getValueFromKey("min_height");
	if (valueMinHeight != "") {
		try {
			double valueMinHeightDouble = std::stod(valueMinHeight);
			area.m_minHeight = valueMinHeightDouble;
		} catch (const std::invalid_argument& e) {
		} catch (const std::out_of_range& e) {
		}
	}
}

bool OSMBuilding::createBuilding(Way & way, bool enable3D) {
	if (way.containsKeyValue("building", "cellar")) return false;
	if (way.containsKeyValue("building", "roof") && !enable3D) return false;
	m_key = "building";
	if (!initialize(way)) return false;
	if (enable3D) m_layer = 0;
	setDisplayName(way);

	m_areas.push_back(createArea(way, enable3D));
	return true;
}

bool OSMBuilding::createBuilding(Relation & relation, bool enable3D) {
	if (relation.containsKeyValue("building", "cellar")) return false;
	if (relation.containsKeyValue("building", "roof") && !enable3D) return false;
	m_key = "building";
	if (!initialize(relation)) return false;
	if (enable3D) m_layer = 0;
	setDisplayName(relation);

	m_areas.push_back(createArea(relation, enable3D));
	return true;
}

bool OSMBuilding::initializeSimple3DBuilding(Relation &relation) {
	m_keyValue = BUILDING;
	bool containsBuilding = relation.containsKey("building");
	bool containsBuildingPart = relation.containsKey("building:part");
	bool containsTypeBuilding = relation.containsKeyValue("type", "building");
	if (containsBuilding) {
		m_key = "building";
		m_value = relation.getValueFromKey(m_key);
	}
	if (containsBuildingPart) {
		std::string value = relation.getValueFromKey(m_key);
		if (value != "no") {
			m_key = "building:part";
			m_value = value;
		} else {
			m_key = "building";
			m_value = relation.getValueFromKey(m_key);
		}
	}
	if (containsTypeBuilding) {
		m_key = "type";
		m_value = "building";
	}

	assignEnum();
	return true;
}

Area OSMBuilding::createArea(const AbstractOSMElement & element, bool enable3D) {
	Area area;
	if (enable3D)
		calculateHeight(element, area);

	area.m_extrudingPolygon = enable3D;
	area.m_color = QColor("#b3a294");

	return area;
}

void OSMBuilding::setDisplayName(const AbstractOSMElement& element) {
	QString displayName;
	if (element.containsKey("addr:street") && element.containsKey("addr:housenumber")) {
		displayName = QString("%1 %2").arg(QString::fromStdString(element.getValueFromKey("addr:street")), QString::fromStdString(element.getValueFromKey("addr:housenumber")));
	}
	if (element.containsKey("name")) {
		std::string name = element.getValueFromKey("name");
		if (name != "") {
			if (displayName.isEmpty()) {
				displayName = QString::fromStdString(name);
			} else {
				displayName += QString(", %1").arg(QString::fromStdString(name));
			}
		}
	}
	m_displayName = displayName.toStdString();
}

void OSMBuilding::setVisible(bool visible) {
	AbstractOSMObject::setVisible(visible);
	m_dirtyLayer = true;
	for (auto& area : m_areas)
		area.m_dirtyTriangulation = true;
}

void OSMBuilding::setSelected(bool selected) {
	AbstractOSMObject::setSelected(selected);
	for (auto& area : m_areas)
		area.m_dirtyTriangulation = true;
}

} // namespace VicOSM
