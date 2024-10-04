#include "VicOSM_AbstractOSMObject.h"

namespace VicOSM {

bool AbstractOSMObject::initialize(AbstractOSMElement & osmElement) {
	if (osmElement.containsKeyValue("location", "underground")) return false;
	if (osmElement.containsKeyValue("location", "underwater")) return false;
	m_value = osmElement.getValueFromKey(m_key);
	std::string layer = osmElement.getValueFromKey("layer");
	assignKeyValue();
	if (layer != "") m_layer = std::stoi(layer);
	return true;
}

void AbstractOSMObject::assignKeyValue() {
	if (m_key == "building") {
		m_keyValue = BUILDING;
	} else if (m_key == "highway") {
		if (m_value == "footway") {
			m_keyValue = HIGHWAY_FOOTWAY;
		} else if (m_value == "steps") {
			m_keyValue = HIGHWAY_STEPS;
		} else if (m_value == "path") {
			m_keyValue = HIGHWAY_PATH;
		}else if (m_value == "service") {
			m_keyValue = HIGHWAY_SERVICE;
		} else if (m_value == "motorway") {
			m_keyValue = HIGHWAY_MOTORWAY;
		}else if (m_value == "primary") {
			m_keyValue = HIGHWAY_PRIMARY;
		}else if (m_value == "secondary") {
			m_keyValue = HIGHWAY_SECONDARY;
		}else if (m_value == "residential") {
			m_keyValue = HIGHWAY_RESIDENTIAL;
		}else if (m_value == "trunk") {
			m_keyValue = HIGHWAY_TRUNK;
		}else if (m_value == "pedestrian") {
			m_keyValue = HIGHWAY_PEDESTRIAN;
		}else {
			m_keyValue = HIGHWAY;
		}
	} else if (m_key == "landuse") {
		if (m_value == "village_green") {
			m_keyValue = LANDUSE_VILLAGE_GREEN;
		} else if (m_value == "grass") {
			m_keyValue = LANDUSE_GRASS;
		} else if (m_value == "brownfield") {
			m_keyValue = LANDUSE_BROWNFIELD;
		} else if (m_value == "forest") {
			m_keyValue = LANDUSE_FOREST;
		} else if (m_value == "farmyard") {
			m_keyValue = LANDUSE_FARMYARD;
		} else if (m_value == "construction") {
			m_keyValue = LANDUSE_CONSTRUCTION;
		} else if (m_value == "industrial") {
			m_keyValue = LANDUSE_INDUSTRIAL;
		} else if (m_value == "orchard") {
			m_keyValue = LANDUSE_ORCHARD;
		} else if (m_value == "retail") {
			m_keyValue = LANDUSE_RETAIL;
		} else if (m_value == "commercial") {
			m_keyValue = LANDUSE_COMMERCIAL;
		} else if (m_value == "residential") {
			m_keyValue = LANDUSE_RESIDENTIAL;
		} else if (m_value == "railway") {
			m_keyValue = LANDUSE_RAILWAY;
		} else if (m_value == "religious") {
			m_keyValue = LANDUSE_RELIGIOUS;
		} else if (m_value == "recreation_ground") {
			m_keyValue = LANDUSE_RECREATION_GROUND;
		} else if (m_value == "cemetery") {
			m_keyValue = LANDUSE_CEMETERY;
		} else if (m_value == "meadow") {
			m_keyValue = LANDUSE_MEADOW;
		} else if (m_value == "flowerbed") {
			m_keyValue = LANDUSE_FLOWERBED;
		} else {
			m_keyValue = LANDUSE;
		}
	} else if (m_key == "leisure") {
		if (m_value == "park") {
			m_keyValue = LEISURE_PARK;
		} else {
			m_keyValue = LEISURE;
		}
	} else if (m_key == "natural") {
		if (m_value == "tree_row") {
			m_keyValue = NATURAL_TREE_ROW;
		} else if (m_value == "water") {
			m_keyValue = NATURAL_WATER;
		} else if (m_value == "tree") {
			m_keyValue = NATURAL_TREE;
		} else {
			m_keyValue = NATURAL;
		}
	} else if (m_key == "place") {
		m_keyValue = PLACE;
	} else if (m_key == "heritage") {
		m_keyValue = HERITAGE;
	} else if (m_key == "amenity") {
		if (m_value == "kindergarten") {
			m_keyValue = AMENITY_KINDERGARTEN;
		} else if (m_value == "school") {
			m_keyValue = AMENITY_SCHOOL;
		} else if (m_value == "social_facility") {
			m_keyValue = AMENITY_SOCIAL_FACILITY;
		} else {
			m_keyValue = AMENITY;
		}
	} else if (m_key == "waterway") {
		m_keyValue = WATERWAY;
	} else if (m_key == "water") {
		m_keyValue = WATER;
	} else if (m_key == "bridge") {
		m_keyValue = BRIDGE;
	} else if (m_key == "tourism") {
		m_keyValue = TOURISM;
	} else if (m_key == "barrier") {
		m_keyValue = BARRIER;
	}else {
		m_keyValue = NUM_KV;
	}
}


} // namespace VicOSM
