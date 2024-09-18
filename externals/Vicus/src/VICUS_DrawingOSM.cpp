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
	double minx, miny, maxx, maxy;
	m_utmZone = IBKMK::LatLonToUTMXY(m_boundingBox.minlat, m_boundingBox.minlon, m_utmZone, minx, miny);
	IBKMK::LatLonToUTMXY(m_boundingBox.maxlat, m_boundingBox.maxlon, m_utmZone, maxx, maxy);

	m_centerMercatorProjection = IBKMK::Vector2D(minx + (maxx - minx) / 2,miny + (maxy - miny) / 2);
	qDebug() << "m_origin: " << QString::number(minx + (maxx - minx) / 2) << " " << QString::number(miny + (maxy - miny) / 2);
	qDebug() << "m_utmZone: " << QString::number(m_utmZone);

	m_filePath = filePath;

	return true;
}

void DrawingOSM::constructObjects()
{
	for (auto& way : m_ways) {
		createBuilding(way);
		createHighway(way);
		createWater(way);
		createLand(way);
		createLeisure(way);
		createNatural(way);
		createAmenity(way);
	}

	for (auto& relation : m_relations) {
		createBuilding(relation);
		createWater(relation);
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
	return IBKMK::Vector2D(x, y) - m_centerMercatorProjection;
}

void DrawingOSM::createBuilding(Way & way){
	if (!way.containsKey("building")) return;
	if (way.containsKeyValue("building", "cellar")) return;
	Building building;

	AreaBorder areaBorder(this);
	areaBorder.m_zPosition = 5;
	if(way.containsKeyValue("layer", "-1")) areaBorder.m_zPosition = 0;

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
	bool containsKeyTags = relation.containsKeyValue("type", "multipolygon");
	if(!(containsKeyBuilding && containsKeyTags)) return;
	Building building;

	AreaBorder areaBorder(this);
	areaBorder.m_zPosition = 5;
	if(relation.containsKeyValue("layer", "-1")) areaBorder.m_zPosition = 0;
	std::vector<const Way*> waysOuter;
	std::vector<const Way*> waysInner;

	for (int i = 0; i < relation.m_members.size(); i++) {
		if (relation.m_members[i].type != WayType) continue;
		const Way * way = findWayFromId(relation.m_members[i].ref);
		if(!way) continue;
		if (relation.m_members[i].role == "outer") {
			waysOuter.push_back(way);
		} else if (relation.m_members[i].role == "inner") {
			waysInner.push_back(way);
		}
	}

	if(waysOuter.size() <= 0) return;

	for (const Way * way : waysOuter) {
		for (int i = 0; i < way->m_nd.size() ; i++) {
			const Node * node = findNodeFromId(way->m_nd[i].ref);
			Q_ASSERT(node);
			areaBorder.m_polyline.push_back(convertLatLonToVector2D(node->m_lat, node->m_lon));
		}
	}

	for (const Way * way : waysInner) {
		std::vector<IBKMK::Vector2D> polylineInner;
		for (int i = 0; i < way->m_nd.size() ; i++) {
			const Node * node = findNodeFromId(way->m_nd[i].ref);
			Q_ASSERT(node);
			polylineInner.push_back(convertLatLonToVector2D(node->m_lat, node->m_lon));
		}
		areaBorder.m_innerPolylines.push_back(polylineInner);
	}

	areaBorder.m_multipolygon = areaBorder.m_innerPolylines.size() != 0;
	building.m_areaBorders.push_back(areaBorder);
	m_buildings.push_back(building);
}

void DrawingOSM::createHighway(Way & way)
{
	if (!way.containsKey("highway")) return;
	Highway highway;
	bool area = way.containsKeyValue("area", "yes");

	if (area) {
		AreaBorder areaBorder(this);
		areaBorder.m_zPosition = 2.7;
		if(way.containsKeyValue("layer", "-1")) areaBorder.m_zPosition = 0;
		areaBorder.m_colorArea = QColor("#78909c");

		for (int i = 0; i < way.m_nd.size() ; i++) {
			const Node * node = findNodeFromId(way.m_nd[i].ref);
			Q_ASSERT(node);
			areaBorder.m_polyline.push_back(convertLatLonToVector2D(node->m_lat, node->m_lon));
		}

		highway.m_areaBorders.push_back(areaBorder);
	} else  {
		LineFromPlanes lineFromPlanes(this);
		lineFromPlanes.m_lineThickness = 3.5;
		lineFromPlanes.m_zPosition = 3;
		lineFromPlanes.m_color = QColor("#78909c");
		for (int i = 0; i < way.m_nd.size() ; i++) {
			const Node * node = findNodeFromId(way.m_nd[i].ref);
			Q_ASSERT(node);
			lineFromPlanes.m_polyline.push_back(convertLatLonToVector2D(node->m_lat, node->m_lon));
		}
		highway.m_linesFromPlanes.push_back(lineFromPlanes);
	}

	m_highways.push_back(highway);
}

void DrawingOSM::createWater(Way & way)
{
	bool containsWater = way.containsKey("water");
	bool containsWaterway = way.containsKey("waterway");
	if( !(containsWater || containsWaterway)) return;
	Water water;

	if (containsWater) {
		AreaNoBorder areaNoBorder(this);
		areaNoBorder.m_color = QColor("#aad3df");
		areaNoBorder.m_zPosition = 2;
		if(way.containsKeyValue("layer", "-1")) areaNoBorder.m_zPosition = 0;

		for (int i = 0; i < way.m_nd.size() ; i++) {
			const Node * node = findNodeFromId(way.m_nd[i].ref);
			Q_ASSERT(node);
			areaNoBorder.m_polyline.push_back(convertLatLonToVector2D(node->m_lat, node->m_lon));
		}
		water.m_areaNoBorders.push_back(areaNoBorder);
	} else if (containsWaterway) {
		LineFromPlanes lineFromPlanes(this);
		lineFromPlanes.m_lineThickness = 1;
		lineFromPlanes.m_zPosition = 2;
		if(way.containsKeyValue("layer", "-1")) lineFromPlanes.m_zPosition = 0;
		for (int i = 0; i < way.m_nd.size() ; i++) {
			const Node * node = findNodeFromId(way.m_nd[i].ref);
			Q_ASSERT(node);
			lineFromPlanes.m_polyline.push_back(convertLatLonToVector2D(node->m_lat, node->m_lon));
		}
		water.m_linesFromPlanes.push_back(lineFromPlanes);
	}
	m_waters.push_back(water);
}

void DrawingOSM::createWater(Relation & relation)
{
	bool containsKey = relation.containsKey("water");
	bool containsKeyTags = relation.containsKeyValue("type", "multipolygon");
	if(!(containsKey && containsKeyTags)) return;
	Water water;

	AreaNoBorder areaNoBorder(this);
	areaNoBorder.m_color = QColor("#aad3df");
	areaNoBorder.m_zPosition = 1;
	if(relation.containsKeyValue("layer", "-1")) areaNoBorder.m_zPosition = 0;
	std::vector<const Way*> waysOuter;
	std::vector<const Way*> waysInner;


	for (int i = 0; i < relation.m_members.size(); i++) {
		if (relation.m_members[i].type != WayType) continue;
		const Way * way = findWayFromId(relation.m_members[i].ref);
		if(!way) continue;
		if (relation.m_members[i].role == "outer") {
			waysOuter.push_back(way);
		} else if (relation.m_members[i].role == "inner") {
			waysInner.push_back(way);
		}
	}

	if(waysOuter.size() <= 0) return;

	for (const Way * way : waysOuter) {
		for (int i = 0; i < way->m_nd.size() ; i++) {
			const Node * node = findNodeFromId(way->m_nd[i].ref);
			Q_ASSERT(node);
			areaNoBorder.m_polyline.push_back(convertLatLonToVector2D(node->m_lat, node->m_lon));
		}
	}

	for (const Way * way : waysInner) {
		std::vector<IBKMK::Vector2D> polylineInner;
		for (int i = 0; i < way->m_nd.size() ; i++) {
			const Node * node = findNodeFromId(way->m_nd[i].ref);
			Q_ASSERT(node);
			polylineInner.push_back(convertLatLonToVector2D(node->m_lat, node->m_lon));
		}
		areaNoBorder.m_innerPolylines.push_back(polylineInner);
	}

	areaNoBorder.m_multipolygon = areaNoBorder.m_innerPolylines.size() != 0;
	water.m_areaNoBorders.push_back(areaNoBorder);
	m_waters.push_back(water);

}

void DrawingOSM::createLand(Way & way)
{
	if (!way.containsKey("landuse")) return;
	Land land;
	std::string value = way.getValueFromKey("landuse");

	AreaNoBorder areaNoBorder(this);
	areaNoBorder.m_color = QColor("#c8facc");
	areaNoBorder.m_zPosition = 1;

	if (value == "residential"){
		areaNoBorder.m_color = QColor("#f2dad9");
	} else if (value == "forest") {
		areaNoBorder.m_color = QColor("#add19e");
		areaNoBorder.m_zPosition = 0;
	} else if (value == "industrial") {
		areaNoBorder.m_color = QColor("#ebdbe8");
	} else if (value == "village_green") {
		areaNoBorder.m_color = QColor("#cdebb0");
	} else if (value == "construction") {
		areaNoBorder.m_color = QColor("#c7c7b4");
	} else if (value == "grass") {
		areaNoBorder.m_color = QColor("#cdebb0");
		areaNoBorder.m_zPosition = 0;
	} else if (value == "retail") {
		areaNoBorder.m_color = QColor("#ffd6d1");
	} else if (value == "cemetery") {
		areaNoBorder.m_color = QColor("#aacbaf");
	} else if (value == "commercial") {
		areaNoBorder.m_color = QColor("#f2dad9");
	} else if (value == "public_administration") {
		areaNoBorder.m_color = QColor("#f2efe9");
	} else if (value == "railway") {
		areaNoBorder.m_color = QColor("#ebdbe8");
	} else if (value == "farmyard") {
		areaNoBorder.m_color = QColor("#f5dcba");
	} else if (value == "meadow") {
		areaNoBorder.m_color = QColor("#cdebb0");
		areaNoBorder.m_zPosition = 1.8;
	} else if (value == "religious") {
		areaNoBorder.m_color = QColor("#d0d0d0");
	} else if (value == "flowerbed") {
		areaNoBorder.m_color = QColor("#cdebb0");
		areaNoBorder.m_zPosition = 2.2;
	} else if (value == "recreation_ground") {
		areaNoBorder.m_color = QColor("#dffce2");
	} else if (value == "brownfield") {
		areaNoBorder.m_color = QColor("#c7c7b4");
	}

	for (int i = 0; i < way.m_nd.size() ; i++) {
		const Node * node = findNodeFromId(way.m_nd[i].ref);
		Q_ASSERT(node);
		areaNoBorder.m_polyline.push_back(convertLatLonToVector2D(node->m_lat, node->m_lon));
	}
	land.m_areaNoBorders.push_back(areaNoBorder);
	m_land.push_back(land);
}

void DrawingOSM::createLeisure(Way & way)
{
	if (!way.containsKey("leisure")) return;
	Leisure leisure;
	std::string value = way.getValueFromKey("landuse");

	AreaNoBorder areaNoBorder(this);
	areaNoBorder.m_color = QColor("#c8facc");
	areaNoBorder.m_zPosition = 1;

	if (value == "park"){
		areaNoBorder.m_color = QColor("#c8facc");
	}

	for (int i = 0; i < way.m_nd.size() ; i++) {
		const Node * node = findNodeFromId(way.m_nd[i].ref);
		Q_ASSERT(node);
		areaNoBorder.m_polyline.push_back(convertLatLonToVector2D(node->m_lat, node->m_lon));
	}
	leisure.m_areaNoBorders.push_back(areaNoBorder);
	m_leisure.push_back(leisure);
}

void DrawingOSM::createNatural(Way & way)
{
	if (!way.containsKey("natural")) return;
	Natural natural;
	std::string value = way.getValueFromKey("natural");

	bool noArea = false;

	QColor color = QColor("#c8facc");
	double zPosition = 1.8;

	if (value == "water"){
		color = QColor("#aad3df");
		zPosition = 2.3;
	} else if (value == "tree_row") {
		color = QColor("#b8d4a7");
		noArea = true;
	}

	if (noArea) {
		LineFromPlanes lineFromPlanes(this);
		lineFromPlanes.m_color = color;
		lineFromPlanes.m_zPosition = zPosition;
		lineFromPlanes.m_lineThickness = 3;

		if(way.containsKeyValue("layer", "-1")) lineFromPlanes.m_zPosition = 0;
		for (int i = 0; i < way.m_nd.size() ; i++) {
			const Node * node = findNodeFromId(way.m_nd[i].ref);
			Q_ASSERT(node);
			lineFromPlanes.m_polyline.push_back(convertLatLonToVector2D(node->m_lat, node->m_lon));
		}

		natural.m_linesFromPlanes.push_back(lineFromPlanes);
		m_natural.push_back(natural);
		return;
	}

	AreaNoBorder areaNoBorder(this);
	areaNoBorder.m_color = color;
	areaNoBorder.m_zPosition = zPosition;


	for (int i = 0; i < way.m_nd.size() ; i++) {
		const Node * node = findNodeFromId(way.m_nd[i].ref);
		Q_ASSERT(node);
		areaNoBorder.m_polyline.push_back(convertLatLonToVector2D(node->m_lat, node->m_lon));
	}
	natural.m_areaNoBorders.push_back(areaNoBorder);
	m_natural.push_back(natural);
}

void DrawingOSM::createAmenity(Way & way)
{
	if (!way.containsKey("amenity")) return;
	if (way.containsKey("building")) return;
	Amenity amenity;
	std::string value = way.getValueFromKey("amenity");

	AreaNoBorder areaNoBorder(this);
	areaNoBorder.m_color = QColor("#c8facc");
	areaNoBorder.m_zPosition = 2;

	if (value == "parking") {
		areaNoBorder.m_color = QColor("#eeeeee");
	} else if (value == "kindergarten") {
		areaNoBorder.m_color = QColor("#ffffe5");
	} else if (value == "school") {
		areaNoBorder.m_color = QColor("#ffffe5");
	} else if (value == "social_facility") {
		areaNoBorder.m_color = QColor("#ffffe5");
	}

	for (int i = 0; i < way.m_nd.size() ; i++) {
		const Node * node = findNodeFromId(way.m_nd[i].ref);
		Q_ASSERT(node);
		areaNoBorder.m_polyline.push_back(convertLatLonToVector2D(node->m_lat, node->m_lon));
	}
	amenity.m_areaNoBorders.push_back(areaNoBorder);
	m_amenity.push_back(amenity);
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

bool DrawingOSM::generatePlanesFromPolyline(const std::vector<IBKMK::Vector3D> & polyline, bool connectEndStart, double width, std::vector<PlaneGeometry> & planes) const
{
	// initialise values
	IBKMK::Vector3D lineVector, previousVector, crossProduct, perpendicularVector;
	std::vector<IBKMK::Vector3D> previousVertices;
	double halfWidth = width / 2;
	double length;

	// if polyline is empty, return
	if(polyline.size() < 2){
		return false;
	}

	// initialise previousVector
	previousVector = polyline[1] - polyline[0];

	auto processSegment = [&](const IBKMK::Vector3D& startPoint, const IBKMK::Vector3D& endPoint)->void {
		// calculate line vector
		lineVector = endPoint - startPoint;
		length = lineVector.magnitude();
		if(length <= 0)
			return;

		IBKMK::Vector3D normal(m_rotationMatrix.toQuaternion().toRotationMatrix()(0,2),
							   m_rotationMatrix.toQuaternion().toRotationMatrix()(1,2),
							   m_rotationMatrix.toQuaternion().toRotationMatrix()(2,2));

		// calculate perpendicular vector
		perpendicularVector = lineVector.crossProduct(normal);
		perpendicularVector.normalize();
		perpendicularVector *= halfWidth;

		// create vertices for the line
		std::vector<IBKMK::Vector3D> lineVertices = {
			startPoint - perpendicularVector,
			endPoint - perpendicularVector,
			endPoint + perpendicularVector,
			startPoint + perpendicularVector,
		};

		// Transformation for block segment
		// Draw the line
		IBKMK::Polygon3D p(VICUS::Polygon2D::T_Rectangle, lineVertices[0], lineVertices[3], lineVertices[1]);
		planes.push_back(VICUS::PlaneGeometry(p));

		// Calculate the cross product between the current line Vector and previous to get the direction of the triangle
		crossProduct = lineVector.crossProduct(previousVector);

		if (previousVertices.size() == lineVertices.size()) {
			// draws the triangle
			if(crossProduct.m_z > 1e-10){
				// line is left
				std::vector<IBKMK::Vector3D> verts(3);
				verts[0] = previousVertices[1];
				verts[1] = startPoint;
				verts[2] = lineVertices[0];

				IBKMK::Polygon3D poly3d(verts);
				planes.push_back(PlaneGeometry(poly3d));
			}
			else if(crossProduct.m_z < -1e-10){
				// line is right

				// line is left
				std::vector<IBKMK::Vector3D> verts(3);
				verts[0] = lineVertices[3];
				verts[1] = previousVertices[2];
				verts[2] = startPoint;

				IBKMK::Polygon3D poly3d(verts);
				planes.push_back(PlaneGeometry(poly3d));
			}
			else {
				// if z coordinate of cross product is 0, lines are parallel, no triangle needed (would crash anyway)
				previousVector = lineVector;
				previousVertices = lineVertices;
				return;
			}
		}

		// update previous values
		previousVector = lineVector;
		previousVertices = lineVertices;
	};

	// loops through all points in polyline, draws a line between every two points, adds a triangle between two lines to fill out the gaps
	for (unsigned int i = 0; i < polyline.size() - 1; i++) {
		processSegment(polyline[i], polyline[i+1]);
	}

	// repeats the code of the for loop for the last line and adds two triangles to fill out the lines
	if(connectEndStart){
		unsigned int lastIndex = polyline.size() - 1;
		processSegment(polyline[lastIndex], polyline[0]);
		processSegment(polyline[0], polyline[1]);
	}

	return true;
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

std::string DrawingOSM::AbstractOSMElement::getValueFromKey(const std::string & key) const
{
	for (int i = 0; i < m_tags.size(); i++) {
		if(m_tags[i].key == key)
			return m_tags[i].value;
	}
	return std::string("");
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

const void DrawingOSM::AreaBorder::addGeometryData(std::vector<VICUS::DrawingOSM::GeometryData*>& data) const
{
	FUNCID(DrawingOSM::AreaBorder::addGeometryData);
	try {
		if (m_dirtyTriangulation) {
			m_geometryData.clear();

			std::vector<IBKMK::Vector3D> areaPoints;

			for (int i = 1; i < m_polyline.size(); i++) {
				IBKMK::Vector3D p = IBKMK::Vector3D(m_polyline[i].m_x,
													m_polyline[i].m_y,
													m_zPosition * Z_MULTIPLYER);

				QVector3D vec = m_drawing->m_rotationMatrix.toQuaternion() * IBKVector2QVector(p);
				vec += IBKVector2QVector(m_drawing->m_origin);

				areaPoints.push_back(QVector2IBKVector(vec));
			}

			VICUS::Polygon3D polygon3D(areaPoints);
			GeometryData geometryData;
			// Initialize PlaneGeometry with the polygon
			geometryData.m_planeGeometry.push_back(VICUS::PlaneGeometry(polygon3D));

			if(m_multipolygon) {
				std::vector<PlaneGeometry::Hole> holes;
				for(int j = 0; j < m_innerPolylines.size(); j++) {
					VICUS::Polygon2D polygon2d(m_innerPolylines[j]);
					holes.push_back(PlaneGeometry::Hole(j, polygon2d, false));
				}

				VICUS::PlaneGeometry& planeGeometry = geometryData.m_planeGeometry.back();
				planeGeometry.setHoles(holes);
			}

			geometryData.m_color = m_colorArea;
			m_geometryData.push_back(geometryData);

			m_dirtyTriangulation = false;
		}
		for(auto& geometryData : m_geometryData) {
			data.push_back(&geometryData);
		}
	}
	catch (IBK::Exception &ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error generating plane geometries for 'DrawingOSM::AreaBorder' element.\n%1").arg(ex.what()), FUNC_ID);
	}
}

const void DrawingOSM::Building::addGeometryData(std::vector<VICUS::DrawingOSM::GeometryData*> &data) const
{
	for (auto& areaBorder : m_areaBorders) {
		areaBorder.addGeometryData(data);
	}
}

const void DrawingOSM::Highway::addGeometryData(std::vector<GeometryData *> & data) const
{
	for (auto& lineFromPlanes : m_linesFromPlanes) {
		lineFromPlanes.addGeometryData(data);
	}
	for (auto& areaBorder : m_areaBorders) {
		areaBorder.addGeometryData(data);
	}
}

const void DrawingOSM::AreaNoBorder::addGeometryData(std::vector<GeometryData *> & data) const
{
	FUNCID(DrawingOSM::AreaNoBorder::addGeometryData);
	try {
		if (m_dirtyTriangulation) {
			m_geometryData.clear();

			std::vector<IBKMK::Vector3D> areaPoints;

			for (int i = 1; i < m_polyline.size(); i++) {
				IBKMK::Vector3D p = IBKMK::Vector3D(m_polyline[i].m_x,
													m_polyline[i].m_y,
													m_zPosition * Z_MULTIPLYER);

				QVector3D vec = m_drawing->m_rotationMatrix.toQuaternion() * IBKVector2QVector(p);
				vec += IBKVector2QVector(m_drawing->m_origin);

				areaPoints.push_back(QVector2IBKVector(vec));
			}

			VICUS::Polygon3D polygon3D(areaPoints);
			GeometryData geometryData;
			// Initialize PlaneGeometry with the polygon
			geometryData.m_planeGeometry.push_back(VICUS::PlaneGeometry(polygon3D));

			if(m_multipolygon) {
				std::vector<PlaneGeometry::Hole> holes;
				for(int j = 0; j < m_innerPolylines.size(); j++) {
					VICUS::Polygon2D polygon2d(m_innerPolylines[j]);
					holes.push_back(PlaneGeometry::Hole(j, polygon2d, false));
				}

				VICUS::PlaneGeometry& planeGeometry = geometryData.m_planeGeometry.back();
				planeGeometry.setHoles(holes);
			}

			geometryData.m_color = m_color;
			m_geometryData.push_back(geometryData);

			m_dirtyTriangulation = false;
		}
		for (auto& geometryData : m_geometryData) {
			data.push_back(&geometryData);
		}
	}
	catch (IBK::Exception &ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error generating plane geometries for 'DrawingOSM::AreaNoBorder' element.\n%1").arg(ex.what()), FUNC_ID);
	}
}

const void DrawingOSM::LineFromPlanes::addGeometryData(std::vector<GeometryData *> & data) const
{
	FUNCID(DrawingOSM::LineFromPlanes::addGeometryData);
	try {
		if (m_dirtyTriangulation) {

			// Create Vector to store vertices of polyline
			std::vector<IBKMK::Vector3D> polylinePoints;

			// adds z-coordinate to polyline
			for(unsigned int i = 0; i < m_polyline.size(); ++i){
				IBKMK::Vector3D p = IBKMK::Vector3D(m_polyline[i].m_x,
													m_polyline[i].m_y,
													m_zPosition * Z_MULTIPLYER);
				QVector3D vec = m_drawing->m_rotationMatrix.toQuaternion() * IBKVector2QVector(p);
				vec += IBKVector2QVector(m_drawing->m_origin);

				polylinePoints.push_back(QVector2IBKVector(vec));
			}

			std::vector<PlaneGeometry> planeGeometry;
			if (m_drawing->generatePlanesFromPolyline(polylinePoints, false, m_lineThickness, planeGeometry)) {
				GeometryData geometryData;
				geometryData.m_planeGeometry = planeGeometry;
				geometryData.m_color = m_color;
				m_geometryData.push_back(geometryData);
			}
		}
		for (auto& geometryData : m_geometryData) {
			data.push_back(&geometryData);
		}
	}
	catch (IBK::Exception &ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error generating plane geometries for 'DrawingOSM::LineFromPlanes' element.\n%1").arg(ex.what()), FUNC_ID);
	}
}

const void DrawingOSM::Water::addGeometryData(std::vector<GeometryData *> & data) const
{
	for (auto& areaNoBorder : m_areaNoBorders) {
		areaNoBorder.addGeometryData(data);
	}
	for (auto& lineFromPlanes : m_linesFromPlanes) {
		lineFromPlanes.addGeometryData(data);
	}
}

const void DrawingOSM::Land::addGeometryData(std::vector<GeometryData *> & data) const
{
	for (auto& areaNoBorder : m_areaNoBorders) {
		areaNoBorder.addGeometryData(data);
	}
}

const void DrawingOSM::Leisure::addGeometryData(std::vector<GeometryData *> & data) const
{
	for (auto& areaNoBorder : m_areaNoBorders) {
		areaNoBorder.addGeometryData(data);
	}
}

const void DrawingOSM::Natural::addGeometryData(std::vector<GeometryData *> & data) const
{
	for (auto& areaNoBorder : m_areaNoBorders) {
		areaNoBorder.addGeometryData(data);
	}
	for (auto& lineFromPlanes : m_linesFromPlanes) {
		lineFromPlanes.addGeometryData(data);
	}
}

const void DrawingOSM::Amenity::addGeometryData(std::vector<GeometryData *> & data) const
{
	for (auto& areaNoBorder : m_areaNoBorders) {
		areaNoBorder.addGeometryData(data);
	}
}

} // namespace VICUS
