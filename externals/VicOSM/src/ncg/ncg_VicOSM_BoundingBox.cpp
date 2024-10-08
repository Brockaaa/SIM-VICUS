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

#include <VicOSM_BoundingBox.h>
#include <VicOSM_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <VicOSM_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace VicOSM {

void BoundingBox::readXML(const TiXmlElement * element) {
	FUNCID(BoundingBox::readXML);

	try {
		// search for mandatory attributes
		// reading attributes
		const TiXmlAttribute * attrib = element->FirstAttribute();
		while (attrib) {
			const std::string & attribName = attrib->NameStr();
			if (attribName == "minlat")
				m_minlat = NANDRAD::readPODAttributeValue<double>(element, attrib);
			else if (attribName == "maxlat")
				m_maxlat = NANDRAD::readPODAttributeValue<double>(element, attrib);
			else if (attribName == "minlon")
				m_minlon = NANDRAD::readPODAttributeValue<double>(element, attrib);
			else if (attribName == "maxlon")
				m_maxlon = NANDRAD::readPODAttributeValue<double>(element, attrib);
			else if (attribName == "zPosition")
				m_zPosition = NANDRAD::readPODAttributeValue<double>(element, attrib);
			else {
				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ATTRIBUTE).arg(attribName).arg(element->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			attrib = attrib->Next();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'BoundingBox' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'BoundingBox' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * BoundingBox::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("BoundingBox");
	parent->LinkEndChild(e);

	e->SetAttribute("minlat", IBK::val2string<double>(m_minlat));
	e->SetAttribute("maxlat", IBK::val2string<double>(m_maxlat));
	e->SetAttribute("minlon", IBK::val2string<double>(m_minlon));
	e->SetAttribute("maxlon", IBK::val2string<double>(m_maxlon));
	e->SetAttribute("zPosition", IBK::val2string<double>(m_zPosition));
	return e;
}

} // namespace VicOSM
