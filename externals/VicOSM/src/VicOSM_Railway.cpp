#include "VicOSM_Railway.h"

namespace VicOSM {

bool Railway::createRailway(Way & way) {
	m_key = "railway";
	if (!initialize(way)) return false;
	if (m_value != "rail" && m_value != "light_rail" && m_value != "tram" && m_value != "platform") {
		return false;
	}
	if (m_layer != 0 && way.containsKey("bridge") && m_layer < 5) {
		m_layer++;
	}

	LineFromPlanes lineFromPlanes;

	if (m_value == "light_rail") {
		lineFromPlanes.m_lineThickness = 1.3f;
	} else if (m_value == "tram" || way.containsKeyValue("tram", "yes")) {
		lineFromPlanes.m_lineThickness = 1.1f;
	}
	lineFromPlanes.m_lineThickness = 1.5f;
	lineFromPlanes.m_color = QColor("999999");
	m_linesFromPlanes.push_back(lineFromPlanes);
	return true;
}


}
