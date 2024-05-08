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

#include <VICUS_NetworkHeatExchange.h>
#include <VICUS_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <VICUS_Constants.h>
#include <NANDRAD_Utilities.h>
#include <VICUS_KeywordList.h>

#include <tinyxml.h>

namespace VICUS {

void NetworkHeatExchange::readXML(const TiXmlElement * element) {
	FUNCID(NetworkHeatExchange::readXML);

	try {
		// search for mandatory attributes
		// reading attributes
		const TiXmlAttribute * attrib = element->FirstAttribute();
		while (attrib) {
			const std::string & attribName = attrib->NameStr();
			if (attribName == "individualHeatFlux")
				m_individualHeatFlux = NANDRAD::readPODAttributeValue<bool>(element, attrib);
			else if (attribName == "areaRelatedValues")
				m_areaRelatedValues = NANDRAD::readPODAttributeValue<bool>(element, attrib);
			else if (attribName == "withCoolingDemand")
				m_withCoolingDemand = NANDRAD::readPODAttributeValue<bool>(element, attrib);
			else if (attribName == "withDomesticHotWaterDemand")
				m_withDomesticHotWaterDemand = NANDRAD::readPODAttributeValue<bool>(element, attrib);
			else if (attribName == "buildingType")
				try {
					m_buildingType = (BuildingType)KeywordList::Enumeration("NetworkHeatExchange::BuildingType", attrib->ValueStr());
				}
				catch (IBK::Exception & ex) {
					throw IBK::Exception( ex, IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
						IBK::FormatString("Invalid or unknown keyword '"+attrib->ValueStr()+"'.") ), FUNC_ID);
				}
			else if (attribName == "ambientTemperatureType")
				try {
					m_ambientTemperatureType = (AmbientTemperatureType)KeywordList::Enumeration("NetworkHeatExchange::AmbientTemperatureType", attrib->ValueStr());
				}
				catch (IBK::Exception & ex) {
					throw IBK::Exception( ex, IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
						IBK::FormatString("Invalid or unknown keyword '"+attrib->ValueStr()+"'.") ), FUNC_ID);
				}
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
			if (cName == "LinearSplineParameter") {
				NANDRAD::LinearSplineParameter p;
				p.readXML(c);
				bool success = false;
				if (p.m_name == "UserDefinedHeatFlux") {
					m_userDefinedHeatFlux = p; success = true;
				}
				try {
					splinePara_t ptype;
					ptype = (splinePara_t)KeywordList::Enumeration("NetworkHeatExchange::splinePara_t", p.m_name);
					m_splPara[ptype] = p; success = true;
				}
				catch (...) { /* intentional fail */  }
				if (!success)
					IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_NAME).arg(p.m_name).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			else if (cName == "IBK:Parameter") {
				IBK::Parameter p;
				NANDRAD::readParameterElement(c, p);
				bool success = false;
				para_t ptype;
				try {
					ptype = (para_t)KeywordList::Enumeration("NetworkHeatExchange::para_t", p.name);
					m_para[ptype] = p; success = true;
				}
				catch (...) { /* intentional fail */  }
				if (!success)
					IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_NAME).arg(p.name).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			else if (cName == "UserDefinedTsvFile")
				m_userDefinedTsvFile = IBK::Path(c->GetText());
			else if (cName == "ModelType") {
				try {
					m_modelType = (ModelType)KeywordList::Enumeration("NetworkHeatExchange::ModelType", c->GetText());
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
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'NetworkHeatExchange' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'NetworkHeatExchange' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * NetworkHeatExchange::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("NetworkHeatExchange");
	parent->LinkEndChild(e);

	if (m_individualHeatFlux != NetworkHeatExchange().m_individualHeatFlux)
		e->SetAttribute("individualHeatFlux", IBK::val2string<bool>(m_individualHeatFlux));
	if (m_areaRelatedValues != NetworkHeatExchange().m_areaRelatedValues)
		e->SetAttribute("areaRelatedValues", IBK::val2string<bool>(m_areaRelatedValues));
	if (m_withCoolingDemand != NetworkHeatExchange().m_withCoolingDemand)
		e->SetAttribute("withCoolingDemand", IBK::val2string<bool>(m_withCoolingDemand));
	if (m_withDomesticHotWaterDemand != NetworkHeatExchange().m_withDomesticHotWaterDemand)
		e->SetAttribute("withDomesticHotWaterDemand", IBK::val2string<bool>(m_withDomesticHotWaterDemand));
	if (m_buildingType != NUM_BT)
		e->SetAttribute("buildingType", KeywordList::Keyword("NetworkHeatExchange::BuildingType",  m_buildingType));
	if (m_ambientTemperatureType != NUM_AT)
		e->SetAttribute("ambientTemperatureType", KeywordList::Keyword("NetworkHeatExchange::AmbientTemperatureType",  m_ambientTemperatureType));

	if (m_modelType != NUM_T)
		TiXmlElement::appendSingleAttributeElement(e, "ModelType", nullptr, std::string(), KeywordList::Keyword("NetworkHeatExchange::ModelType",  m_modelType));
	if (!m_userDefinedHeatFlux.m_name.empty()) {
		IBK_ASSERT("UserDefinedHeatFlux" == m_userDefinedHeatFlux.m_name);
		m_userDefinedHeatFlux.writeXML(e);
	}

	for (unsigned int i=0; i<NUM_P; ++i) {
		if (!m_para[i].name.empty()) {
			TiXmlElement::appendIBKParameterElement(e, m_para[i].name, m_para[i].IO_unit.name(), m_para[i].get_value(m_para[i].IO_unit));
		}
	}
	for (int i=0; i<NUM_SPL; ++i) {
		if (!m_splPara[i].m_name.empty()) {
			m_splPara[i].writeXML(e);
		}
	}
	if (m_userDefinedTsvFile.isValid())
		TiXmlElement::appendSingleAttributeElement(e, "UserDefinedTsvFile", nullptr, std::string(), m_userDefinedTsvFile.str());
	return e;
}

} // namespace VICUS
