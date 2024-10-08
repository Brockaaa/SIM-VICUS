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

#include <VicOSM_Circle.h>
#include <VicOSM_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <VicOSM_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace VicOSM {

void Circle::readXML(const TiXmlElement * element) {
	FUNCID(Circle::readXML);

	try {
		// search for mandatory attributes
		// reading attributes
		const TiXmlAttribute * attrib = element->FirstAttribute();
		while (attrib) {
			const std::string & attribName = attrib->NameStr();
			if (attribName == "x")
				m_x = NANDRAD::readPODAttributeValue<double>(element, attrib);
			else if (attribName == "y")
				m_y = NANDRAD::readPODAttributeValue<double>(element, attrib);
			else if (attribName == "radius")
				m_radius = NANDRAD::readPODAttributeValue<double>(element, attrib);
			else if (attribName == "color")
				m_color.setNamedColor(QString::fromStdString(attrib->ValueStr()));
			else {
				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ATTRIBUTE).arg(attribName).arg(element->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			attrib = attrib->Next();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Circle' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Circle' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Circle::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Circle");
	parent->LinkEndChild(e);

	e->SetAttribute("x", IBK::val2string<double>(m_x));
	e->SetAttribute("y", IBK::val2string<double>(m_y));
	e->SetAttribute("radius", IBK::val2string<double>(m_radius));
	if (m_color.isValid())
		e->SetAttribute("color", m_color.name().toStdString());
	return e;
}

} // namespace VicOSM
