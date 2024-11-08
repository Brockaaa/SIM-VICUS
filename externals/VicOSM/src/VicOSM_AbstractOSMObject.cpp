#include "VicOSM_AbstractOSMObject.h"
#include <VicOSM_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <VicOSM_Constants.h>
#include <NANDRAD_Utilities.h>

namespace VicOSM {

void AbstractOSMObject::updatePlaneGeometry() {
	for (auto& area : m_areas)
		area.m_dirtyTriangulation = true;
	for (auto& lineFromPlanes : m_linesFromPlanes)
		lineFromPlanes.m_dirtyTriangulation = true;
	for (auto& circle : m_circles)
		circle.m_dirtyTriangulation = true;
}

bool AbstractOSMObject::initialize(AbstractOSMElement & osmElement) {
	if (osmElement.containsKeyValue("location", "underground")) return false;
	if (osmElement.containsKeyValue("location", "underwater")) return false;
	if (osmElement.containsKey("tunnel") && !osmElement.containsKeyValue("tunnel", "no")) return false;
	if (osmElement.containsKeyValue("subway", "yes")) return false;
	m_id = osmElement.m_id;
	m_value = osmElement.getValueFromKey(m_key);
	std::string layer = osmElement.getValueFromKey("layer");
	assignEnum();
	try {
		if (layer != "") m_layer = (int)std::stod(layer);
	} catch (IBK::Exception & ex){

	}
	return true;
}

void AbstractOSMObject::assignEnum() {
	if (m_key == "type") {
		m_keyValue = BUILDING;
	} else if (m_key == "building") {
		m_keyValue = BUILDING;
	} else if (m_key == "building:part") {
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
		if (m_value == "square") {
			m_keyValue = PLACE_SQUARE;
		} else {
			m_keyValue = PLACE;
		}
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
	}else if (m_key == "railway") {
		m_keyValue = RAILWAY;
	}else {
		m_keyValue = NUM_KV;
	}
}

void AbstractOSMObject::setVisible(bool visible)
{
	m_visible = visible;
	m_dirtyLayer = true;
}

void AbstractOSMObject::setSelected(bool selected)
{
	m_selected = selected;
	m_dirtyLayer = true;
}

void AbstractOSMObject::readXML(const TiXmlElement * element) {
	FUNCID(AbstractOSMObject::readXML);

	try {
		// search for mandatory attributes
		// reading attributes
		const TiXmlAttribute * attrib = element->FirstAttribute();
		while (attrib) {
			const std::string & attribName = attrib->NameStr();
			if (attribName == "id")
				m_id = atol(attrib->Value());
			else if (attribName == "key")
				m_key = attrib->ValueStr();
			else if (attribName == "value")
				m_value = attrib->ValueStr();
			else if (attribName == "displayName")
				m_displayName = attrib->ValueStr();
			else {
				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ATTRIBUTE).arg(attribName).arg(element->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			attrib = attrib->Next();
		}
		// search for mandatory elements
		// reading elements
		const TiXmlElement * c = element->FirstChildElement();
		while (c) {
			const std::string & cName = c->ValueStr();
			if (cName == "Areas") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "Area")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					Area obj;
					obj.readXML(c2);
					m_areas.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "LinesFromPlanes") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "LineFromPlanes")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					LineFromPlanes obj;
					obj.readXML(c2);
					m_linesFromPlanes.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "Circles") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "Circle")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					Circle obj;
					obj.readXML(c2);
					m_circles.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else {
				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			c = c->NextSiblingElement();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'AbstractOSMObject' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'AbstractOSMObject' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * AbstractOSMObject::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("AbstractOSMObject");
	parent->LinkEndChild(e);

	if (m_id != VicOSM::INVALID_ID)
		e->SetAttribute("id", std::to_string(m_id));
	if (!m_key.empty())
		e->SetAttribute("key", m_key);
	if (!m_value.empty())
		e->SetAttribute("value", m_value);
	if (!m_displayName.empty())
		e->SetAttribute("displayName", m_displayName);

	if (!m_areas.empty()) {
		TiXmlElement * child = new TiXmlElement("Areas");
		e->LinkEndChild(child);

		for (std::vector<Area>::const_iterator it = m_areas.begin();
			 it != m_areas.end(); ++it)
		{
			it->writeXML(child);
		}
	}


	if (!m_linesFromPlanes.empty()) {
		TiXmlElement * child = new TiXmlElement("LinesFromPlanes");
		e->LinkEndChild(child);

		for (std::vector<LineFromPlanes>::const_iterator it = m_linesFromPlanes.begin();
			 it != m_linesFromPlanes.end(); ++it)
		{
			it->writeXML(child);
		}
	}


	if (!m_circles.empty()) {
		TiXmlElement * child = new TiXmlElement("Circles");
		e->LinkEndChild(child);

		for (std::vector<Circle>::const_iterator it = m_circles.begin();
			 it != m_circles.end(); ++it)
		{
			it->writeXML(child);
		}
	}

	return e;
}

} // namespace VicOSM
