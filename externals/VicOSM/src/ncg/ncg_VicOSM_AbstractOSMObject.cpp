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

#include <VicOSM_AbstractOSMObject.h>
#include <VicOSM_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <VicOSM_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace VicOSM {

void AbstractOSMObject::readXML(const TiXmlElement * element) {
	FUNCID(AbstractOSMObject::readXML);

	try {
		// search for mandatory attributes
		// reading attributes
		const TiXmlAttribute * attrib = element->FirstAttribute();
		while (attrib) {
			const std::string & attribName = attrib->NameStr();
			if (attribName == "id")
				m_id = NANDRAD::readPODAttributeValue<unsigned int>(element, attrib);
			else if (attribName == "key")
				m_key = attrib->ValueStr();
			else if (attribName == "value")
				m_value = attrib->ValueStr();
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
		e->SetAttribute("id", IBK::val2string<unsigned int>(m_id));
	if (!m_key.empty())
		e->SetAttribute("key", m_key);
	if (!m_value.empty())
		e->SetAttribute("value", m_value);

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
