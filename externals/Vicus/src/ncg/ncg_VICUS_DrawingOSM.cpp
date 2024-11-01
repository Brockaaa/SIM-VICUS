/*	The NANDRAD data model library.

	Copyright (c) 2012-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
	  Anne Paepcke     <anne.paepcke -[at]- tu-dresden.de>

	This library is part of SIM-VICUS (https://github.com/ghorwin/SIM-VICUS)

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 3 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.
*/

#include <VICUS_DrawingOSM.h>
#include <VICUS_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <VICUS_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace VICUS {

void DrawingOSM::readXML(const TiXmlElement * element) {
	FUNCID(DrawingOSM::readXML);

	try {
		// search for mandatory attributes
		// reading attributes
		const TiXmlAttribute * attrib = element->FirstAttribute();
		while (attrib) {
			const std::string & attribName = attrib->NameStr();
			if (attribName == "utmZone")
				m_utmZone = NANDRAD::readPODAttributeValue<int>(element, attrib);
			else if (attribName == "centerX")
				m_centerX = NANDRAD::readPODAttributeValue<double>(element, attrib);
			else if (attribName == "centerY")
				m_centerY = NANDRAD::readPODAttributeValue<double>(element, attrib);
			else if (attribName == "enable3DBuildings")
				m_enable3DBuildings = NANDRAD::readPODAttributeValue<bool>(element, attrib);
			else if (attribName == "addedToProject")
				m_addedToProject = NANDRAD::readPODAttributeValue<bool>(element, attrib);
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
			if (cName == "Buildings") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "OSMBuilding")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					OSMBuilding obj;
					obj.readXML(c2);
					m_buildings.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "Highways") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "Highway")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					Highway obj;
					obj.readXML(c2);
					m_highways.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "Waters") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "Water")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					Water obj;
					obj.readXML(c2);
					m_waters.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "Land") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "Land")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					Land obj;
					obj.readXML(c2);
					m_land.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "Leisure") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "Leisure")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					Leisure obj;
					obj.readXML(c2);
					m_leisure.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "Natural") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "Natural")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					Natural obj;
					obj.readXML(c2);
					m_natural.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "Amenities") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "Amenity")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					Amenity obj;
					obj.readXML(c2);
					m_amenities.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "Places") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "Place")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					Place obj;
					obj.readXML(c2);
					m_places.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "Bridges") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "Bridge")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					Bridge obj;
					obj.readXML(c2);
					m_bridges.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "Tourism") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "Tourism")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					Tourism obj;
					obj.readXML(c2);
					m_tourism.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "Barriers") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "Barrier")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					Barrier obj;
					obj.readXML(c2);
					m_barriers.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "Railways") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "Railway")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					Railway obj;
					obj.readXML(c2);
					m_railways.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "BoundingBox")
				m_boundingBox.readXML(c);
			else {
				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			c = c->NextSiblingElement();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'DrawingOSM' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'DrawingOSM' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * DrawingOSM::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("DrawingOSM");
	parent->LinkEndChild(e);

	e->SetAttribute("utmZone", IBK::val2string<int>(m_utmZone));
	e->SetAttribute("centerX", IBK::val2string<double>(m_centerX));
	e->SetAttribute("centerY", IBK::val2string<double>(m_centerY));
	if (m_enable3DBuildings != DrawingOSM().m_enable3DBuildings)
		e->SetAttribute("enable3DBuildings", IBK::val2string<bool>(m_enable3DBuildings));
	if (m_addedToProject != DrawingOSM().m_addedToProject)
		e->SetAttribute("addedToProject", IBK::val2string<bool>(m_addedToProject));

	m_boundingBox.writeXML(e);

	if (!m_buildings.empty()) {
		TiXmlElement * child = new TiXmlElement("Buildings");
		e->LinkEndChild(child);

		for (std::vector<OSMBuilding>::const_iterator it = m_buildings.begin();
			it != m_buildings.end(); ++it)
		{
			it->writeXML(child);
		}
	}


	if (!m_highways.empty()) {
		TiXmlElement * child = new TiXmlElement("Highways");
		e->LinkEndChild(child);

		for (std::vector<Highway>::const_iterator it = m_highways.begin();
			it != m_highways.end(); ++it)
		{
			it->writeXML(child);
		}
	}


	if (!m_waters.empty()) {
		TiXmlElement * child = new TiXmlElement("Waters");
		e->LinkEndChild(child);

		for (std::vector<Water>::const_iterator it = m_waters.begin();
			it != m_waters.end(); ++it)
		{
			it->writeXML(child);
		}
	}


	if (!m_land.empty()) {
		TiXmlElement * child = new TiXmlElement("Land");
		e->LinkEndChild(child);

		for (std::vector<Land>::const_iterator it = m_land.begin();
			it != m_land.end(); ++it)
		{
			it->writeXML(child);
		}
	}


	if (!m_leisure.empty()) {
		TiXmlElement * child = new TiXmlElement("Leisure");
		e->LinkEndChild(child);

		for (std::vector<Leisure>::const_iterator it = m_leisure.begin();
			it != m_leisure.end(); ++it)
		{
			it->writeXML(child);
		}
	}


	if (!m_natural.empty()) {
		TiXmlElement * child = new TiXmlElement("Natural");
		e->LinkEndChild(child);

		for (std::vector<Natural>::const_iterator it = m_natural.begin();
			it != m_natural.end(); ++it)
		{
			it->writeXML(child);
		}
	}


	if (!m_amenities.empty()) {
		TiXmlElement * child = new TiXmlElement("Amenities");
		e->LinkEndChild(child);

		for (std::vector<Amenity>::const_iterator it = m_amenities.begin();
			it != m_amenities.end(); ++it)
		{
			it->writeXML(child);
		}
	}


	if (!m_places.empty()) {
		TiXmlElement * child = new TiXmlElement("Places");
		e->LinkEndChild(child);

		for (std::vector<Place>::const_iterator it = m_places.begin();
			it != m_places.end(); ++it)
		{
			it->writeXML(child);
		}
	}


	if (!m_bridges.empty()) {
		TiXmlElement * child = new TiXmlElement("Bridges");
		e->LinkEndChild(child);

		for (std::vector<Bridge>::const_iterator it = m_bridges.begin();
			it != m_bridges.end(); ++it)
		{
			it->writeXML(child);
		}
	}


	if (!m_tourism.empty()) {
		TiXmlElement * child = new TiXmlElement("Tourism");
		e->LinkEndChild(child);

		for (std::vector<Tourism>::const_iterator it = m_tourism.begin();
			it != m_tourism.end(); ++it)
		{
			it->writeXML(child);
		}
	}


	if (!m_barriers.empty()) {
		TiXmlElement * child = new TiXmlElement("Barriers");
		e->LinkEndChild(child);

		for (std::vector<Barrier>::const_iterator it = m_barriers.begin();
			it != m_barriers.end(); ++it)
		{
			it->writeXML(child);
		}
	}


	if (!m_railways.empty()) {
		TiXmlElement * child = new TiXmlElement("Railways");
		e->LinkEndChild(child);

		for (std::vector<Railway>::const_iterator it = m_railways.begin();
			it != m_railways.end(); ++it)
		{
			it->writeXML(child);
		}
	}

	return e;
}

} // namespace VICUS
