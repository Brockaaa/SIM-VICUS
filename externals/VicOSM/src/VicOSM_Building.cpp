#include "VicOSM_Building.h"
#include <algorithm>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <VicOSM_Constants.h>
#include <NANDRAD_Utilities.h>

namespace VicOSM {

void OSMBuilding::calculateHeight(const AbstractOSMElement & element, Area& area) const{
	std::string valueLevel = element.getValueFromKey("building:levels");
	if (valueLevel != "") {
		try {
			double valueLevelDouble = std::stod(valueLevel);
			if (valueLevelDouble > 0) area.m_height = valueLevelDouble * m_levelHeight;
		} catch (const std::invalid_argument& e) {
		} catch (const std::out_of_range& e) {
		}
	}

	std::string valueRoof = element.getValueFromKey("roof:levels");
	if (valueRoof != "") {
		try {
			double valueRoofDouble = std::stod(valueRoof);
			if (valueRoofDouble > 0) area.m_height += valueRoofDouble * m_roofHeight;
		} catch (const std::invalid_argument& e) {
		} catch (const std::out_of_range& e) {
		}
	}

	std::string valueEstHeight = element.getValueFromKey("est_height");
	if (valueEstHeight != "") {
		try {
			double valueHeightDouble = std::stod(valueEstHeight);
			area.m_height = valueHeightDouble;
		} catch (const std::invalid_argument& e) {
		} catch (const std::out_of_range& e) {
		}
	}

	std::string valueHeight = element.getValueFromKey("height");
	if (valueHeight != "") {
		try {
			double valueHeightDouble = std::stod(valueHeight);
			area.m_height = valueHeightDouble;
		} catch (const std::invalid_argument& e) {
		} catch (const std::out_of_range& e) {
		}
	}

	std::string valueMinLevel = element.getValueFromKey("building:min_level");
	if (valueMinLevel != "") {
		try {
			double valueMinLevelDouble = std::stod(valueMinLevel);
			if (valueMinLevelDouble > 0) area.m_minHeight = valueMinLevelDouble * m_levelHeight;
		} catch (const std::invalid_argument& e) {
		} catch (const std::out_of_range& e) {
		}
	}

	std::string valueMinHeight = element.getValueFromKey("min_height");
	if (valueMinHeight != "") {
		try {
			double valueMinHeightDouble = std::stod(valueMinHeight);
			area.m_minHeight = valueMinHeightDouble;
		} catch (const std::invalid_argument& e) {
		} catch (const std::out_of_range& e) {
		}
	}
}

bool OSMBuilding::createBuilding(Way & way, bool enable3D) {
	if (way.containsKeyValue("building", "cellar")) return false;
	if (way.containsKeyValue("building", "roof") && !enable3D) return false;
	m_key = "building";
	if (!initialize(way)) return false;
	//if (enable3D) m_layer = 0;
	setDisplayName(way);

	m_areas.push_back(createArea(way, enable3D));
	return true;
}

bool OSMBuilding::createBuilding(Relation & relation, bool enable3D) {
	if (relation.containsKeyValue("building", "cellar")) return false;
	if (relation.containsKeyValue("building", "roof") && !enable3D) return false;
	m_key = "building";
	if (!initialize(relation)) return false;
	//if (enable3D) m_layer = 0;
	setDisplayName(relation);

	m_areas.push_back(createArea(relation, enable3D));
	return true;
}

bool OSMBuilding::initializeSimple3DBuilding(Relation &relation) {
	m_keyValue = BUILDING;
	bool containsBuilding = relation.containsKey("building");
	bool containsBuildingPart = relation.containsKey("building:part");
	bool containsTypeBuilding = relation.containsKeyValue("type", "building");
	if (containsBuilding) {
		m_key = "building";
		m_value = relation.getValueFromKey(m_key);
	}
	if (containsBuildingPart) {
		std::string value = relation.getValueFromKey(m_key);
		if (value != "no") {
			m_key = "building:part";
			m_value = value;
		} else {
			m_key = "building";
			m_value = relation.getValueFromKey(m_key);
		}
	}
	if (containsTypeBuilding) {
		m_key = "type";
		m_value = "building";
	}

	assignEnum();
	return true;
}

Area OSMBuilding::createArea(const AbstractOSMElement & element, bool enable3D) {
	Area area;
	if (enable3D)
		calculateHeight(element, area);

	area.m_extrudingPolygon = enable3D;
	area.m_color = QColor("#b3a294");

	return area;
}

void OSMBuilding::setDisplayName(const AbstractOSMElement& element) {
	QString displayName;
	if (element.containsKey("addr:street") && element.containsKey("addr:housenumber")) {
		displayName = QString("%1 %2").arg(QString::fromStdString(element.getValueFromKey("addr:street")), QString::fromStdString(element.getValueFromKey("addr:housenumber")));
	}
	if (element.containsKey("name")) {
		std::string name = element.getValueFromKey("name");
		if (name != "") {
			if (displayName.isEmpty()) {
				displayName = QString::fromStdString(name);
			} else {
				displayName += QString(", %1").arg(QString::fromStdString(name));
			}
		}
	}
	m_displayName = displayName.toStdString();
}

void OSMBuilding::setVisible(bool visible) {
	AbstractOSMObject::setVisible(visible);
	m_dirtyLayer = true;
	for (auto& area : m_areas)
		area.m_dirtyTriangulation = true;
}

void OSMBuilding::setSelected(bool selected) {
	AbstractOSMObject::setSelected(selected);
	for (auto& area : m_areas)
		area.m_dirtyTriangulation = true;
}

void OSMBuilding::readXML(const TiXmlElement * element) {
	FUNCID(OSMBuilding::readXML);

	try {
		// search for mandatory attributes
		// reading attributes
		const TiXmlAttribute * attrib = element->FirstAttribute();
		while (attrib) {
			const std::string & attribName = attrib->NameStr();
			if (attribName == "id")
				m_id = atol(attrib->Value());
			if (attribName == "key")
				m_key = attrib->ValueStr();
			else if (attribName == "value")
				m_value = attrib->ValueStr();
			else if (attribName == "displayName")
				m_displayName = attrib->ValueStr();
			else if (attribName == "zPosition")
				m_zPosition = NANDRAD::readPODAttributeValue<double>(element, attrib);
			else if (attribName == "levelHeight")
				m_levelHeight = NANDRAD::readPODAttributeValue<double>(element, attrib);
			else if (attribName == "roofHeight")
				m_roofHeight = NANDRAD::readPODAttributeValue<double>(element, attrib);
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
			else if (cName == "Outlines") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "Area")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					Area obj;
					obj.readXML(c2);
					m_outlines.push_back(obj);
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'OSMBuilding' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'OSMBuilding' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * OSMBuilding::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("OSMBuilding");
	parent->LinkEndChild(e);

	if (m_id != VicOSM::INVALID_ID)
		e->SetAttribute("id", std::to_string(m_id));
	if (!m_key.empty())
		e->SetAttribute("key", m_key);
	if (!m_value.empty())
		e->SetAttribute("value", m_value);
	if (!m_displayName.empty())
		e->SetAttribute("displayName", m_displayName);
	e->SetAttribute("zPosition", IBK::val2string<double>(m_zPosition));
	e->SetAttribute("levelHeight", IBK::val2string<double>(m_levelHeight));
	e->SetAttribute("roofHeight", IBK::val2string<double>(m_roofHeight));

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


	if (!m_outlines.empty()) {
		TiXmlElement * child = new TiXmlElement("Outlines");
		e->LinkEndChild(child);

		for (std::vector<Area>::const_iterator it = m_outlines.begin();
			 it != m_outlines.end(); ++it)
		{
			it->writeXML(child);
		}
	}

	return e;
}

} // namespace VicOSM
