#include "VicOSM_AbstractOSMElement.h"
#include <IBK_Exception.h>

namespace VicOSM {

void Tag::readXML(const TiXmlElement * element)
{
	FUNCID(AbstractOSMElement::Tag::readXML);

	if (!TiXmlAttribute::attributeByName(element, "k"))
		throw IBK::Exception( IBK::FormatString("Error in XML file, line %1: %2").arg(element->Row()).arg(
								 IBK::FormatString("Missing required 'k' attribute.") ), FUNC_ID);
	if (!TiXmlAttribute::attributeByName(element, "v"))
		throw IBK::Exception( IBK::FormatString("Error in XML file, line %1: %2").arg(element->Row()).arg(
								 IBK::FormatString("Missing required 'v' attribute.") ), FUNC_ID);

	key = TiXmlAttribute::attributeByName(element, "k")->ValueStr();
	value = TiXmlAttribute::attributeByName(element, "v")->ValueStr();
}

void Member::readXML(const TiXmlElement * element)
{
	FUNCID(AbstractOSMElement::Member::readXML);

	if (!TiXmlAttribute::attributeByName(element, "type"))
		throw IBK::Exception( IBK::FormatString("Error in XML file, line %1: %2").arg(element->Row()).arg(
								 IBK::FormatString("Missing required 'type' attribute.") ), FUNC_ID);
	if (!TiXmlAttribute::attributeByName(element, "ref"))
		throw IBK::Exception( IBK::FormatString("Error in XML file, line %1: %2").arg(element->Row()).arg(
								 IBK::FormatString("Missing required 'ref' attribute.") ), FUNC_ID);
	if (!TiXmlAttribute::attributeByName(element, "role"))
		throw IBK::Exception( IBK::FormatString("Error in XML file, line %1: %2").arg(element->Row()).arg(
								 IBK::FormatString("Missing required 'role' attribute.") ), FUNC_ID);

	std::string typeStr = TiXmlAttribute::attributeByName(element, "type")->ValueStr();
	if (typeStr == "node")
		type = NodeType;
	else if (typeStr == "way")
		type = WayType;
	else if (typeStr == "relation")
		type = RelationType;
	else
		throw IBK::Exception( IBK::FormatString("Error in XML file, line %1: %2").arg(element->Row()).arg(
								 IBK::FormatString("Unknown type '%1'.").arg(typeStr) ), FUNC_ID);

	ref = TiXmlAttribute::attributeByName(element, "ref")->IntValue();
	role = TiXmlAttribute::attributeByName(element, "role")->ValueStr();
}

void Nd::readXML(const TiXmlElement * element)
{
	FUNCID(AbstractOSMElement::Nd::readXML);

	if (!TiXmlAttribute::attributeByName(element, "ref"))
		throw IBK::Exception( IBK::FormatString("Error in XML file, line %1: %2").arg(element->Row()).arg(
								 IBK::FormatString("Missing required 'ref' attribute.") ), FUNC_ID);

	ref = TiXmlAttribute::attributeByName(element, "ref")->IntValue();
}

void AbstractOSMElement::readXML(const TiXmlElement * element)
{
	FUNCID(AbstractOSMElement::readXML);

	// mandatory attributes
	if (!TiXmlAttribute::attributeByName(element, "id"))
		throw IBK::Exception( IBK::FormatString("Error in XML file, line %1: %2").arg(element->Row()).arg(
								 IBK::FormatString("Missing required 'id' attribute.") ), FUNC_ID);

	// Read common attributes
	const TiXmlAttribute * attrib = element->FirstAttribute();
	while (attrib) {
		const std::string & attribName = attrib->NameStr();
		if (attribName == "id") {
			m_id = attrib->IntValue();
		}
		else if (attribName == "visible") {
			std::string value = attrib->ValueStr();
			m_visible = value == "true" ? true : false;
		}
		attrib = attrib->Next();
	}
}

bool AbstractOSMElement::containsKey(const std::string & key) const
{
	for (int i = 0; i < m_tags.size(); i++) {
		if(m_tags[i].key == key)
			return true;
	}
	return false;
}

bool AbstractOSMElement::containsValue(const std::string & value) const
{
	for (int i = 0; i < m_tags.size(); i++) {
		if(m_tags[i].value == value)
			return true;
	}
	return false;
}

bool AbstractOSMElement::containsKeyValue(const std::string & key, const std::string & value) const
{
	for (int i = 0; i < m_tags.size(); i++) {
		if(m_tags[i].key == key && m_tags[i].value == value)
			return true;
	}
	return false;
}

std::string AbstractOSMElement::getValueFromKey(const std::string & key) const
{
	for (int i = 0; i < m_tags.size(); i++) {
		if(m_tags[i].key == key)
			return m_tags[i].value;
	}
	return std::string("");
}

} // namespace VicOSM
