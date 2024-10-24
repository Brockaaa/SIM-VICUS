#include "VicOSM_Land.h"

namespace VicOSM {

QColor Land::setColor() {
	QColor color("#c8facc");

	if (m_value == "residential"){
		color = QColor("#f2dad9");
	} else if (m_value == "forest") {
		color = QColor("#add19e");
	} else if (m_value == "industrial") {
		color = QColor("#ebdbe8");
	} else if (m_value == "orchard") {
		color = QColor("#aedfa3");
	} else if (m_value == "village_green") {
		color = QColor("#cdebb0");
	} else if (m_value == "construction") {
		color = QColor("#c7c7b4");
	} else if (m_value == "grass") {
		color = QColor("#cdebb0");
	} else if (m_value == "retail") {
		color = QColor("#ffd6d1");
	} else if (m_value == "cemetery") {
		color = QColor("#aacbaf");
	} else if (m_value == "commercial") {
		color = QColor("#f2dad9");
	} else if (m_value == "public_administration") {
		color = QColor("#f2efe9");
	} else if (m_value == "railway") {
		color = QColor("#f7f6f1");
	} else if (m_value == "farmyard") {
		color = QColor("#f5dcba");
	} else if (m_value == "meadow") {
		color = QColor("#cdebb0");
	} else if (m_value == "religious") {
		color = QColor("#d0d0d0");
	} else if (m_value == "flowerbed") {
		color = QColor("#cdebb0");
	} else if (m_value == "recreation_ground") {
		color = QColor("#dffce2");
	} else if (m_value == "brownfield") {
		color = QColor("#c7c7b4");
	}

	return color;
}

bool Land::createLand(Way & way) {
	m_key = "landuse";
	if (!initialize(way)) return false;

	Area area;
	area.m_color = setColor();

	m_areas.push_back(area);
	return true;
}

bool Land::createLand(Relation & relation) {
	if(!(relation.containsKeyValue("type", "multipolygon"))) return false;
	m_key = "landuse";
	if (!initialize(relation)) return false;

	Area area;
	area.m_color = setColor();
	m_areas.push_back(area);

	return true;
}

} // namespace VicOSM
