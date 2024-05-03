#include "VICUS_NetworkController.h"

#include "VICUS_KeywordList.h"

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <VICUS_Constants.h>
#include <NANDRAD_Utilities.h>
#include <VICUS_KeywordList.h>

#include <tinyxml.h>

namespace VICUS {


NetworkController::NetworkController(){
	// set default value
	m_para[P_RelControllerErrorForIntegratorReset] = IBK::Parameter("RelControllerErrorForIntegratorReset", 0.7, "---");
}

void NetworkController::readXML(const TiXmlElement * element)
{
	FUNCID(NetworkController::readXML);

	try {
		// reading attributes
		const TiXmlAttribute * attrib = element->FirstAttribute();
		while (attrib) {
			const std::string & attribName = attrib->NameStr();
			if (attribName == "id")
				m_id = NANDRAD::readPODAttributeValue<unsigned int>(element, attrib);
			else if (attribName == "displayName")
				m_displayName.setEncodedString(attrib->ValueStr());
			else if (attribName == "color")
				m_color.setNamedColor(QString::fromStdString(attrib->ValueStr()));
			else if (attribName == "modelType")
				try {
					m_modelType = (ModelType)KeywordList::Enumeration("NetworkController::ModelType", attrib->ValueStr());
				}
				catch (IBK::Exception & ex) {
					throw IBK::Exception( ex, IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
												 IBK::FormatString("Invalid or unknown keyword '"+attrib->ValueStr()+"'.") ), FUNC_ID);
				}
			else if (attribName == "controllerType")
				try {
					m_controllerType = (ControllerType)KeywordList::Enumeration("NetworkController::ControllerType", attrib->ValueStr());
				}
				catch (IBK::Exception & ex) {
					throw IBK::Exception( ex, IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
												 IBK::FormatString("Invalid or unknown keyword '"+attrib->ValueStr()+"'.") ), FUNC_ID);
				}
			else if (attribName == "controlledProperty")
				try {
					m_controlledProperty = (ControlledProperty)KeywordList::Enumeration("NetworkController::ControlledProperty", attrib->ValueStr());
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
			if (cName == "MaximumControllerResultValue")
				m_maximumControllerResultValue = NANDRAD::readPODElement<double>(c, cName);
			else if (cName == "IBK:Parameter") {
				IBK::Parameter p;
				NANDRAD::readParameterElement(c, p);
				bool success = false;
				para_t ptype;
				try {
					ptype = (para_t)KeywordList::Enumeration("NetworkController::para_t", p.name);
					m_para[ptype] = p; success = true;
				}
				catch (...) { /* intentional fail */  }
				if (!success)
					IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_NAME).arg(p.name).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			else {
				bool found = false;
				for (int i=0; i<NUM_ID; ++i) {
					if (cName == KeywordList::Keyword("NetworkController::References",i)) {
						m_idReferences[i] = (IDType)NANDRAD::readPODElement<unsigned int>(c, cName);
						found = true;
						break;
					}
				}
				if (!found)
					IBK::IBK_Message(IBK::FormatString(XML_READ_UNKNOWN_ELEMENT).arg(cName).arg(c->Row()), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
			}
			c = c->NextSiblingElement();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'NetworkController' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'NetworkController' element.").arg(ex2.what()), FUNC_ID);
	}
}

TiXmlElement * NetworkController::writeXML(TiXmlElement * parent) const
{
	TiXmlElement * e = new TiXmlElement("NetworkController");
	parent->LinkEndChild(e);
	if(this->m_modelType == NUM_MT || this->m_controlledProperty == NUM_CP) return e;

	if (!m_displayName.empty())
		e->SetAttribute("displayName", m_displayName.encodedString());
	if (m_color.isValid())
		e->SetAttribute("color", m_color.name().toStdString());
	if (m_modelType != NUM_MT)
		e->SetAttribute("modelType", KeywordList::Keyword("NetworkController::ModelType",  m_modelType));
	if (m_controllerType != NUM_CT)
		e->SetAttribute("controllerType", KeywordList::Keyword("NetworkController::ControllerType",  m_controllerType));
	if (m_controlledProperty != NUM_CP)
		e->SetAttribute("controlledProperty", KeywordList::Keyword("NetworkController::ControlledProperty",  m_controlledProperty));

	for (int i=0; i<NUM_ID; ++i) {
		if (m_idReferences[i] != VICUS::INVALID_ID)
			TiXmlElement::appendSingleAttributeElement(e, KeywordList::Keyword("NetworkController::References",  i), nullptr, std::string(), IBK::val2string<unsigned int>(m_idReferences[i]));
	}
	TiXmlElement::appendSingleAttributeElement(e, "MaximumControllerResultValue", nullptr, std::string(), IBK::val2string<double>(m_maximumControllerResultValue));

	for (unsigned int i=0; i<NUM_P; ++i) {
		if (!m_para[i].name.empty()) {
			TiXmlElement::appendIBKParameterElement(e, m_para[i].name, m_para[i].IO_unit.name(), m_para[i].get_value(m_para[i].IO_unit));
		}
	}
	return e;
}

bool NetworkController::isValid(const Database<Schedule> &scheduleDB) const {

	std::string err;
	// call check function of NANDRAD::HydraulicNetworkControlElement
	try {
		// TODO Hauke:
		// we should know the zone ids here for complete check!
		checkParameters();
	} catch (...) {
		return false;
	}

	// check if schedule exists
	if (m_modelType == MT_Scheduled){
		const Schedule * setPointSched = scheduleDB[m_idReferences[VICUS::NetworkController::ID_Schedule]];
		if (setPointSched == nullptr)
			return false;
		if (!setPointSched->isValid(err, true))
			return false;
	}

	return true;
}


AbstractDBElement::ComparisonResult NetworkController::equal(const VICUS::AbstractDBElement *other) const {
	const NetworkController * otherCtrl = dynamic_cast<const NetworkController*>(other);
	if (otherCtrl == nullptr)
		return Different;

	// check important parameters

	if (m_modelType != otherCtrl->m_modelType
		|| m_controllerType != otherCtrl->m_controllerType
		|| m_controlledProperty != otherCtrl->m_controlledProperty
		|| m_maximumControllerResultValue > otherCtrl->m_maximumControllerResultValue
		|| m_maximumControllerResultValue < otherCtrl->m_maximumControllerResultValue)
		return Different;

	for (unsigned int i=0; i<NANDRAD::HydraulicNetworkControlElement::NUM_P; ++i) {
		if (m_para[i] != otherCtrl->m_para[i])
			return Different;
	}

	for (unsigned int i=0; i<NANDRAD::HydraulicNetworkControlElement::NUM_ID; ++i) {
		if (m_idReferences[i] != otherCtrl->m_idReferences[i])
			return Different;
	}


	//check meta data
	if (m_displayName != otherCtrl->m_displayName ||
		m_color != otherCtrl->m_color)
		return OnlyMetaDataDiffers;

	return Equal;
}



void NetworkController::checkParameters() const {
	FUNCID(HydraulicNetworkControlElement::checkParameters);

	if (m_controlledProperty == CP_PumpOperation){
		if (m_controllerType != CT_OnOffController)
			throw IBK::Exception("Controlled property 'PumpOperation' can only be used with 'OnOffController'.", FUNC_ID);
	}
	else {
		if (!(m_controllerType == CT_PController || m_controllerType == CT_PIController))
			throw IBK::Exception(IBK::FormatString("Controlled property '%1' can only be used with 'PController' or 'PIController'.")
								 .arg(KeywordList::Keyword("HydraulicNetworkControlElement::ControlledProperty", m_controlledProperty)),
								 FUNC_ID);
	}

	if (m_controlledProperty == CP_PumpOperation){
		if (m_controllerType != CT_OnOffController)
			throw IBK::Exception("Controlled property 'PumpOperation' can only be used with 'OnOffController'.", FUNC_ID);
	}
	else {
		if (!(m_controllerType == CT_PController || m_controllerType == CT_PIController || m_controllerType == CT_PIDController))
			throw IBK::Exception(IBK::FormatString("Controlled property '%1' can only be used with 'PController', 'PIController' or 'PIDController'.")
								 .arg(KeywordList::Keyword("NetworkController::ControlledProperty", m_controlledProperty)),
								 FUNC_ID);
	}

	if (m_controlledProperty == CP_PumpOperation){
		if (m_controllerType != CT_OnOffController)
			throw IBK::Exception("Controlled property 'PumpOperation' can only be used with 'OnOffController'.", FUNC_ID);
	}
	else {
		if (!(m_controllerType == CT_PController || m_controllerType == CT_PIController || m_controllerType == CT_PIDController))
			throw IBK::Exception(IBK::FormatString("Controlled property '%1' can only be used with 'PController', 'PIController' or 'PIDController'.")
								 .arg(KeywordList::Keyword("NetworkController::ControlledProperty", m_controlledProperty)),
								 FUNC_ID);
	}

	try {
		// check individual configuations for different controller properties
		switch (m_controlledProperty) {
			case CP_TemperatureDifference:
			case CP_TemperatureDifferenceOfFollowingElement: {
				if (m_controllerType == NUM_CT)
					throw IBK::Exception("Missing attribute 'controllerType'.", FUNC_ID);

				if (m_modelType == MT_Constant)
					m_para[P_TemperatureDifferenceSetpoint].checkedValue("TemperatureDifferenceSetpoint", "K", "K",
						 std::numeric_limits<double>::lowest(), false, std::numeric_limits<double>::max(), false, nullptr);
			} break;

			case CP_ThermostatValue: {
				if (m_idReferences[ID_ThermostatZone] == NANDRAD::INVALID_ID)
					throw IBK::Exception("Missing 'ThermostatZoneId' for controlled property 'ThermostatValue'!", FUNC_ID);

//				// check validity of thermostat zone
//				std::vector<NANDRAD::Zone>::const_iterator zone_it = std::find(zones.begin(), zones.end(), m_idReferences[ID_ThermostatZone]);

//				if (zone_it == zones.end())
//					throw IBK::Exception(IBK::FormatString("Invalid/undefined zone with '%1' in ThermostatZoneId.")
//										 .arg(m_idReferences[ID_ThermostatZone]), FUNC_ID);
			} break;

			case CP_MassFlux : {
				// we need mass flux, but > 0 (cannot set mass flux to zero)
				if (m_modelType == MT_Constant)
					m_para[P_MassFluxSetpoint].checkedValue("MassFluxSetpoint", "kg/s", "kg/s",
						 0, false, std::numeric_limits<double>::max(), false, nullptr);
			} break;

			case CP_PumpOperation : {
					m_para[P_HeatLossOfFollowingElementThreshold].checkedValue("HeatLossOfFollowingElementThreshold", "W", "W",
						 0, false, std::numeric_limits<double>::max(), false, nullptr);
			} break;

			case CP_PressureDifferenceWorstpoint : {
					m_para[P_PressureDifferenceSetpoint].checkedValue("PressureDifferenceSetpoint", "Pa", "Pa",
						 0, false, std::numeric_limits<double>::max(), false, nullptr);
			} break;

			case NUM_CP:
				throw IBK::Exception("Missing or invalid attribute 'controlledProperty'.", FUNC_ID);
		}
	}
	catch (IBK::Exception & ex) {
			throw IBK::Exception(ex, "Missing/invalid parameters.", FUNC_ID);
	}

	try {

		// decide which parameters are needed
		switch (m_controllerType) {

			case CT_PController: {
				m_para[P_Kp].checkedValue("Kp", "---", "---", 0, false, std::numeric_limits<double>::max(), true, nullptr);
			} break;

			case CT_PIController: {
				m_para[P_Kp].checkedValue("Kp", "---", "---", 0, false, std::numeric_limits<double>::max(), true, nullptr);
				m_para[P_Ki].checkedValue("Ki", "---", "---", 0, false, std::numeric_limits<double>::max(), true, nullptr);
				m_para[P_RelControllerErrorForIntegratorReset].checkedValue("RelControllerErrorForIntegratorReset", "---", "---", 0, true, 1, true, nullptr);
			} break;

			case CT_PIDController: {
				m_para[P_Kp].checkedValue("Kp", "---", "---", 0, false, std::numeric_limits<double>::max(), true, nullptr);
				m_para[P_Ki].checkedValue("Ki", "---", "---", 0, true, std::numeric_limits<double>::max(), true, nullptr);
				m_para[P_Kd].checkedValue("Kd", "---", "---", 0, true, std::numeric_limits<double>::max(), true, nullptr);
				m_para[P_RelControllerErrorForIntegratorReset].checkedValue("RelControllerErrorForIntegratorReset", "---", "---", 0, true, 1, true, nullptr);
			} break;

			case CT_OnOffController: {
				m_para[P_HeatLossOfFollowingElementThreshold].checkedValue("HeatLossOfFollowingElementThreshold",
																"W", "W", 0, false, std::numeric_limits<double>::max(), true, nullptr);
			} break;

				case NUM_CT:
				throw IBK::Exception("Missing or invalid attribute 'controllerType'.", FUNC_ID);
		}
	}
	catch (IBK::Exception & ex) {
			throw IBK::Exception(ex, "Missing/invalid parameters.", FUNC_ID);
	}
}


NetworkController::para_t NetworkController::setPointType(ControlledProperty controlledProperty) {
	switch (controlledProperty) {
		case CP_TemperatureDifference:
		case CP_TemperatureDifferenceOfFollowingElement:
			return P_TemperatureDifferenceSetpoint;
		case CP_MassFlux:
			return P_MassFluxSetpoint;
		case CP_PressureDifferenceWorstpoint:
			return P_PressureDifferenceSetpoint;
		case CP_PumpOperation:
			return P_HeatLossOfFollowingElementThreshold;
		case CP_ThermostatValue:
		case NUM_CP: ; // no parameter to be set here
	}
	return NUM_P;
}


} // namespace VICUS
