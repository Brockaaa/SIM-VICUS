#include "VicOSM_Natural.h"

namespace VicOSM {

bool Natural::createNatural(Node & node) {
	m_key = "natural";
	if (!initialize(node)) return false;

	Circle circle;
	circle.m_radius = 1.25;

	m_circles.push_back(circle);
	return true;
}

bool Natural::createNatural(Way & way) {
	m_key = "natural";
	if (!initialize(way)) return false;

	bool noArea = false;

	QColor color = QColor("#c8facc");

	if (m_value == "water"){
		color = QColor("#aad3df");
	} else if (m_value == "tree_row") {
		color = QColor("#b8d4a7");
		noArea = true;
	}

	if (noArea) {
		LineFromPlanes lineFromPlanes;
		lineFromPlanes.m_color = color;
		lineFromPlanes.m_lineThickness = 3;

		m_linesFromPlanes.push_back(lineFromPlanes);
		return true;
	}

	Area area;
	area.m_color = color;

	m_areas.push_back(area);
	return true;
}

} // namespace VicOSM
