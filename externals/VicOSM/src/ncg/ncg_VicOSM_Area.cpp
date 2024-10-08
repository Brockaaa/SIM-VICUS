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

#include <VicOSM_Area.h>
#include <VicOSM_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <VicOSM_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace VicOSM {

void Area::readXML(const TiXmlElement * element) {
	FUNCID(Area::readXML);

	try {
		// search for mandatory attributes
		// reading attributes
		const TiXmlAttribute * attrib = element->FirstAttribute();
		while (attrib) {
			const std::string & attribName = attrib->NameStr();
			if (attribName == "extrudingPolygon")
				m_extrudingPolygon = NANDRAD::readPODAttributeValue<bool>(element, attrib);
			else if (attribName == "height")
				m_height = NANDRAD::readPODAttributeValue<double>(element, attrib);
			else if (attribName == "minHeight")
				m_minHeight = NANDRAD::readPODAttributeValue<double>(element, attrib);
			else if (attribName == "color")
				m_color.setNamedColor(QString::fromStdString(attrib->ValueStr()));
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
			if (cName == "Multipolygon")
				m_multiPolygon.readXML(c);
			else {
				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			c = c->NextSiblingElement();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Area' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Area' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Area::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Area");
	parent->LinkEndChild(e);

	if (m_extrudingPolygon != Area().m_extrudingPolygon)
		e->SetAttribute("extrudingPolygon", IBK::val2string<bool>(m_extrudingPolygon));
	e->SetAttribute("height", IBK::val2string<double>(m_height));
	e->SetAttribute("minHeight", IBK::val2string<double>(m_minHeight));
	if (m_color.isValid())
		e->SetAttribute("color", m_color.name().toStdString());

	m_multiPolygon.writeXML(e);
	return e;
}

} // namespace VicOSM
