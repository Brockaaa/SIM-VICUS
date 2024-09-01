#ifndef VICUS_DRAWINGOSM_H
#define VICUS_DRAWINGOSM_H

#include "VICUS_Constants.h"
#include "tinyxml.h"

#include <IBKMK_Vector2D.h>
#include <VICUS_Object.h>
#include <string>
#include <vector>

namespace VICUS {

/*!
	DrawingOSM class is data structure for all primitive osm elements nodes, ways, relations
 */
class DrawingOSM : public Object {

public:

	/*! Type-info string. */
	const char * typeinfo() const override {
		return "DrawingOSM";
	}

	// *** PUBLIC MEMBER FUNCTIONS ***

	~DrawingOSM();

	enum Types{
		NodeType,
		WayType,
		RelationType
	};

	struct Tag{
		std::string key;
		std::string value;

		void readXML(const TiXmlElement * element) {
			FUNCID(DrawingOSM::Tag::readXML);

			if (!TiXmlAttribute::attributeByName(element, "k"))
				throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
										 IBK::FormatString("Missing required 'k' attribute.") ), FUNC_ID);
			if (!TiXmlAttribute::attributeByName(element, "v"))
				throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
										 IBK::FormatString("Missing required 'v' attribute.") ), FUNC_ID);

			key = TiXmlAttribute::attributeByName(element, "k")->ValueStr();
			value = TiXmlAttribute::attributeByName(element, "v")->ValueStr();
		}
	};

	struct Member{
		Types type;
		int ref;
		std::string role;

		void readXML(const TiXmlElement * element) {
			FUNCID(DrawingOSM::Member::readXML);

			if (!TiXmlAttribute::attributeByName(element, "type"))
				throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
										 IBK::FormatString("Missing required 'type' attribute.") ), FUNC_ID);
			if (!TiXmlAttribute::attributeByName(element, "ref"))
				throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
										 IBK::FormatString("Missing required 'ref' attribute.") ), FUNC_ID);
			if (!TiXmlAttribute::attributeByName(element, "role"))
				throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
										 IBK::FormatString("Missing required 'role' attribute.") ), FUNC_ID);

			std::string typeStr = TiXmlAttribute::attributeByName(element, "type")->ValueStr();
			if (typeStr == "node")
				type = NodeType;
			else if (typeStr == "way")
				type = WayType;
			else if (typeStr == "relation")
				type = RelationType;
			else
				throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
										 IBK::FormatString("Unknown type '%1'.").arg(typeStr) ), FUNC_ID);

			ref = TiXmlAttribute::attributeByName(element, "ref")->IntValue();
			role = TiXmlAttribute::attributeByName(element, "role")->ValueStr();
		}
	};

	struct Nd{
		int ref;

		void readXML(const TiXmlElement * element) {
			FUNCID(DrawingOSM::nd::readXML);

			if (!TiXmlAttribute::attributeByName(element, "ref"))
				throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
										 IBK::FormatString("Missing required 'ref' attribute.") ), FUNC_ID);

			ref = TiXmlAttribute::attributeByName(element, "ref")->IntValue();
		}
	};

	struct BoundingBox{
		double minlat;
		double maxlat;
		double minlon;
		double maxlon;
	};

	/* Abstract class for all directly drawable dxf entities */
	struct AbstractOSMElement {

		~AbstractOSMElement(){
			for (size_t i = 0; i < m_tags.size(); ++i)
				delete m_tags[i];
			m_tags.clear();
		}

		void readXML(const TiXmlElement * element){
			FUNCID(DrawingOSM::AbstractOSMElement::readXML);

			// mandatory attributes
			if (!TiXmlAttribute::attributeByName(element, "id"))
				throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
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

		unsigned int                    m_id = VICUS::INVALID_ID; // unique id

		std::vector<Tag*>				m_tags; // stores all tags. Does not make an effort to interpret them

		bool                            m_visible = true; // visibility flag
	};

	/*! Stores attributes of line */
	struct Node : public AbstractOSMElement {

		void readXML(const TiXmlElement * element) {
			FUNCID(DrawingOSM::Node::readXML);

			AbstractOSMElement::readXML(element);

			// Check for mandatory attributes
			if (!TiXmlAttribute::attributeByName(element, "lat"))
				throw IBK::Exception(IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
					IBK::FormatString("Missing required 'lat' attribute.")), FUNC_ID);
			if (!TiXmlAttribute::attributeByName(element, "lon"))
				throw IBK::Exception(IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
					IBK::FormatString("Missing required 'lon' attribute.")), FUNC_ID);

			// Read the latitude and longitude attributes
			m_lat = TiXmlAttribute::attributeByName(element, "lat")->DoubleValue();
			m_lon = TiXmlAttribute::attributeByName(element, "lon")->DoubleValue();

			// Read child elements
			const TiXmlElement * child = element->FirstChildElement();
			while (child) {
				const std::string & childName = child->ValueStr();
				if (childName == "tag") {
					Tag *tag = new Tag();
					tag->readXML(child);
					m_tags.push_back(tag);
				}
				child = child->NextSiblingElement();
			}
		}

		/*! Point coordinate */
		double                          m_lon;
		double                          m_lat;
	};

	/*! Stores both LW and normal polyline */
	struct Way : public AbstractOSMElement {

		~Way(){
			for (size_t i = 0; i < m_nd.size(); ++i)
				delete m_nd[i];
			m_nd.clear();
		}

		void readXML(const TiXmlElement * element) {
			FUNCID(DrawingOSM::Way::readXML);

			AbstractOSMElement::readXML(element);

			// Read child elements
			const TiXmlElement * child = element->FirstChildElement();
			while (child) {
				const std::string & childName = child->ValueStr();
				if (childName == "tag") {
					Tag *tag = new Tag();
					tag->readXML(child);
					m_tags.push_back(tag);
				}
				if (childName == "nd") {
					Nd *nd = new Nd();
					nd->readXML(child);
					m_nd.push_back(nd);
				}
				child = child->NextSiblingElement();
			}
		}

		std::vector<Nd*>				m_nd;
	};

	/*! Stores both LW and normal polyline */
	struct Relation : public AbstractOSMElement {

		~Relation(){
			for (size_t i = 0; i < m_members.size(); ++i) {
					delete m_members[i];
			}
			m_members.clear();
		}

		void readXML(const TiXmlElement * element) {
			FUNCID(DrawingOSM::Relation::readXML);

			AbstractOSMElement::readXML(element);

			// Read child elements
			const TiXmlElement * child = element->FirstChildElement();
			while (child) {
				const std::string & childName = child->ValueStr();
				if (childName == "tag") {
					Tag *tag = new Tag();
					tag->readXML(child);
					m_tags.push_back(tag);
				}
				if (childName == "member") {
					Member *member = new Member();
					member->readXML(child);
					m_members.push_back(member);
				}
				child = child->NextSiblingElement();
			}
		}

		std::vector<Member*>				m_members;
	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	void readXML(const TiXmlElement * element);

	bool readOSMFile(QString filePath);

	// *** PUBLIC MEMBER VARIABLES ***

	/*! list of nodes */
	std::vector<Node*>								m_nodes;
	/*! list of ways */
	std::vector<Way*>								m_ways;
	/*! lists of relations */
	std::vector<Relation*>								m_relations;
	/*! Stores the bounding box of the drawing */
	BoundingBox									m_boundingBox;
	/*! path of the OSM File */
	QString										m_filePath;
};

} // namespace VICUS



#endif // VICUS_DRAWINGOSM_H
