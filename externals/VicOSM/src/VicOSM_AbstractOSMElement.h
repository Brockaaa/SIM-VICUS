#ifndef VicOSM_ABSTRACTOSMELEMENT_H
#define VicOSM_ABSTRACTOSMELEMENT_H

#include "tinyxml.h"
#include <vector>

namespace VicOSM {

enum Types {
	NodeType,
	WayType,
	RelationType
};

struct Tag {
	std::string key;
	std::string value;
	void readXML(const TiXmlElement * element);
};


struct Member {
	Types type;
	int ref;
	std::string role;
	void readXML(const TiXmlElement * element);
};

struct Nd {
	int ref;
	void readXML(const TiXmlElement * element);
};


class AbstractOSMElement {
public:

	virtual ~AbstractOSMElement() {}

	void readXML(const TiXmlElement * element);

	bool containsKey(const std::string& key) const;

	bool containsValue(const std::string& value) const;

	bool containsKeyValue(const std::string& key, const std::string& value) const;

	std::string getValueFromKey(const std::string& key) const;

	unsigned int                    m_id = -1; // unique id

	std::vector<Tag>				m_tags; // stores all tags. Does not make an effort to interpret them

	std::vector<Nd>					m_nd;

	std::vector<Member>				m_members;

	bool                            m_visible = true; // visibility flag
};

} // namespace VicOSM

#endif // VicOSM_ABSTRACTOSMELEMENT_H
