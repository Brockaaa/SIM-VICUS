#include "VicOSM_Natural.h"

namespace VicOSM {

bool Natural::createNatural(Node & node, Natural & natural) {
	natural.m_key = "natural";
	if (!natural.initialize(node)) return false;

	Circle circle;
	circle.m_radius = 1.25;

	natural.m_circles.push_back(circle);
	return true;
}

bool Natural::createNatural(Way & way, Natural & natural) {
	natural.m_key = "natural";
	if (!natural.initialize(way)) return false;

	bool noArea = false;

	QColor color = QColor("#c8facc");

	if (natural.m_value == "water"){
		color = QColor("#aad3df");
	} else if (natural.m_value == "tree_row") {
		color = QColor("#b8d4a7");
		noArea = true;
	}

	if (noArea) {
		LineFromPlanes lineFromPlanes;
		lineFromPlanes.m_color = color;
		lineFromPlanes.m_lineThickness = 3;

		//createMultilineFromWay

		natural.m_linesFromPlanes.push_back(lineFromPlanes);
		return true;
	}

	Area area;
	area.m_color = color;

	//createMultipolygonFromWay(way, area.m_multiPolygon);

	natural.m_areas.push_back(area);
	return true;
}

} // namespace VicOSM
