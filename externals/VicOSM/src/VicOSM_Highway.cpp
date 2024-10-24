#include "VicOSM_Highway.h"

namespace VicOSM {

bool Highway::createHighway(Way & way) {
	m_key = "highway";
	if (!initialize(way)) return false;
	bool area = way.containsKeyValue("area", "yes");
	// workaround for messy layer implementation
	if (m_layer != 0 && way.containsKey("bridge") && m_layer < 4) {
		m_layer += 2;
	}

	if (area) {
		Area area;
		area.m_color = QColor("#dddde8");
		m_keyValue = HIGHWAY_GENERALAREA;

		m_areas.push_back(area);
	} else  {
		LineFromPlanes lineFromPlanes;
		double lineThickness = 3.0f;
		QColor color("#78909c");

		if (m_keyValue == HIGHWAY_FOOTWAY || m_keyValue == HIGHWAY_STEPS || m_keyValue == HIGHWAY_PATH) {
			color = QColor("#fa8173");
			lineThickness = 0.6f;
		} else if (m_keyValue == HIGHWAY_SERVICE) {
			color = QColor("#ffffff");
			lineThickness = 2.0f;
		} else if (m_keyValue == HIGHWAY_MOTORWAY) {
			color = QColor("#f1bcc6");
			lineThickness = 4.5f;
		} else if (m_keyValue == HIGHWAY_PRIMARY) {
			color = QColor("#fcd6a4");
			lineThickness = 4.2f;
		} else if (m_keyValue == HIGHWAY_TRUNK) {
			color = QColor("#fcd6a4");
			lineThickness = 4.2f;
		} else if (m_keyValue == HIGHWAY_SECONDARY) {
			color = QColor("#f7fabf");
			lineThickness = 4.0f;
		} else if (m_keyValue == HIGHWAY_RESIDENTIAL) {
			lineThickness = 3.5f;
		} else if (m_keyValue == HIGHWAY_PEDESTRIAN) {
			lineThickness = 2.0f;
			color = QColor("#dddde8");
		}

		lineFromPlanes.m_lineThickness = lineThickness;
		lineFromPlanes.m_color = color;

		// createMultipolygonFromWay
		m_linesFromPlanes.push_back(lineFromPlanes);
	}

	return true;

}

bool Highway::createHighway(Relation & relation) {
	m_key = "highway";
	if (!initialize(relation)) return false;

	bool containsKey = (m_keyValue == HIGHWAY_PEDESTRIAN || m_keyValue == HIGHWAY_FOOTWAY);
	bool isMultipolygon = relation.containsKeyValue("type", "multipolygon");
	if (!(containsKey && isMultipolygon)) return false;
	m_keyValue = LANDUSE_RELIGIOUS; // highway area should not exist, assigning a key value that should approximately reflect the order and likely not overlap

	Area area;
	area.m_color = QColor("#dddde8");
	m_areas.push_back(area);

	return true;
}

} // namespace VicOSM
