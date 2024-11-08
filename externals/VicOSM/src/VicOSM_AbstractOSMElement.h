#ifndef VicOSM_ABSTRACTOSMELEMENT_H
#define VicOSM_ABSTRACTOSMELEMENT_H

#include "tinyxml.h"
#include <vector>

namespace VicOSM {

/*! The 3 elements in a .osm file */
enum Types {
	NodeType,
	WayType,
	RelationType
};

/*! Tag with key and value that contains metadata. Can be used by any osm element */
struct Tag {
	/*! Key of the Tag */
	std::string m_key;
	/*! Value of the Tag */
	std::string m_value;
	/*! readXML (handwritten) to read a tag in a .osm file */
	void readXML(const TiXmlElement * element);
};

/*! Member only used by Relations. Can hold a reference to any of the 3 osm elements and marks that element with a role */
struct Member {
	/*! Specifies if the member is a node, way or relation */
	Types m_type;
	/*! Reference to the OSM Element */
	uint64_t m_ref;
	/*! Role of the OSM Element */
	std::string m_role;
	/*! readXML (handwritten) to read a member in a .osm file */
	void readXML(const TiXmlElement * element);
};

/*! Nd (for node) only used by ways to reference nodes. The order of the nodes define the polyline described by the way element */
struct Nd {
	/*! Reference to a node element */
	uint64_t m_ref;
	/*! readXML (handwritten) to read a node in a .osm file */
	void readXML(const TiXmlElement * element);
};

/*! Abstract class for any of the 3 .osm elements. Contains some helper functions for easy access to tags */
class AbstractOSMElement {
public:
	virtual ~AbstractOSMElement() {}
	/*! Function (handwritten) to read from a .osm file */
	void readXML(const TiXmlElement * element);
	/*! checks if this OSM Element has a key in it's list of tags */
	bool containsKey(const std::string& key) const;
	/*! checks if this OSM Element has a value in it's list of tags */
	bool containsValue(const std::string& value) const;
	/*! checks if this OSM Element has the specified key value combination */
	bool containsKeyValue(const std::string& key, const std::string& value) const;
	/*! Retrieves the value of the first occurence of a key */
	std::string getValueFromKey(const std::string& key) const;
	/*! Unique ID of the OSM Element. The ID space is described by openstreetmap and is unique for every osm element
		in Planet.osm */
	uint64_t				        m_id = -1; // unique id
	/*! Stores all tags of a OSM Element */
	std::vector<Tag>				m_tags; // stores all tags. Does not make an effort to interpret them
	/*! Stores all Nd elements of a way */
	std::vector<Nd>					m_nd;
	/*! Stores all Member elements of a relation */
	std::vector<Member>				m_members;
	/*! Visibility flag of an osm element. Unused so far */
	bool                            m_visible = true; // visibility flag
};

} // namespace VicOSM

#endif // VicOSM_ABSTRACTOSMELEMENT_H
