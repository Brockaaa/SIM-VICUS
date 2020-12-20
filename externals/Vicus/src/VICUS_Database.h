#ifndef VICUS_DatabaseH
#define VICUS_DatabaseH

#include <map>

#include <IBK_Path.h>
#include <IBK_messages.h>

#include <tinyxml.h>

namespace VICUS {

/*! Wrapper class for different databases.
	Template argument classes must provide a public bool member m_builtIn, and the functions
	readXML(const TiXmlElement * element) and writeXML(TiXmlElement * parent) const.

	Usage:
	\code
		VICUS::Database<Material> materials;

		VICUS::Material m;
		m.   .... set parameters

		unsigned ínt newId = materials.add(m);

		const VICUS::Material * materials[newId]; // -> either VICUS::Material pointer or nullptr, if object doesn't exist
	\endcodde
*/
template<typename T>
class Database {
public:
	Database(unsigned int userIDSpaceStart) :
		USER_ID_SPACE_START(userIDSpaceStart), m_userIdCounter(userIDSpaceStart)
	{
	}

	/*! Returns database element by ID, or nullptr if no element exists with this ID. */
	const T * operator[](unsigned int id) const {
		typename std::map<unsigned int, T>::const_iterator it = m_data.find(id);
		if (it == m_data.end())		return nullptr;
		else						return &(it->second);
	}

	/*! Returns begin for iterator-type read-only access to data store. */
	typename std::map<unsigned int, T>::const_iterator begin() const { return m_data.begin(); }
	/*! Returns end for iterator-type read-only access to data store. */
	typename std::map<unsigned int, T>::const_iterator end() const { return m_data.end(); }
	/*! Returns number of DB elements. */
	size_t size() const { return m_data.size(); }
	/*! Returns true if database is empty. */
	bool empty() const { return m_data.empty(); }

	/*! Adds a new item to the database.
		\param newData New object to be added.
		\param suggestedId ID of object to insert (possibly when adding this data object from a project file), or 0,
			if object was newly created and needs a new ID anyway.
	*/
	unsigned int add(T & newData, unsigned int suggestedId = 0) {
		// check if suggestedId is already used
		bool used = false;
		if (suggestedId != 0) {
			for (typename std::map<unsigned int, T>::const_iterator it = m_data.begin(); it != m_data.end(); ++it) {
				if (it->first == suggestedId) {
					used = true;
					break;
				}
			}
		}
		// if used, or suggestedId == 0 (new object), find first unused user-space ID
		if (suggestedId == 0 || used) {
			// object gets new unique Id, search for next free userId
			unsigned int newId = ++m_userIdCounter;
			while (m_data.find(newId) != m_data.end())
				newId = ++m_userIdCounter;
			newData.m_id = newId;
		}
		else {
			// object gets suggested Id
			if (newData.m_id != suggestedId) {
				newData.m_id = suggestedId; // this should be the case already, but just to be certain
			}
		}
		// set built-in flag to identify material as built-in or user-defined base on UI space
		if (newData.m_id >= USER_ID_SPACE_START)
			newData.m_builtIn = false;
		m_data[newData.m_id] = newData;
		// for now database is always modified when data is set, callers have to ensure that
		// they don't re-set data with original data and id
		m_modified = true;
		return newData.m_id;
	}

	/*! Removes a database element identifies by its ID
		\warning Throws an IBK::Exception if no element with given ID exists.
	*/
	void remove(unsigned int id) {
		FUNCID(Database::remove);
		typename std::map<unsigned int, T>::const_iterator it = m_data.find(id);
		if (it == m_data.end())
			throw IBK::Exception( IBK::FormatString("Error removing database element with id=%1. No such ID in database.").arg(id), FUNC_ID);
		m_data.erase(it);
		m_modified = true;
	}

	/*! Reads database from xml file.
		Usage:
		\code
		// read built-in material DB
		db.readXML("db_materials.xml", "Materials", "Material", true);
		\endcode

		\warning Throws an IBK::Exception if reading fails.
	*/
	void readXML(const IBK::Path & fname, const std::string & topLevelTag,
				   const std::string & childTagName,
				   bool builtIn = false)
	{
		FUNCID(Datbase::readXML);

		TiXmlDocument doc;
		if (!fname.isFile() )
			return;

		try {
			if (!doc.LoadFile(fname.str().c_str(), TIXML_ENCODING_UTF8)) {
				throw IBK::Exception(IBK::FormatString("Error in line %1 of XML file '%2':\n%3")
						.arg(doc.ErrorRow())
						.arg(fname)
						.arg(doc.ErrorDesc()), FUNC_ID);
			}

			// we use a handle so that NULL pointer checks are done during the query functions
			TiXmlHandle xmlHandleDoc(&doc);

			// read root element
			TiXmlElement * xmlElem = xmlHandleDoc.FirstChildElement().Element();
			if (!xmlElem)
				return; // empty file?
			std::string rootnode = xmlElem->Value();
			if (rootnode != topLevelTag)
				throw IBK::Exception( IBK::FormatString("Expected '%1' as root node in XML file.")
									  .arg(topLevelTag), FUNC_ID);

			const TiXmlElement * c2 = xmlElem->FirstChildElement();
			while (c2) {
				const std::string & c2Name = c2->ValueStr();
				if (c2Name != childTagName)
					IBK::IBK_Message(IBK::FormatString("Unknown/unsupported tag '%1' in line %2, expected '%3'.")
									 .arg(c2Name).arg(c2->Row()).arg(childTagName), IBK::MSG_WARNING, FUNC_ID, IBK::VL_STANDARD);
				T obj;
				obj.readXML(c2);
				obj.m_builtIn = builtIn;

				// check for existing DB element - must not exist, otherwise DB file is faulty
				if (m_data.find(obj.m_id) != m_data.end()){
					IBK::Exception(IBK::FormatString("Database '%1' contains duplicate ids %2 ")
								   .arg(fname.str()).arg(obj.m_id), FUNC_ID);
				}

				m_data[obj.m_id] = obj;
				c2 = c2->NextSiblingElement();
			}
		}
		catch (IBK::Exception & ex) {
			ex.writeMsgStackToError();
			IBK::IBK_Message(IBK::FormatString("Error reading XML database '%1'.").arg(fname), IBK::MSG_ERROR, FUNC_ID);
		}
	}


	/*! Writes database to XML file.
		Usage:
		\code
		// write user material DB (writes only those materials marked not as built-in)
		db.writeXML("db_materials.xml", "Materials");
		\endcode
	*/
	void writeXML(const IBK::Path & fname, const std::string & topLevelTag) const {
		TiXmlDocument doc;
		TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );
		doc.LinkEndChild( decl );

		TiXmlElement * root = new TiXmlElement( topLevelTag );
		doc.LinkEndChild(root);

		for (auto e : m_data)
			if (!e.second.m_builtIn)
				e.second.writeXML(root);

		doc.SaveFile( fname.c_str() );
	}

	/*! Modified marker, should be changed to true, whenever a database object was modified.
		Will be automatically set to true in functions add() and remove().
	*/
	bool										m_modified = false;

private:
	std::map<unsigned int, T>					m_data;

	/*! Counter that holds the first user material ID. */
	const unsigned int							USER_ID_SPACE_START;
	/*! Counter that holds the next unused user material ID. */
	unsigned int								m_userIdCounter;
};

} // namespace VICUS


#endif // VICUS_DatabaseH
