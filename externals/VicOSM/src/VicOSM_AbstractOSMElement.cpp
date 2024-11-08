#include "VicOSM_AbstractOSMElement.h"
#include <VicOSM_KeywordList.h>

#include <IBK_messages.h>
#include <IBK_Exception.h>
#include <IBK_StringUtils.h>
#include <VicOSM_Constants.h>
#include <NANDRAD_Utilities.h>

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

	m_key = TiXmlAttribute::attributeByName(element, "k")->ValueStr();
	m_value = TiXmlAttribute::attributeByName(element, "v")->ValueStr();
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
		m_type = NodeType;
	else if (typeStr == "way")
		m_type = WayType;
	else if (typeStr == "relation")
		m_type = RelationType;
	else
		throw IBK::Exception( IBK::FormatString("Error in XML file, line %1: %2").arg(element->Row()).arg(
								 IBK::FormatString("Unknown type '%1'.").arg(typeStr) ), FUNC_ID);

	m_ref = std::atol(TiXmlAttribute::attributeByName(element, "ref")->Value());
	m_role = TiXmlAttribute::attributeByName(element, "role")->ValueStr();
}

void Nd::readXML(const TiXmlElement * element)
{
	FUNCID(AbstractOSMElement::Nd::readXML);

	if (!TiXmlAttribute::attributeByName(element, "ref"))
		throw IBK::Exception( IBK::FormatString("Error in XML file, line %1: %2").arg(element->Row()).arg(
								 IBK::FormatString("Missing required 'ref' attribute.") ), FUNC_ID);

	m_ref = std::atol(TiXmlAttribute::attributeByName(element, "ref")->Value());
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
			m_id = std::atol(attrib->Value());
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
	for (unsigned int i = 0; i < m_tags.size(); i++) {
		if(m_tags[i].m_key == key)
			return true;
	}
	return false;
}

bool AbstractOSMElement::containsValue(const std::string & value) const
{
	for (unsigned int i = 0; i < m_tags.size(); i++) {
		if(m_tags[i].m_value == value)
			return true;
	}
	return false;
}

bool AbstractOSMElement::containsKeyValue(const std::string & key, const std::string & value) const
{
	for (unsigned int i = 0; i < m_tags.size(); i++) {
		if(m_tags[i].m_key == key && m_tags[i].m_value == value)
			return true;
	}
	return false;
}

std::string AbstractOSMElement::getValueFromKey(const std::string & key) const
{
	for (unsigned int i = 0; i < m_tags.size(); i++) {
		if(m_tags[i].m_key == key)
			return m_tags[i].m_value;
	}
	return std::string("");
}

} // namespace VicOSM
