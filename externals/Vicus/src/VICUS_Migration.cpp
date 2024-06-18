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

//		if (newVersion <= IBK::Version(1,0)) 			migrateVersion_1_0(rootElement, newVersion);
		if (newVersion <= IBK::Version(1,1)) 			migrateVersion_1_1(rootElement, newVersion);

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

	std::map<unsigned int, std::unique_ptr<TiXmlNode>> componentNodes;
	std::map<unsigned int, std::unique_ptr<TiXmlNode>> controllerNodes;

	// read components and controllers
	TiXmlElement *projectElement = firstChildSave(rootElement, "Project");
	TiXmlElement *dbElement = firstChildSave(projectElement, "EmbeddedDatabase");
	TiXmlElement *netComps = firstChildSave(dbElement, "NetworkComponents");
	for (TiXmlElement *e = netComps->FirstChildElement("NetworkComponent"); e != nullptr; ) {
		std::unique_ptr<TiXmlNode> compCopy(e->Clone());
		unsigned int id = IBK::string2val<unsigned int>(e->Attribute("id"));
		componentNodes[id] = std::move(compCopy);
		// get next element and remove current
		TiXmlElement *next = e->NextSiblingElement("NetworkComponent");
		netComps->RemoveChild(e);
		e = next;
	}

	TiXmlElement *netCtrs = firstChildSave(dbElement, "NetworkControllers");
	for (TiXmlElement *e = netCtrs->FirstChildElement("NetworkController"); e != nullptr; ) {
		std::unique_ptr<TiXmlNode> ctrCopy(e->Clone());
		unsigned int id = IBK::string2val<unsigned int>(e->Attribute("id"));
		controllerNodes[id] = std::move(ctrCopy);
		// get next element and remove current
		TiXmlElement *next = e->NextSiblingElement("NetworkController");
		netCtrs->RemoveChild(e);
		e = next;
	}

	// read subnetworks
	TiXmlElement *subNetsElem = firstChildSave(dbElement, "SubNetworks");
	for (TiXmlElement *subNetNode = subNetsElem->FirstChildElement("SubNetwork"); subNetNode != nullptr;
			subNetNode = subNetNode->NextSiblingElement("SubNetwork")) {

		int hxElemId = 0;
		int hxCompId = 0;
		readAttributeSave(subNetNode, "idHeatExchangeElement", &hxElemId, false);

		// collect component and controller ids
		std::set<unsigned int> compIds;
		std::map<unsigned int, int> comp2ctrIds;
		TiXmlElement *netElems = firstChildSave(subNetNode, "Elements");
		for (TiXmlElement *eElem = netElems->FirstChildElement("NetworkElement"); eElem != nullptr; eElem = eElem->NextSiblingElement("NetworkElement")) {
			// find the element with heat exchange and store the respective component id
			int elemId = 0;
			readAttributeSave(eElem, "id", &elemId, false);
			int compId = 0;
			readAttributeSave(eElem, "componentId", &compId, true);
			if (elemId == hxElemId)
				hxCompId = compId;
			compIds.insert((unsigned int)compId);
			int ctrId = 0;
			readAttributeSave(eElem, "controlElementId", &ctrId, false);
			if (ctrId != 0)
				comp2ctrIds[(unsigned int)compId] = ctrId;
		}

		// create new components
		TiXmlElement* componentsElem = new TiXmlElement("Components");
		for (unsigned int compId: compIds) {
			if (componentNodes.find(compId) != componentNodes.end()) {
				TiXmlElement *eComp = dynamic_cast<TiXmlElement*>(componentNodes.at(compId).get());
				// controller is now child of component
				if (comp2ctrIds.find(compId) != comp2ctrIds.end())
					eComp->InsertEndChild( *controllerNodes.at((unsigned int)comp2ctrIds.at(compId)) );

				// add also heat exchange
				if (compId == (unsigned int)hxCompId) {
					NetworkHeatExchange hx;
					hx.m_individualHeatExchange = true;
					hx.writeXML(eComp);
				}

				componentsElem->InsertEndChild( *eComp );
			}
			else
				throw IBK::Exception(IBK::FormatString("Error transfering network component #%1").arg(compId), FUNC_ID);

		}
		subNetNode->LinkEndChild(componentsElem);
	}

	// done with conversion, we are now at version 1.2
	TiXmlAttribute * versionAttrib = const_cast<TiXmlAttribute *>(TiXmlAttribute::attributeByName(rootElement, "fileVersion"));
	versionAttrib->SetValue("1.2");
	newVersion = IBK::Version(1,2);
}


TiXmlElement * Migration::firstChildSave(TiXmlElement * parent, const std::string & childName) {
	FUNCID(Migration::firstChildSave);
	TiXmlElement *child = parent->FirstChildElement(childName);
	std::string b = "";
	if (!child)
		throw IBK::Exception(IBK::FormatString("Could not find element '%1' in '%2'").arg(childName).arg(parent->ValueStr()), FUNC_ID);
	return child;
}


void Migration::readAttributeSave(const TiXmlElement * elem, std::string name, int *value, bool required) {
	FUNCID(Migration::readAttributeSave);
	elem->Attribute(name, value);
	if (required && value == nullptr)
		throw IBK::Exception(IBK::FormatString("Could not find required attribute '%1' in '%2'").arg(name).arg(elem->ValueStr()), FUNC_ID);
}



} // namespace VICUS
