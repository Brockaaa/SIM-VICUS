#include "VicOSM_Node.h"
#include "IBK_Exception.h"

namespace VicOSM {

void Node::readXML(const TiXmlElement * element) {
	FUNCID(VicOSM::Node::readXML);

	AbstractOSMElement::readXML(element);

	// Check for mandatory attributes
	if (!TiXmlAttribute::attributeByName(element, "lat"))
		throw IBK::Exception(IBK::FormatString("Error in XML file, line %1: %2").arg(element->Row()).arg(
								 IBK::FormatString("Missing required 'lat' attribute.")), FUNC_ID);
	if (!TiXmlAttribute::attributeByName(element, "lon"))
		throw IBK::Exception(IBK::FormatString("Error in XML file, line %1: %2").arg(element->Row()).arg(
								 IBK::FormatString("Missing required 'lon' attribute.")), FUNC_ID);

	// Read the latitude and longitude attributes
	m_lat = TiXmlAttribute::attributeByName(element, "lat")->DoubleValue();
	m_lon = TiXmlAttribute::attributeByName(element, "lon")->DoubleValue();

	// Read child elements
	const TiXmlElement * child = element->FirstChildElement();
	while (child) {
		const std::string & childName = child->ValueStr();
		if (childName == "tag") {
			Tag tag;
			tag.readXML(child);
			m_tags.push_back(tag);
		}
		child = child->NextSiblingElement();
	}
}

} // namespace VicOSM
