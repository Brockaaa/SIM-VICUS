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

#include <NANDRAD_EmbeddedObject.h>
#include <NANDRAD_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <NANDRAD_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace NANDRAD {

void EmbeddedObject::readXML(const TiXmlElement * element) {
	FUNCID(EmbeddedObject::readXML);

	try {
		// search for mandatory attributes
		if (!TiXmlAttribute::attributeByName(element, "id"))
			throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
				IBK::FormatString("Missing required 'id' attribute.") ), FUNC_ID);

		// reading attributes
		const TiXmlAttribute * attrib = element->FirstAttribute();
		while (attrib) {
			const std::string & attribName = attrib->NameStr();
			if (attribName == "id")
				m_id = readPODAttributeValue<unsigned int>(element, attrib);
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
			if (cName == "IBK:Parameter") {
				IBK::Parameter p;
				readParameterElement(c, p);
				bool success = false;
				para_t ptype;
				try {
					ptype = (para_t)KeywordList::Enumeration("EmbeddedObject::para_t", p.name);
					m_para[ptype] = p;
					success = true;
				}
				catch (IBK::Exception & ex) { ex.writeMsgStackToError(); }
				if (success) {
					std::string refUnit = KeywordList::Unit("EmbeddedObject::para_t", ptype);
					if (!refUnit.empty() && (p.IO_unit.base_id() != IBK::Unit(refUnit).base_id())) {
						throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(c->Row())
											  .arg("Incompatible unit '"+p.IO_unit.name()+"', expected '"+refUnit +"'."), FUNC_ID);
					}
				}
				if (!success)
					IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_NAME).arg(p.name).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			else {
				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			c = c->NextSiblingElement();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'EmbeddedObject' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'EmbeddedObject' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * EmbeddedObject::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("EmbeddedObject");
	parent->LinkEndChild(e);

	e->SetAttribute("id", IBK::val2string<unsigned int>(m_id));
	if (!m_displayName.empty())
		e->SetAttribute("displayName", m_displayName);

	for (unsigned int i=0; i<NUM_P; ++i) {
		if (!m_para[i].name.empty())
			TiXmlElement::appendIBKParameterElement(e, m_para[i].name, m_para[i].IO_unit.name(), m_para[i].get_value());
	}
	return e;
}

} // namespace NANDRAD
