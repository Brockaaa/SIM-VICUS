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

#include <VICUS_Network.h>
#include <VICUS_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <VICUS_Constants.h>
#include <IBKMK_Vector3D.h>
#include <IBK_StringUtils.h>
#include <NANDRAD_Utilities.h>
#include <VICUS_KeywordList.h>
#include <vector>

#include <tinyxml.h>

namespace VICUS {

void Network::readXML(const TiXmlElement * element) {
	FUNCID(Network::readXML);

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
				m_id = NANDRAD::readPODAttributeValue<unsigned int>(element, attrib);
			else if (attribName == "fluidID")
				m_fluidID = NANDRAD::readPODAttributeValue<unsigned int>(element, attrib);
			else if (attribName == "displayName")
				m_displayName = QString::fromStdString(attrib->ValueStr());
			else if (attribName == "visible")
				m_visible = NANDRAD::readPODAttributeValue<bool>(element, attrib);
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
			if (cName == "Nodes") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "NetworkNode")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					NetworkNode obj;
					obj.readXML(c2);
					m_nodes.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "Edges") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "NetworkEdge")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					NetworkEdge obj;
					obj.readXML(c2);
					m_edges.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "AvailablePipes")
				NANDRAD::readVector(c, "AvailablePipes", m_availablePipes);
			else if (cName == "Origin") {
				try {
					std::vector<double> vals;
					IBK::string2valueVector(c->GetText(), vals);
					// must have 3 elements
					if (vals.size() != 3)
						throw IBK::Exception("Missing values (expected 3).", FUNC_ID);
					m_origin.set(vals[0], vals[1], vals[2]);
				} catch (IBK::Exception & ex) {
					throw IBK::Exception( ex, IBK::FormatString(XML_READ_ERROR).arg(c->Row())
										  .arg("Invalid vector data."), FUNC_ID);
				}
			}
			else if (cName == "HydraulicSubNetworks") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "HydraulicNetwork")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					NANDRAD::HydraulicNetwork obj;
					obj.readXML(c2);
					m_hydraulicSubNetworks.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "IBK:Parameter") {
				IBK::Parameter p;
				NANDRAD::readParameterElement(c, p);
				bool success = false;
				para_t ptype;
				try {
					ptype = (para_t)KeywordList::Enumeration("Network::para_t", p.name);
					m_para[ptype] = p; success = true;
				}
				catch (...) { /* intentional fail */  }
				if (!success)
					IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_NAME).arg(p.name).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			else if (cName == "ScaleNodes")
				m_scaleNodes = NANDRAD::readPODElement<double>(c, cName);
			else if (cName == "ScaleEdges")
				m_scaleEdges = NANDRAD::readPODElement<double>(c, cName);
			else if (cName == "Controllers") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "NetworkController")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					VICUS::NetworkController obj;
					obj.readXML(c2);
					m_controllers.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "Type") {
				try {
					m_type = (NetworkType)KeywordList::Enumeration("Network::NetworkType", c->GetText());
				}
				catch (IBK::Exception & ex) {
					throw IBK::Exception( ex, IBK::FormatString(XML_READ_ERROR).arg(c->Row()).arg(
						IBK::FormatString("Invalid or unknown keyword '"+std::string(c->GetText())+"'.") ), FUNC_ID);
				}
			}
			else {
				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			c = c->NextSiblingElement();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Network' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Network' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Network::writeXML(TiXmlElement * parent) const {
	if (m_id == VICUS::INVALID_ID)  return nullptr;
	TiXmlElement * e = new TiXmlElement("Network");
	parent->LinkEndChild(e);

	if (m_id != VICUS::INVALID_ID)
		e->SetAttribute("id", IBK::val2string<unsigned int>(m_id));
	if (m_fluidID != VICUS::INVALID_ID)
		e->SetAttribute("fluidID", IBK::val2string<unsigned int>(m_fluidID));
	if (!m_displayName.isEmpty())
		e->SetAttribute("displayName", m_displayName.toStdString());
	if (m_visible != Network().m_visible)
		e->SetAttribute("visible", IBK::val2string<bool>(m_visible));

	if (!m_nodes.empty()) {
		TiXmlElement * child = new TiXmlElement("Nodes");
		e->LinkEndChild(child);

		for (std::vector<NetworkNode>::const_iterator it = m_nodes.begin();
			it != m_nodes.end(); ++it)
		{
			it->writeXML(child);
		}
	}


	if (!m_edges.empty()) {
		TiXmlElement * child = new TiXmlElement("Edges");
		e->LinkEndChild(child);

		for (std::vector<NetworkEdge>::const_iterator it = m_edges.begin();
			it != m_edges.end(); ++it)
		{
			it->writeXML(child);
		}
	}

	NANDRAD::writeVector(e, "AvailablePipes", m_availablePipes);
	{
		std::vector<double> v = { m_origin.m_x, m_origin.m_y, m_origin.m_z};
		TiXmlElement::appendSingleAttributeElement(e, "Origin", nullptr, std::string(), IBK::vector2string<double>(v," "));
	}

	if (!m_hydraulicSubNetworks.empty()) {
		TiXmlElement * child = new TiXmlElement("HydraulicSubNetworks");
		e->LinkEndChild(child);

		for (std::vector<NANDRAD::HydraulicNetwork>::const_iterator it = m_hydraulicSubNetworks.begin();
			it != m_hydraulicSubNetworks.end(); ++it)
		{
			it->writeXML(child);
		}
	}


	if (m_type != NUM_NET)
		TiXmlElement::appendSingleAttributeElement(e, "Type", nullptr, std::string(), KeywordList::Keyword("Network::NetworkType",  m_type));

	for (unsigned int i=0; i<NUM_P; ++i) {
		if (!m_para[i].name.empty()) {
			TiXmlElement::appendIBKParameterElement(e, m_para[i].name, m_para[i].IO_unit.name(), m_para[i].get_value());
		}
	}
	TiXmlElement::appendSingleAttributeElement(e, "ScaleNodes", nullptr, std::string(), IBK::val2string<double>(m_scaleNodes));
	TiXmlElement::appendSingleAttributeElement(e, "ScaleEdges", nullptr, std::string(), IBK::val2string<double>(m_scaleEdges));

	if (!m_controllers.empty()) {
		TiXmlElement * child = new TiXmlElement("Controllers");
		e->LinkEndChild(child);

		for (std::vector<VICUS::NetworkController>::const_iterator it = m_controllers.begin();
			it != m_controllers.end(); ++it)
		{
			it->writeXML(child);
		}
	}

	return e;
}

} // namespace VICUS
