#include "VicOSM_Barrier.h"

namespace VicOSM {

bool Barrier::createBarrier(Way & way) {
	m_key = "barrier";
	if (!initialize(way)) return false;
	if (way.containsKeyValue("area", "yes")) return false;

	LineFromPlanes lineFromPlanes;
	lineFromPlanes.m_color = QColor("#7b7a7a");
	lineFromPlanes.m_lineThickness = 1.5;

	if (m_value == "fence") {
		lineFromPlanes.m_lineThickness = 1.0;
	}

	// createMultipolygonFromWay

	m_linesFromPlanes.push_back(lineFromPlanes);
	return true;
}

} // namespace VicOSM

