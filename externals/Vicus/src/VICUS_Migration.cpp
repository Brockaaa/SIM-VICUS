#include "VICUS_Migration.h"

#include <tinyxml.h>

#include <IBK_Version.h>
#include <IBK_messages.h>
#include <IBK_Exception.h>

#include <NANDRAD_Utilities.h>

#include "VICUS_Constants.h"
#include "VICUS_Project.h"


namespace VICUS {


bool Migration::migrateProject(TiXmlElement * rootElement, IBK::Version & srcVersion) {
	FUNCID(Migration::migrateProject);
	// check for original version
	const TiXmlAttribute * versionAttrib = TiXmlAttribute::attributeByName(rootElement, "fileVersion");
	if (versionAttrib == nullptr)
		throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(rootElement->Row()).arg(
			IBK::FormatString("Missing required 'version' attribute.") ), FUNC_ID);

	std::string version = versionAttrib->ValueStr();
	unsigned int major, minor;
	bool validVersion = IBK::Version::extractMajorMinorVersionNumber(version, major, minor);
	if (!validVersion)
		throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(rootElement->Row()).arg(
			IBK::FormatString("Invalid 'version' attribute, expected <major>.<minor>.") ), FUNC_ID);

	srcVersion = IBK::Version(major, minor);
	IBK::Version currentVersion(VICUS::VERSION); // no check for validity here - we expect us as coders to use the correct format!
	if (srcVersion >= currentVersion)
		return false;

	IBK::Version newVersion = srcVersion;
	// now process the cascade
	try {

		if (newVersion == IBK::Version(1,0)) 			migrateVersion_1_0(rootElement, newVersion);
		if (newVersion == IBK::Version(1,1)) 			migrateVersion_1_1(rootElement, newVersion);

	} catch (IBK::Exception & ex) {
		throw IBK::Exception(ex, "Error migrating project.", FUNC_ID);
	}

	return newVersion != srcVersion;
}


void Migration::migrateVersion_1_0(TiXmlElement * rootElement, IBK::Version & newVersion) {
	FUNCID(Migration::migrateVersion_1_0);
	IBK::IBK_Message("Migrating project from Version 1.0 to 1.1.\n", IBK::MSG_PROGRESS, FUNC_ID);

	// TODO : modify DOM in-place

	// done with conversion, we are now at version 1.1
	TiXmlAttribute * versionAttrib = const_cast<TiXmlAttribute *>(TiXmlAttribute::attributeByName(rootElement, "fileVersion"));
	versionAttrib->SetValue("1.1");
	newVersion = IBK::Version(1,1);
}


void Migration::migrateVersion_1_1(TiXmlElement * rootElement, IBK::Version & newVersion) {
	FUNCID(Migration::migrateVersion_1_1);
	IBK::IBK_Message("Migrating project from Version 1.1 to 1.2.\n", IBK::MSG_PROGRESS, FUNC_ID);


	/*!
	 *  Structure of sub networks has changed. Network components and controllers are now stored directly in the sub network,
	 *  instead of using database references.
	 *  For components, there are still database elements existing, which can be used as parametrization templates.
	 *  However, When used, these are always stored as local copies in the sub network.
	 *  For controllers, no database exist anymore. We only keep the datastructure to be able to read those
	 *  For heat exchange definitions ....
	 */

	std::vector<NetworkComponent> networkComponents;
	std::vector<NetworkController> networkConotrollers;

	// read components and controllers
	TiXmlElement *projectElement = accessChildSave(rootElement, "Project");
	TiXmlElement *dbElement = accessChildSave(projectElement, "EmbeddedDatabase");
	TiXmlElement *netCompsElement = accessChildSave(dbElement, "NetworkComponents");
	for (const TiXmlElement *e = netCompsElement->FirstChildElement("NetworkComponent"); e != nullptr; e = e->NextSiblingElement("NetworkComponent")) {
		// read component with existing function
		VICUS::NetworkComponent obj;
		obj.readXML(e);
		networkComponents.push_back(obj);
	}
	const TiXmlElement *netCtrsElement = accessChildSave(dbElement, "NetworkControllers");
	for (const TiXmlElement *e = netCtrsElement->FirstChildElement("NetworkController"); e != nullptr; e = e->NextSiblingElement("NetworkController")) {
		// read controller with existing function
		VICUS::NetworkController obj;
		obj.readXML(e);
		networkConotrollers.push_back(obj);
	}

	// read subnetworks
	TiXmlElement *subNetsElem = accessChildSave(dbElement, "SubNetworks");
	for (TiXmlElement *eSub = subNetsElem->FirstChildElement("SubNetwork"); eSub != nullptr; eSub = eSub->NextSiblingElement("SubNetwork")) {

		// collect component ids
		std::set<unsigned int> compIds;
		const TiXmlElement *netElems = accessChildSave(eSub, "NetworkElements");
		for (const TiXmlElement *eElem = netElems->FirstChildElement("NetworkElement"); eElem != nullptr; eElem = eElem->NextSiblingElement("NetworkElement")) {
			int compId = 0;
			readAttributeSave(eElem, "componentId", &compId);
			compIds.insert((unsigned int)compId);
		}

		// create new components
		TiXmlElement* eComps = new TiXmlElement("NetworkComponents");
		for (unsigned int compId: compIds) {
			VICUS::NetworkComponent *comp = VICUS::element(networkComponents, compId);
			Q_ASSERT(comp!=nullptr);
			comp->writeXML(eComps);
		}
		eSub->LinkEndChild(eComps);

	}




//	// iterates over every element and copies component into Subnetwork and create new IDs
//	for(VICUS::NetworkElement &element : m_subNetwork->m_elements){
//		if(element.m_componentId != VICUS::INVALID_ID){
//			VICUS::NetworkComponent *componentPtr = m_db->m_networkComponents[element.m_componentId];
//			if (componentPtr == nullptr)
//				throw IBK::Exception(tr("Could not find network component #%1.")
//										 .arg(element.m_componentId).toStdString(), FUNC_ID);
//			VICUS::NetworkComponent component = *componentPtr;
//			component.m_id = VICUS::largestUniqueId(m_subNetwork->m_components);
//			element.m_componentId = component.m_id;

//			// copies controller from database and to the component
//			if(element.m_controlElementId != VICUS::INVALID_ID){
//				VICUS::NetworkController *controllerPtr = m_db->m_networkControllers[element.m_controlElementId];
//				if (controllerPtr == nullptr)
//					throw IBK::Exception(tr("Could not find network controller #%1.")
//											 .arg(element.m_controlElementId).toStdString(), FUNC_ID);
//				VICUS::NetworkController controller = *controllerPtr;
//				controller.m_id = VICUS::INVALID_ID;
//				component.m_networkController = controller;
//			}

//			m_subNetwork->m_components.push_back(component);
//		} else {
//			throw IBK::Exception(tr("Invalid network component #%1.")
//									 .arg(element.m_componentId).toStdString(), FUNC_ID);
//		}
//	}

//	m_db->removeNotReferencedLocalElements(SVDatabase::DT_NetworkComponents, SVProjectHandler::instance().project());
//	m_db->removeNotReferencedLocalElements(SVDatabase::DT_NetworkControllers, SVProjectHandler::instance().project());



	// done with conversion, we are now at version 1.2
	TiXmlAttribute * versionAttrib = const_cast<TiXmlAttribute *>(TiXmlAttribute::attributeByName(rootElement, "fileVersion"));
	versionAttrib->SetValue("1.2");
	newVersion = IBK::Version(1,2);
}


TiXmlElement * Migration::accessChildSave(TiXmlElement * parent, const std::string & childName) {
	FUNCID(Migration::accessChildSave);
	TiXmlElement *child = parent->FirstChildElement(childName);
	std::string b = "";
	if (!child)
		throw IBK::Exception(IBK::FormatString("Could not find element '%1' in '%2'").arg(childName).arg(parent->ValueStr()), FUNC_ID);
	return child;
}


void Migration::readAttributeSave(const TiXmlElement * elem, std::string name, int *value) {
	FUNCID(Migration::readAttributeSave);
	elem->Attribute(name, value);
	if (value == nullptr)
		throw IBK::Exception(IBK::FormatString("Could not find attribute '%1' in '%2'").arg(name).arg(elem->ValueStr()), FUNC_ID);
}



} // namespace VICUS
