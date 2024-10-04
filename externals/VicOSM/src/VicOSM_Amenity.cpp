#include "VicOSM_Amenity.h"

namespace VicOSM {

bool Amenity::createAmenity(Way & way, Amenity& amenity) {
	amenity.m_key = "amenity";
	if (!amenity.initialize(way)) return false;

	Area area;
	area.m_color = QColor("#c8facc");

	if (amenity.m_value == "parking") {
		area.m_color = QColor("#eeeeee");
	} else if (amenity.m_value == "kindergarten") {
		area.m_color = QColor("#ffffe5");
	} else if (amenity.m_value == "school") {
		area.m_color = QColor("#ffffe5");
	} else if (amenity.m_value == "social_facility") {
		area.m_color = QColor("#ffffe5");
	}

	amenity.m_areas.push_back(area);
	return true;
}

} // namespace VicOSM
