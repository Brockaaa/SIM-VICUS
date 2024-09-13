#include "VICUS_DrawingOSM.h"
#include "VICUS_Constants.h"

#include "IBK_MessageHandler.h"
#include "IBK_messages.h"
#include "IBK_physics.h"

#include "NANDRAD_Utilities.h"

#include <QDebug>
#include "tinyxml.h"

/*! IBKMK::Vector3D to QVector3D conversion macro. */
inline QVector3D IBKVector2QVector(const IBKMK::Vector3D & v) {
	return QVector3D((float)v.m_x, (float)v.m_y, (float)v.m_z);
}

/*! QVector3D to IBKMK::Vector3D to conversion macro. */
inline IBKMK::Vector3D QVector2IBKVector(const QVector3D & v) {
	return IBKMK::Vector3D((double)v.x(), (double)v.y(), (double)v.z());
}

namespace VICUS {


void DrawingOSM::readXML(const TiXmlElement * element) {
	FUNCID(DrawingOSM::readXML);

	try {
		// search for mandatory attributes

		// reading attributes
		const TiXmlAttribute * attrib = element->FirstAttribute();
		while (attrib) {
			const std::string & attribName = attrib->NameStr();
			if (attribName == "bounds") {
			}
			attrib = attrib->Next();
		}
		// search for mandatory elements
		// reading elements
		const TiXmlElement * c = element->FirstChildElement();
		while (c) {
			const std::string & cName = c->ValueStr();
			if (cName == "bounds") {
				// search for mandatory attributes
				if (!TiXmlAttribute::attributeByName(c, "minlat"))
					throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(c->Row()).arg(
											 IBK::FormatString("Missing required 'minlat' attribute.") ), FUNC_ID);
				if (!TiXmlAttribute::attributeByName(c, "minlon"))
					throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(c->Row()).arg(
											 IBK::FormatString("Missing required 'minlon' attribute.") ), FUNC_ID);
				if (!TiXmlAttribute::attributeByName(c, "maxlat"))
					throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(c->Row()).arg(
											 IBK::FormatString("Missing required 'maxlat' attribute.") ), FUNC_ID);
				if (!TiXmlAttribute::attributeByName(c, "maxlon"))
					throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(c->Row()).arg(
											 IBK::FormatString("Missing required 'maxlon' attribute.") ), FUNC_ID);

				// reading attributes
				const TiXmlAttribute * attrib = c->FirstAttribute();
				while (attrib) {
					const std::string & attribName = attrib->NameStr();
					if (attribName == "minlat")
						m_boundingBox.minlat = attrib->DoubleValue();
					else if (attribName == "minlon")
						m_boundingBox.minlon = attrib->DoubleValue();
					else if (attribName == "maxlat")
						m_boundingBox.maxlat = attrib->DoubleValue();
					else if (attribName == "maxlon")
						m_boundingBox.maxlon = attrib->DoubleValue();
					attrib = attrib->Next();
				}
			}
			else if (cName == "node") {
				Node obj;
				obj.readXML(c);
				m_nodes.push_back(obj);
			}
			else if (cName == "way") {
				Way obj ;
				obj.readXML(c);
				m_ways.push_back(obj);
			}
			else if (cName == "relation") {
				Relation obj;
				obj.readXML(c);
				m_relations.push_back(obj);
			}
			c = c->NextSiblingElement();
		}
	}
	catch (IBK::Exception & ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error reading 'Drawing' element."), FUNC_ID);
	}
	catch (std::exception & ex2) {
		throw IBK::Exception( IBK::FormatString("%1\nError reading 'Drawing::Text' element.").arg(ex2.what()), FUNC_ID);
	}
}

bool DrawingOSM::readOSMFile(QString filePath)
{
	TiXmlDocument document(filePath.toStdString());

	if (!document.LoadFile()) {
		qDebug() << "Failed to load file: " << filePath;
		qDebug() << "Error: " << document.ErrorDesc();
		return false;
	}

	TiXmlElement* root = document.RootElement();
	if (!root) {
		qDebug() << "Failed to get root element";
		return false;
	}

	// Print the root element's name
	qDebug() << "Root element: " << root->Value();

	readXML(document.RootElement());
	double x, y;
	m_utmZone = IBKMK::LatLonToUTMXY(m_boundingBox.minlat, m_boundingBox.minlon, m_utmZone, x, y);

	m_originMercatorProjection = IBKMK::Vector2D(x,y);
	qDebug() << "m_origin: " << QString::number(x) << " " << QString::number(y);
	qDebug() << "m_utmZone: " << QString::number(m_utmZone);

	m_filePath = filePath;

	return true;
}

void DrawingOSM::constructObjects()
{
	for (auto& way : m_ways) {
		createBuilding(way);
	}
}

void DrawingOSM::updatePlaneGeometries()
{
	for (auto& building : m_buildings) {
		for (auto& areaBorder : building.m_areaBorders ){
			areaBorder.updatePlaneGeometry();
		}
	}

}

const DrawingOSM::Node * DrawingOSM::findNodeFromId(unsigned int id) const
{
	for (auto& node : m_nodes) {
		if (node.m_id == id) return &node;
	}
	return nullptr;
}

const DrawingOSM::Way * DrawingOSM::findWayFromId(unsigned int id) const
{
	for (auto& way : m_ways) {
		if (way.m_id == id) return &way;
	}
	return nullptr;
}

const DrawingOSM::Relation * DrawingOSM::findRelationFromId(unsigned int id) const
{
	for (auto& relation : m_relations) {
		if (relation.m_id == id) return &relation;
	}
	return nullptr;
}

inline IBKMK::Vector2D DrawingOSM::convertLatLonToVector2D(double lat, double lon)
{
	double x, y;
	IBKMK::LatLonToUTMXY(lat, lon, m_utmZone, x, y);
	return IBKMK::Vector2D(x, y) - m_originMercatorProjection;
}

void DrawingOSM::createBuilding(Way & way){
	if (!way.containsKey("building")) return;
	Building building;

	AreaBorder areaBorder(this);

	for (int i = 0; i < way.m_nd.size() ; i++) {
		const Node * node = findNodeFromId(way.m_nd[i].ref);
		Q_ASSERT(node);
		areaBorder.m_polyline.push_back(convertLatLonToVector2D(node->m_lat, node->m_lon));
	}

	building.m_areaBorders.push_back(areaBorder);
	m_buildings.push_back(building);
}

void DrawingOSM::createBuilding(Relation & relation){
	bool containsKeyBuilding = relation.containsKey("building");
	bool containsKeyTags = relation.containsKeyValue("tags", "building");
	Q_ASSERT(containsKeyBuilding || containsKeyTags);
	Building building;

	std::vector<const Node*> nodes;
	std::vector<const Way*> ways;
	bool outline = false;

	processRelation(relation, nodes, ways, outline);

	//Polyline buildingOutline;

}

void DrawingOSM::processRelation(const Relation & relation, std::vector<const Node *> & nodes, std::vector<const Way *> & ways, bool & outline) {
	if (relation.containsKey("building:part")) return; // if relation contains building:part, it is presumably only 3D information, skip



	for (const Member& member : relation.m_members) {
		if (member.type == NodeType) {
			const Node* node = findNodeFromId(member.ref);
			if (node) {
				nodes.push_back(node);
			}
		}
		else if (member.type == WayType) {
			const Way* way = findWayFromId(member.ref);
			if (!way) continue;
			if (way->containsKey("building:part")) continue;
			ways.push_back(way);
		}
		else if(member.type == RelationType) {
			const Relation* subRelation = findRelationFromId(member.ref);
			if(subRelation) {
				processRelation(*subRelation, nodes, ways, outline);
			}
		}
	}
}

void DrawingOSM::AbstractOSMElement::readXML(const TiXmlElement * element){
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

bool DrawingOSM::AbstractOSMElement::containsKey(const std::string& key) const
{
	for (int i = 0; i < m_tags.size(); i++) {
		if(m_tags[i].key == key)
			return true;
	}
	return false;
}

bool DrawingOSM::AbstractOSMElement::containsValue(const std::string& value) const
{
	for (int i = 0; i < m_tags.size(); i++) {
		if(m_tags[i].value == value)
			return true;
	}
	return false;
}

bool DrawingOSM::AbstractOSMElement::containsKeyValue(const std::string & key, const std::string & value) const
{
	for (int i = 0; i < m_tags.size(); i++) {
		if(m_tags[i].key == key && m_tags[i].value == value)
			return true;
	}
	return false;
}

void DrawingOSM::Nd::readXML(const TiXmlElement * element) {
	FUNCID(DrawingOSM::nd::readXML);

	if (!TiXmlAttribute::attributeByName(element, "ref"))
		throw IBK::Exception( IBK::FormatString(XML_READ_ERROR).arg(element->Row()).arg(
								 IBK::FormatString("Missing required 'ref' attribute.") ), FUNC_ID);

	ref = TiXmlAttribute::attributeByName(element, "ref")->IntValue();
}

void DrawingOSM::Member::readXML(const TiXmlElement * element) {
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

void DrawingOSM::Tag::readXML(const TiXmlElement * element) {
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

void DrawingOSM::Node::readXML(const TiXmlElement * element) {
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
			Tag tag;
			tag.readXML(child);
			m_tags.push_back(tag);
		}
		child = child->NextSiblingElement();
	}
}

void DrawingOSM::Way::readXML(const TiXmlElement * element) {
	FUNCID(DrawingOSM::Way::readXML);

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
			nd.readXML(child);
			m_nd.push_back(nd);
		}
		child = child->NextSiblingElement();
	}
}

void DrawingOSM::Relation::readXML(const TiXmlElement * element) {
	FUNCID(DrawingOSM::Relation::readXML);

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

const std::vector<PlaneGeometry> & DrawingOSM::AreaBorder::planeGeometries() const
{
	FUNCID(DrawingOSM::AreaBorder::planeGeometries);
	try {
		if (m_dirtyTriangulation) {
			m_planeGeometries.clear();

			std::vector<IBKMK::Vector3D> areaPoints;

			for(unsigned int i = 0; i < m_polyline.size(); i++){
				IBKMK::Vector3D p = IBKMK::Vector3D(m_polyline[i].m_x,
													m_polyline[i].m_y,
													m_zPosition * Z_MULTIPLYER);

				QVector3D vec = m_drawing->m_rotationMatrix.toQuaternion() * IBKVector2QVector(p);
				vec += IBKVector2QVector(m_drawing->m_origin);

				areaPoints.push_back(QVector2IBKVector(vec));
			}

			VICUS::Polygon3D polygon3D(areaPoints);

			// Initialize PlaneGeometry with the polygon
			m_planeGeometries.push_back(VICUS::PlaneGeometry(polygon3D));

			return m_planeGeometries;

			m_dirtyTriangulation = false;
		}
	}
	catch (IBK::Exception &ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error generating plane geometries for 'DrawingOSM::AreaBorder' element.\n%1").arg(ex.what()), FUNC_ID);
	}
}

} // namespace VICUS
