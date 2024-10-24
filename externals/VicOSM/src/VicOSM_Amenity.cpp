#include "VicOSM_Amenity.h"

namespace VicOSM {

bool Amenity::createAmenity(Way & way) {
	m_key = "amenity";
	if (!initialize(way)) return false;

	Area area;
	area.m_color = QColor("#c8facc");

	if (m_value == "parking") {
		area.m_color = QColor("#eeeeee");
	} else if (m_value == "kindergarten") {
		area.m_color = QColor("#ffffe5");
	} else if (m_value == "school") {
		area.m_color = QColor("#ffffe5");
	} else if (m_value == "social_facility") {
		area.m_color = QColor("#ffffe5");
	} else if (m_value == "fountain") {
		area.m_color = QColor("#aad3df");
	}

	m_areas.push_back(area);
	return true;
}

} // namespace VicOSM
