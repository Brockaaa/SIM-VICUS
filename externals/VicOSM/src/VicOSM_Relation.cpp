#include "VicOSM_Relation.h"
#include "IBK_Exception.h"

namespace VicOSM {

void Relation::readXML(const TiXmlElement * element) {
	FUNCID(VicOSM::Relation::readXML);

	AbstractOSMElement::readXML(element);

	// Read child elements
	const TiXmlElement * child = element->FirstChildElement();
	while (child) {
		const std::string & childName = child->ValueStr();
		if (childName == "tag") {
			Tag tag;
			tag.readXML(child);
			m_tags.push_back(tag);
		}
		if (childName == "member") {
			Member member;
			member.readXML(child);
			m_members.push_back(member);
		}
		child = child->NextSiblingElement();
	}
}

} // namespace VicOSM
