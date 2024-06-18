#ifndef VICUS_MIGRATION_H
#define VICUS_MIGRATION_H

#include <string>
class TiXmlElement;

namespace IBK {
	class Version;
}

namespace VICUS {

/*! Utility class that handlers VICUS project version migration. */
class Migration {
public:

	/*! Central migration function.
		Call this function with a DOM of the VICUS Project right after reading it from file.
		Depending on the version in the data structure, the function calls the appropriate sequence
		of migration functions to bring the DOM up-to-date.
		\code
			TiXmlHandle xmlHandleDoc(&doc);
			// read root element
			TiXmlElement * xmlElem = xmlHandleDoc.FirstChildElement().Element();
			// start migration
			std::string versionSuffix;
			bool migrated = Migration::migrateProject(xmlElem, versionSuffix);
		\endcode
		\param rootElement The root element of the DOM. If a migration was necessary, this DOM is modified in-place.
		\param srcVersion The version number of the original DOM before migration.
		\return Returns true when a migration was necessary or false, if project is already up-to-date.
	*/
	static bool migrateProject(TiXmlElement * rootElement, IBK::Version & srcVersion);

private:
	/*! Migrates project version from 1.0 to 1.1 */
	static void migrateVersion_1_0(TiXmlElement * rootElement, IBK::Version & newVersion);
	/*! Migrates project version from 1.0 to 1.2 */
	static void migrateVersion_1_1(TiXmlElement * rootElement, IBK::Version & newVersion);

	static TiXmlElement * firstChildSave(TiXmlElement * parent, const std::string &childName);

	static void readAttributeSave(const TiXmlElement * elem, std::string name, int * value, bool required);
};

} // namespace VICUS

#endif // VICUS_MIGRATION_H
