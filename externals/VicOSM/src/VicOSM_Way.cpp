#include "VicOSM_Way.h"
#include "IBK_Exception.h"

namespace VicOSM {

void Way::readXML(const TiXmlElement * element) {
	FUNCID(VicOSM::Way::readXML);

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
		if (childName == "nd") {
			Nd nd;
			//nd.readXML(child);
			m_nd.push_back(nd);
		}
		child = child->NextSiblingElement();
	}
}

} // namespace VicOSM
