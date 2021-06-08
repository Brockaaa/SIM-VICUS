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

#include <NANDRAD_NetworkInterfaceAdapterModel.h>
#include <NANDRAD_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <NANDRAD_Constants.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace NANDRAD {

void NetworkInterfaceAdapterModel::readXML(const TiXmlElement * element) {
	FUNCID(NetworkInterfaceAdapterModel::readXML);

	try {
		// search for mandatory attributes
		if (!TiXmlAttribute::attributeByName(element, "id"))
			throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
				IBK::FormatString("Missing required 'id' attribute.") ), FUNC_ID);

		if (!TiXmlAttribute::attributeByName(element, "summationModelId"))
			throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
				IBK::FormatString("Missing required 'summationModelId' attribute.") ), FUNC_ID);

		// reading attributes
		const TiXmlAttribute * attrib = element->FirstAttribute();
		while (attrib) {
			const std::string & attribName = attrib->NameStr();
			if (attribName == "id")
				m_id = NANDRAD::readPODAttributeValue<unsigned int>(element, attrib);
			else if (attribName == "displayName")
				m_displayName = attrib->ValueStr();
			else if (attribName == "summationModelId")
				m_summationModelId = NANDRAD::readPODAttributeValue<unsigned int>(element, attrib);
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
				NANDRAD::readParameterElement(c, p);
				bool success = false;
				if (p.name == "FluidHeatCapacity") {
					m_fluidHeatCapacity = p; success = true;
				}
				if (!success) {
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'NetworkInterfaceAdapterModel' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'NetworkInterfaceAdapterModel' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * NetworkInterfaceAdapterModel::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("NetworkInterfaceAdapterModel");
	parent->LinkEndChild(e);

	if (m_id != NANDRAD::INVALID_ID)
		e->SetAttribute("id", IBK::val2string<unsigned int>(m_id));
	if (!m_displayName.empty())
		e->SetAttribute("displayName", m_displayName);
	if (m_summationModelId != NANDRAD::INVALID_ID)
		e->SetAttribute("summationModelId", IBK::val2string<unsigned int>(m_summationModelId));
	if (!m_fluidHeatCapacity.name.empty()) {
		IBK_ASSERT("FluidHeatCapacity" == m_fluidHeatCapacity.name);
		TiXmlElement::appendIBKParameterElement(e, "FluidHeatCapacity", m_fluidHeatCapacity.IO_unit.name(), m_fluidHeatCapacity.get_value());
	}
	return e;
}

} // namespace NANDRAD
