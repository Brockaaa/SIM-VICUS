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

#include <VICUS_Project.h>
#include <VICUS_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <VICUS_Constants.h>

#include <tinyxml.h>

namespace VICUS {

void Project::readXML(const TiXmlElement * element) {
	FUNCID(Project::readXML);

	try {
		// search for mandatory elements
		// reading elements
		const TiXmlElement * c = element->FirstChildElement();
		while (c) {
			const std::string & cName = c->ValueStr();
			if (cName == "GeometricNetworks") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "Network")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					Network obj;
					obj.readXML(c2);
					m_geometricNetworks.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "Buildings") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "Building")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					Building obj;
					obj.readXML(c2);
					m_buildings.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "PlainGeometry") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "Surface")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					Surface obj;
					obj.readXML(c2);
					m_plainGeometry.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "NetworkFluids") {
				const TiXmlElement * c2 = c->FirstChildElement();
				while (c2) {
					const std::string & c2Name = c2->ValueStr();
					if (c2Name != "NetworkFluid")
						IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(c2Name).arg(c2->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
					NetworkFluid obj;
					obj.readXML(c2);
					m_networkFluids.push_back(obj);
					c2 = c2->NextSiblingElement();
				}
			}
			else if (cName == "SolverParameter")
				m_solverParameter.readXML(c);
			else if (cName == "SimulationParameter")
				m_simulationParameter.readXML(c);
			else if (cName == "Location")
				m_location.readXML(c);
			else if (cName == "VICUS::Outputs")
				m_outputs.readXML(c);
			else if (cName == "ViewSettings")
				m_viewSettings.readXML(c);
			else {
				IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			c = c->NextSiblingElement();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Project' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Project' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * Project::writeXML(TiXmlElement * parent) const {
	TiXmlElement * e = new TiXmlElement("Project");
	parent->LinkEndChild(e);


	m_solverParameter.writeXML(e);

	m_simulationParameter.writeXML(e);

	m_location.writeXML(e);

	m_outputs.writeXML(e);

	m_viewSettings.writeXML(e);

	if (!m_geometricNetworks.empty()) {
		TiXmlElement * child = new TiXmlElement("GeometricNetworks");
		e->LinkEndChild(child);

		for (std::vector<Network>::const_iterator it = m_geometricNetworks.begin();
			it != m_geometricNetworks.end(); ++it)
		{
			it->writeXML(child);
		}
	}


	if (!m_buildings.empty()) {
		TiXmlElement * child = new TiXmlElement("Buildings");
		e->LinkEndChild(child);

		for (std::vector<Building>::const_iterator it = m_buildings.begin();
			it != m_buildings.end(); ++it)
		{
			it->writeXML(child);
		}
	}


	if (!m_plainGeometry.empty()) {
		TiXmlElement * child = new TiXmlElement("PlainGeometry");
		e->LinkEndChild(child);

		for (std::vector<Surface>::const_iterator it = m_plainGeometry.begin();
			it != m_plainGeometry.end(); ++it)
		{
			it->writeXML(child);
		}
	}


	if (!m_networkFluids.empty()) {
		TiXmlElement * child = new TiXmlElement("NetworkFluids");
		e->LinkEndChild(child);

		for (std::vector<NetworkFluid>::const_iterator it = m_networkFluids.begin();
			it != m_networkFluids.end(); ++it)
		{
			it->writeXML(child);
		}
	}

	return e;
}

} // namespace VICUS
