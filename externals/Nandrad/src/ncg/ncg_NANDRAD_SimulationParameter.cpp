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

#include <NANDRAD_SimulationParameter.h>
#include <NANDRAD_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <NANDRAD_Constants.h>
#include <NANDRAD_KeywordList.h>
#include <NANDRAD_Utilities.h>

#include <tinyxml.h>

namespace NANDRAD {

void SimulationParameter::readXML(const TiXmlElement * element) {
	FUNCID(SimulationParameter::readXML);

	try {
		// search for mandatory elements
		// reading elements
		const TiXmlElement * c = element->FirstChildElement();
		while (c) {
			const std::string & cName = c->ValueStr();
			if (cName == "IBK:Parameter") {
				IBK::Parameter p;
				NANDRAD::readParameterElement(c, p);
				bool success = false;
				para_t ptype;
				try {
					ptype = (para_t)KeywordList::Enumeration("SimulationParameter::para_t", p.name);
					m_para[ptype] = p; success = true;
				}
				catch (...) { /* intentional fail */  }
				if (!success)
					IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_NAME).arg(p.name).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			else if (cName == "IBK:IntPara") {
				IBK::IntPara p;
				NANDRAD::readIntParaElement(c, p);
				bool success = false;
				try {
					intPara_t ptype = (intPara_t)KeywordList::Enumeration("SimulationParameter::intPara_t", p.name);
					m_intPara[ptype] = p; success = true;
				}
				catch (...) { /* intentional fail */  }
				if (!success)
					IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_NAME).arg(p.name).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			else if (cName == "IBK:Flag") {
				IBK::Flag f;
				NANDRAD::readFlagElement(c, f);
				bool success = false;
				try {
					flag_t ftype = (flag_t)KeywordList::Enumeration("SimulationParameter::flag_t", f.name());
					m_flags[ftype] = f; success=true;
				}
				catch (...) { /* intentional fail */  }
				if (!success)
					IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_NAME).arg(f.name()).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			else if (cName == "ShwradDistributionType") {
				try {
					m_shwradDistributionType = (swrad_distribution_t)KeywordList::Enumeration("SimulationParameter::swrad_distribution_t", c->GetText());
				}
				catch (IBK::Exception & ex) {
					throw IBK::Exception( ex, IBK::FormatString(XML_READ_ERROR).arg(c->Row()).arg(
						IBK::FormatString("Invalid or unknown keyword '"+std::string(c->GetText())+"'.") ), FUNC_ID);
				}
			}
			else if (cName == "Interval")
				m_interval.readXML(c);
			else {
				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			c = c->NextSiblingElement();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'SimulationParameter' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'SimulationParameter' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * SimulationParameter::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("SimulationParameter");
	parent->LinkEndChild(e);


	for (unsigned int i=0; i<NUM_P; ++i) {
		if (!m_para[i].name.empty()) {
			TiXmlElement::appendIBKParameterElement(e, m_para[i].name, m_para[i].IO_unit.name(), m_para[i].get_value());
		}
	}

	for (unsigned int i=0; i<NUM_IP; ++i) {
		if (!m_intPara[i].name.empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:IntPara", "name", m_intPara[i].name, IBK::val2string(m_intPara[i].value));
		}
	}

	for (int i=0; i<NUM_F; ++i) {
		if (!m_flags[i].name().empty()) {
			TiXmlElement::appendSingleAttributeElement(e, "IBK:Flag", "name", m_flags[i].name(), m_flags[i].isEnabled() ? "true" : "false");
		}
	}

	if (m_shwradDistributionType != NUM_SWR)
		TiXmlElement::appendSingleAttributeElement(e, "ShwradDistributionType", nullptr, std::string(), KeywordList::Keyword("SimulationParameter::swrad_distribution_t",  m_shwradDistributionType));

	m_interval.writeXML(e);
	return e;
}

} // namespace NANDRAD
