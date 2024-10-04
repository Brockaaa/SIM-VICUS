#include "VICUS_DrawingOSM.h"
#include "VICUS_Constants.h"

#include "IBK_MessageHandler.h"
#include "IBK_messages.h"
#include "IBK_physics.h"

#include <unordered_set>

#include "NANDRAD_Utilities.h"

#include "IBKMK_2DCalculations.h"
#include "IBKMK_3DCalculations.h"

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


std::vector<IBKMK::Vector2D> DrawingOSM::convertHoleToLocalCoordinates(
	const std::vector<IBKMK::Vector3D>& globalVertices,
	const IBKMK::Vector3D& offset,
	const IBKMK::Vector3D& localX,
	const IBKMK::Vector3D& localY) const {
	std::vector<IBKMK::Vector2D> localVertices;
	localVertices.reserve(globalVertices.size());

	for (const IBKMK::Vector3D& globalVertex : globalVertices) {
		double x_local, y_local;
		// Use the planeCoordinates function to convert global to local coordinates
		if (IBKMK::planeCoordinates(offset, localX, localY, globalVertex, x_local, y_local)) {
			localVertices.emplace_back(x_local, y_local);
		}
		else {
			// Handle the case where the projection fails
			// For example, you can log an error or throw an exception
			throw std::runtime_error("Failed to project global vertex to local coordinates.");
		}
	}

	return localVertices;
}

void DrawingOSM::createMultipolygonFromWay(VicOSM::Way & way, VicOSM::Multipolygon & multipolygon)
{
	for (int i = 0; i < way.m_nd.size() ; i++) {
		const VicOSM::Node * node = findNodeFromId(way.m_nd[i].ref);
		Q_ASSERT(node);
		multipolygon.m_outerPolyline.push_back(convertLatLonToVector2D(node->m_lat, node->m_lon));
	}
}

void DrawingOSM::createMultipolygonsFromRelation(VicOSM::Relation & relation, std::vector<VicOSM::Multipolygon> & multipolygons)
{
	auto processWay = [&](std::vector<int>& nodeRefs, int wayRef) -> bool {
		const VicOSM::Way* way = findWayFromId(wayRef);
		if(!way) return false;
		for (int i = 0; i < way->m_nd.size(); i++) {
			nodeRefs.push_back(way->m_nd[i].ref);
		}
		return true;
	};

	std::vector<WayWithMarks> ways;

	//for (int i = 0; i < relation.m_members.size(); i++) {
	//	if (relation.m_members[i].type != VicOSM::AbstractOSMElement::WayType) continue;
	//	WayWithMarks way;
	//	/* if not all ways available, it is likely a huge multipolygon that is partially outside of the boundingbox of the .osm file.
	//	 * To avoid weird bugs (e.g. areas covered by the polygon that should not be covered), we skip this incomplete multipolygon */
	//	if (!processWay(way.refs, relation.m_members[i].ref))
	//		return;
	//	ways.push_back(way);
	//}

	std::vector<std::vector<WayWithMarks*>> rings;
	// first creates all possible areas/rings out of the set of open and closed ways
	ringAssignment(ways, rings);
	// then calculates if the areas contain each other and tries to create Multipolygons with holes
	ringGrouping(rings, multipolygons);

}

void DrawingOSM::ringAssignment(std::vector<WayWithMarks> & ways, std::vector<std::vector<WayWithMarks*>>& allRings)
{
	std::vector<WayWithMarks*> currentRing;

	// get next unassigned way for a new ring
	std::function<bool()> createNewRing = [&]() -> bool {
		currentRing.clear();
		for (auto& way : ways) {
			if (!way.assigned) {
				way.assigned = true;
				if(way.refs.empty()) {
					return createNewRing();
				}
				currentRing.push_back(&way);
				return true;
			}
		}
		return false;
	};

	// uses Polygon3D to check if the
	auto checkIfValidGeometry = [&]() -> bool {
		std::vector<IBKMK::Vector2D> polyline = convertVectorWayWithMarksToVector2D(currentRing);
		Polygon2D polygon(polyline);
		return polygon.isValid();
	};

	auto getNewWay = [&]() -> bool {
		int nodeID = currentRing.back()->reversedOrder ? currentRing.back()->refs.front() : currentRing.back()->refs.back();
		for (auto& way : ways) {
			if (way.assigned || way.selected) continue;
			if (way.refs.empty()) {
				way.assigned = true;
				continue;
			}
			if (way.refs.back() == nodeID) {
				way.reversedOrder = true;
				way.selected = true;
				currentRing.push_back(&way);
				return true;
			} else if (way.refs.front() == nodeID) {
				way.selected = true;
				currentRing.push_back(&way);
				return true;
			}
		}
		return false;
	};

	auto constructRing = [&]() -> bool {
		while(true) {
			if (!currentRing.front()->refs.empty() && !currentRing.back()->refs.empty() &&
				currentRing.front()->refs[0] == (currentRing.back()->reversedOrder ? currentRing.back()->refs.front() : currentRing.back()->refs.back())) {
				if (checkIfValidGeometry()) {
					for (WayWithMarks* way : currentRing) {
						way->assigned = true;
					}
					allRings.push_back(currentRing);
					return true;
				} else {
					return false;
				}
			} else {
				if (getNewWay()) {
					continue;
				} else {
					for (auto it = currentRing.begin(); it != currentRing.end();) {
						if ((*it)->selected) {
							(*it)->selected = false;
							it = currentRing.erase(it);
						} else {
							++it;
						}
					}
					if (checkIfValidGeometry()) {
						allRings.push_back(currentRing);
						return true;
					}
					return false;
				}
			}
		}
	};

	while (createNewRing()) {
		constructRing();
	}
}

std::vector<IBKMK::Vector2D> DrawingOSM::convertVectorWayWithMarksToVector2D(const std::vector<WayWithMarks*>& ways){
	std::vector<IBKMK::Vector2D> vectorCoordinates;
	for (WayWithMarks * way : ways) {
		if (way->reversedOrder) {
			for (int i = way->refs.size() - 1; i >= 0; i--) {
				const VicOSM::Node *node = findNodeFromId(way->refs[i]);
				Q_ASSERT(node);
				vectorCoordinates.push_back(convertLatLonToVector2D(node->m_lat, node->m_lon));
			}
		} else {
			for (int refs : way->refs) {
				const VicOSM::Node *node = findNodeFromId(refs);
				Q_ASSERT(node);
				vectorCoordinates.push_back(convertLatLonToVector2D(node->m_lat, node->m_lon));
			}
		}
	}
	return vectorCoordinates;
}

void DrawingOSM::ringGrouping(std::vector<std::vector<WayWithMarks *> >& rings, std::vector<VicOSM::Multipolygon>& multipolygons)
{

	// create Matrix and reset available flags
	// matrix[i][j] true if ring i is in ring j
	std::vector<std::vector<bool>> matrix;
	std::vector<std::vector<IBKMK::Vector2D>> ringsVector;

	for (auto& ring : rings) {
		ringsVector.push_back(convertVectorWayWithMarksToVector2D(ring));
	}

	std::vector<int> usedRings;
	int size = rings.size();
	for (int i = 0; i < size; i++) {
		std::vector<bool> row;
		for(WayWithMarks * way : rings[i]) way->assigned = false;
		row.resize(size);
		for (int j = 0; j < size; j++) {
			// ring does not contain itself
			if(i == j) {
				row[j] = false;
			}
			int contained = 1 == IBKMK::polygonInPolygon(ringsVector[i], ringsVector[j]);
			row[j] = contained;
		}
		matrix.push_back(row);
	}

	int activeOuterRing;
	std::function<bool()> findOuterRing = [&]() -> bool {
		for (unsigned int i = 0; i < rings.size(); i++) {
			if (std::find(usedRings.begin(), usedRings.end(), i) != usedRings.end())  continue;
			bool isInnerRing = false;
			for (unsigned int j = 0; j < matrix.size(); j++) {
				if (std::find(usedRings.begin(), usedRings.end(), j) != usedRings.end())  continue;
				if (matrix[i][j]) {
					isInnerRing = true;
					break;
				}
			}

			if (!isInnerRing) {
				activeOuterRing = i;
				usedRings.push_back(i);
				return true;
			}
		}
		return false;
	};

	// checks if ring is contained in the active Outer Ring and not contained in any other unused ring
	std::function<void(VicOSM::Multipolygon&)> addAllInners = [&](VicOSM::Multipolygon& multipolygon) {
		for (unsigned int i = 0; i < matrix.size(); i++) {
			if (std::find(usedRings.begin(), usedRings.end(), i) != usedRings.end())  continue;
			if (matrix[i][activeOuterRing]) {
				for (unsigned int j = 0; j < matrix.size(); j++) {
					if (std::find(usedRings.begin(), usedRings.end(), j) != usedRings.end())  continue;
					if (j != activeOuterRing && matrix[i][j]) {
						continue;
					}
				}
				usedRings.push_back(i);
				multipolygon.m_innerPolylines.push_back(ringsVector[i]);
			}
		}


		/* converts coordinates of holes to coordinate system of outer polygon to make it compatible
		 * with PlaneGeometry setHoles */

		std::vector<IBKMK::Vector3D> outerPolygon;

		for (int i = 1; i < multipolygon.m_outerPolyline.size(); i++) {
			IBKMK::Vector3D p = IBKMK::Vector3D(multipolygon.m_outerPolyline[i].m_x,
												multipolygon.m_outerPolyline[i].m_y,
												0);

			QVector3D vec = m_rotationMatrix.toQuaternion() * IBKVector2QVector(p);
			vec += IBKVector2QVector(m_origin);

			outerPolygon.push_back(QVector2IBKVector(vec));
		}

		VICUS::PlaneGeometry outerPlaneGeometry (outerPolygon);
		if (!outerPlaneGeometry.isValid()) return;

		for (auto& innerPolyline : multipolygon.m_innerPolylines) {
			std::vector<IBKMK::Vector3D> innerPolygon;

			for (int i = 1; i < innerPolyline.size(); i++) {
				IBKMK::Vector3D p = IBKMK::Vector3D(innerPolyline[i].m_x,
													innerPolyline[i].m_y,
													0);

				QVector3D vec = m_rotationMatrix.toQuaternion() * IBKVector2QVector(p);
				vec += IBKVector2QVector(m_origin);

				innerPolygon.push_back(QVector2IBKVector(vec));
			}

			innerPolyline = convertHoleToLocalCoordinates(innerPolygon, outerPlaneGeometry.offset(), outerPlaneGeometry.localX(), outerPlaneGeometry.localY());

		}

		multipolygons.push_back(multipolygon);

	};

	while(findOuterRing()) {
		VicOSM::Multipolygon multipolygon;
		multipolygon.m_outerPolyline = ringsVector[activeOuterRing];
		addAllInners(multipolygon);
	}

}

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
				VicOSM::Node obj;
				obj.readXML(c);
				m_nodes[obj.m_id] = obj;
			}
			else if (cName == "way") {
				VicOSM::Way obj ;
				obj.readXML(c);
				m_ways[obj.m_id] = obj;
			}
			else if (cName == "relation") {
				VicOSM::Relation obj;
				obj.readXML(c);
				m_relations[obj.m_id] = obj;
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
	/* order relevant. For example heritage should come at the very end because key heritage
	 * is not supposed to occur alone and only in combination with other keys like place.
	 * In practice this does not always happen */
	//for (auto& pair : m_nodes) {
	//	if (pair.second.containsKey("natural")) {
	//		createNatural(pair.second);
	//	}
	//}

	//for (auto& pair : m_ways) {
	//	if (pair.second.containsKey("building"))
	//		createBuilding(pair.second);
	//	else if (pair.second.containsKey("highway"))
	//		createHighway(pair.second);
	//	else if (pair.second.containsKey("water") || pair.second.containsKey("waterway"))
	//		createWater(pair.second);
	//	else if (pair.second.containsKey("landuse"))
	//		createLand(pair.second);
	//	else if (pair.second.containsKey("leisure"))
	//		createLeisure(pair.second);
	//	else if (pair.second.containsKey("natural"))
	//		createNatural(pair.second);
	//	else if (pair.second.containsKey("amenity"))
	//		createAmenity(pair.second);
	//	else if (pair.second.containsKey("bridge"))
	//		createBridge(pair.second);
	//	else if (pair.second.containsKey("tourism"))
	//		createTourism(pair.second);
	//	else if (pair.second.containsKey("barrier"))
	//		createBarrier(pair.second);
	//	else if (pair.second.containsKey("place") || pair.second.containsKey("heritage"))
	//		createPlace(pair.second);
	//}

	//for (auto& pair : m_relations) {
	//	if (pair.second.containsKey("building"))
	//		createBuilding(pair.second);
	//	else if (pair.second.containsKey("place"))
	//		createPlace(pair.second);
	//	else if (pair.second.containsKey("water") || pair.second.containsKey("waterway"))
	//		createWater(pair.second);
	//	else if (pair.second.containsKey("highway"))
	//		createHighway(pair.second);
	//	else if (pair.second.containsKey("landuse"))
	//		createLand(pair.second);
	//}

	std::function<int(const AbstractOSMObject&)> convertKeyToInt = [&](const AbstractOSMObject& object){
		if(object.m_layer == 0) {
			return static_cast<int>(object.m_keyValue);
		}

		switch (object.m_layer) {
			case -5: {
				if (static_cast<int>(object.m_keyValue) < static_cast<int>(LAYERHIGHWAYNEG5)){
					return static_cast<int>(LAYERLANDUSENEG5);
				} else {
					return static_cast<int>(LAYERHIGHWAYNEG5);
				}
				break;
			}
			case -4: {
				if (static_cast<int>(object.m_keyValue) < static_cast<int>(LAYERHIGHWAYNEG5)){
					return static_cast<int>(LAYERLANDUSENEG4);
				} else {
					return static_cast<int>(LAYERHIGHWAYNEG4);
				}
				break;
			}
			case -3: {
				if (static_cast<int>(object.m_keyValue) < static_cast<int>(LAYERHIGHWAYNEG5)){
					return static_cast<int>(LAYERLANDUSENEG3);
				} else {
					return static_cast<int>(LAYERHIGHWAYNEG3);
				}
				break;
			}
			case -2: {
				if (static_cast<int>(object.m_keyValue) < static_cast<int>(LAYERHIGHWAYNEG5)){
					return static_cast<int>(LAYERLANDUSENEG2);
				} else {
					return static_cast<int>(LAYERHIGHWAYNEG2);
				}
				break;
			}
			case -1: {
				if (static_cast<int>(object.m_keyValue) < static_cast<int>(LAYERHIGHWAYNEG5)){
					return static_cast<int>(LAYERLANDUSENEG1);
				} else {
					return static_cast<int>(LAYERHIGHWAYNEG1);
				}
				break;
			}
			case 5: {
				if (static_cast<int>(object.m_keyValue) < static_cast<int>(LAYERHIGHWAYNEG5)){
					return static_cast<int>(LAYERLANDUSE5);
				} else {
					return static_cast<int>(LAYERHIGHWAY5);
				}
				break;
			}
			case 4: {
				if (static_cast<int>(object.m_keyValue) < static_cast<int>(LAYERHIGHWAYNEG5)){
					return static_cast<int>(LAYERLANDUSE4);
				} else {
					return static_cast<int>(LAYERHIGHWAY4);
				}
				break;
			}
			case 3: {
				if (static_cast<int>(object.m_keyValue) < static_cast<int>(LAYERHIGHWAYNEG5)){
					return static_cast<int>(LAYERLANDUSE3);
				} else {
					return static_cast<int>(LAYERHIGHWAY3);
				}
				break;
			}
			case 2: {
				if (static_cast<int>(object.m_keyValue) < static_cast<int>(LAYERHIGHWAYNEG5)){
					return static_cast<int>(LAYERLANDUSE2);
				} else {
					return static_cast<int>(LAYERHIGHWAY2);
				}
				break;
			}
			case 1: {
				if (static_cast<int>(object.m_keyValue) < static_cast<int>(LAYERHIGHWAYNEG5)){
					return static_cast<int>(LAYERLANDUSE1);
				} else {
					return static_cast<int>(LAYERHIGHWAY1);
				}
				break;
			}
			default:
				return static_cast<int>(static_cast<int>(object.m_keyValue));
		}

	};

	std::vector<int> usedKeyValues;

	for (const auto & building : m_buildings) {
		usedKeyValues.push_back(convertKeyToInt(building));
	}

	for( const auto & highway : m_highways) {
		usedKeyValues.push_back(convertKeyToInt(highway));
	}

	for( const auto & water : m_waters) {
		usedKeyValues.push_back(convertKeyToInt(water));
	}

	for( const auto & land : m_land) {
		usedKeyValues.push_back(convertKeyToInt(land));
	}

	for( const auto & leisure : m_leisure) {
		usedKeyValues.push_back(convertKeyToInt(leisure));
	}

	for( const auto & natural : m_natural) {
		usedKeyValues.push_back(convertKeyToInt(natural));
	}

	for( const auto & amenity : m_amenities) {
		usedKeyValues.push_back(convertKeyToInt(amenity));
	}

	for( const auto & place : m_places) {
		usedKeyValues.push_back(convertKeyToInt(place));
	}

	for( const auto & bridge : m_bridges) {
		usedKeyValues.push_back(convertKeyToInt(bridge));
	}

	for( const auto & tourism : m_tourism) {
		usedKeyValues.push_back(convertKeyToInt(tourism));
	}

	for( const auto & barrier : m_barriers) {
		usedKeyValues.push_back(convertKeyToInt(barrier));
	}

	std::unordered_set<int> s;
	for (int i : usedKeyValues)
		s.insert(i);
	usedKeyValues.assign( s.begin(), s.end() );
	sort( usedKeyValues.begin(), usedKeyValues.end() );
	int lastElement = static_cast<int>(NUM_KV);
	if (!usedKeyValues.empty() && usedKeyValues.back() == lastElement) {
		usedKeyValues.pop_back();
		usedKeyValues.insert(usedKeyValues.begin(), lastElement);
	}
	usedKeyValues.insert(usedKeyValues.begin(), (static_cast<int>(BOUNDINGBOX))); // boundingbox always included

	int i = 0;
	for (; i < usedKeyValues.size(); i++) {
		if (usedKeyValues[i] == static_cast<int>(BOUNDINGBOX)) break;
	}
	m_boundingBox.m_zPosition = (i / (double)(usedKeyValues.size() - 1));

	std::function<void(AbstractOSMObject&)> assignZValue = [&](AbstractOSMObject& object){
		int keyValue = convertKeyToInt(object);
		int i = 0;
		for (; i < usedKeyValues.size(); i++) {
			if (usedKeyValues[i] == keyValue) break;
		}
		object.m_zPosition = (i / (double)(usedKeyValues.size() - 1));
	};

	for (auto & building : m_buildings) {
		assignZValue(building);
	}

	for( auto & highway : m_highways) {
		assignZValue(highway);
	}

	for( auto & water : m_waters) {
		assignZValue(water);
	}

	for( auto & land : m_land) {
		assignZValue(land);
	}

	for( auto & leisure : m_leisure) {
		assignZValue(leisure);
	}

	for( auto & natural : m_natural) {
		assignZValue(natural);
	}

	for( auto & amenity : m_amenities) {
		assignZValue(amenity);
	}

	for( auto & place : m_places) {
		assignZValue(place);
	}

	for( auto & bridge : m_bridges) {
		assignZValue(bridge);
	}

	for( auto & tourism : m_tourism) {
		assignZValue(tourism);
	}

	for( auto & barrier : m_barriers) {
		assignZValue(barrier);
	}
}

void DrawingOSM::updatePlaneGeometries()
{
	for (auto& building : m_buildings) {
		for (auto& area : building.m_areas ){
			area.updatePlaneGeometry();
		}
	}
}

const void DrawingOSM::geometryData(std::map<double, std::vector<GeometryData *>>& geometryData) const
{

	m_boundingBox.addGeometryData(this, geometryData[m_boundingBox.m_zPosition]);

	for (const auto & building : m_buildings) {
		building.addGeometryData(geometryData[building.m_zPosition]);
	}

	for( const auto & highway : m_highways) {
		highway.addGeometryData(geometryData[highway.m_zPosition]);
	}

	for( const auto & water : m_waters) {
		water.addGeometryData(geometryData[water.m_zPosition]);
	}

	for( const auto & land : m_land) {
		land.addGeometryData(geometryData[land.m_zPosition]);
	}

	for( const auto & leisure : m_leisure) {
		leisure.addGeometryData(geometryData[leisure.m_zPosition]);
	}

	for( const auto & natural : m_natural) {
		natural.addGeometryData(geometryData[natural.m_zPosition]);
	}

	for( const auto & amenity : m_amenities) {
		amenity.addGeometryData(geometryData[amenity.m_zPosition]);
	}

	for( const auto & place : m_places) {
		place.addGeometryData(geometryData[place.m_zPosition]);
	}

	for( const auto & bridge : m_bridges) {
		bridge.addGeometryData(geometryData[bridge.m_zPosition]);
	}

	for( const auto & tourism : m_tourism) {
		tourism.addGeometryData(geometryData[tourism.m_zPosition]);
	}

	for( const auto & barrier : m_barriers) {
		barrier.addGeometryData(geometryData[barrier.m_zPosition]);
	}
}

const VicOSM::Node * DrawingOSM::findNodeFromId(unsigned int id) const
{
	auto it = m_nodes.find(id);
	if (it != m_nodes.end()) {
		return &it->second;
	} else {
		return nullptr;
	}
}

const VicOSM::Way * DrawingOSM::findWayFromId(unsigned int id) const
{
	auto it = m_ways.find(id);
	if (it != m_ways.end()) {
		return &it->second;
	} else {
		return nullptr;
	}
}

const VicOSM::Relation * DrawingOSM::findRelationFromId(unsigned int id) const
{
	auto it = m_relations.find(id);
	if (it != m_relations.end()) {
		return &it->second;
	} else {
		return nullptr;
	}
}

IBKMK::Vector2D DrawingOSM::convertLatLonToVector2D(double lat, double lon) const
{
	double x, y;
	IBKMK::LatLonToUTMXY(lat, lon, m_utmZone, x, y);
	return IBKMK::Vector2D(x, y) - m_centerMercatorProjection;
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


const void DrawingOSM::Area::addGeometryData(std::vector<VICUS::DrawingOSM::GeometryData*>& data) const
{
	FUNCID(DrawingOSM::Area::addGeometryData);
	try {
		if (m_dirtyTriangulation) {
			GeometryData geometryData;
			m_geometryData.clear();

			if (m_extrudingPolygon) {
				geometryData.m_extrudingPolygon = true;
				if (!m_multiPolygon.m_outerPolyline.empty()) {
					geometryData.m_multipolygons.push_back(m_multiPolygon);
					geometryData.m_color = m_color;
					geometryData.m_height = m_height;
					geometryData.m_minHeight = m_minHeight;
				}
			} else {
				std::vector<IBKMK::Vector3D> areaPoints;

				for (int i = 1; i < m_multiPolygon.m_outerPolyline.size(); i++) {
					IBKMK::Vector3D p = IBKMK::Vector3D(m_multiPolygon.m_outerPolyline[i].m_x,
														m_multiPolygon.m_outerPolyline[i].m_y,
														0);

					QVector3D vec = m_drawing->m_rotationMatrix.toQuaternion() * IBKVector2QVector(p);
					vec += IBKVector2QVector(m_drawing->m_origin);

					areaPoints.push_back(QVector2IBKVector(vec));
				}

				VICUS::Polygon3D polygon3D(areaPoints);
				// Initialize PlaneGeometry with the polygon
				geometryData.m_planeGeometry.push_back(VICUS::PlaneGeometry(polygon3D));

				if(!m_multiPolygon.m_innerPolylines.empty()) {
					std::vector<PlaneGeometry::Hole> holes;
					for(int j = 0; j < m_multiPolygon.m_innerPolylines.size(); j++) {
						VICUS::Polygon2D polygon2d(m_multiPolygon.m_innerPolylines[j]);
						holes.push_back(PlaneGeometry::Hole(j, polygon2d, false));
					}

					VICUS::PlaneGeometry& planeGeometry = geometryData.m_planeGeometry.back();
					planeGeometry.setHoles(holes);
				}

				geometryData.m_color = m_color;
			}
			m_geometryData.push_back(geometryData);
			m_dirtyTriangulation = false;
		}
		for(auto& geometryData : m_geometryData) {
			data.push_back(&geometryData);
		}
	}
	catch (IBK::Exception &ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error generating plane geometries for 'DrawingOSM::Area' element.\n%1").arg(ex.what()), FUNC_ID);
	}
}

void DrawingOSM::Building::calculateHeight(VicOSM::AbstractOSMElement & element)
{
	std::string valueLevel = element.getValueFromKey("building:levels");
	if (valueLevel != "") {
		double valueLevelDouble = std::stoi(valueLevel);
		if (valueLevelDouble > 0) m_height = valueLevelDouble * m_levelHeight;
	}

	std::string valueRoof = element.getValueFromKey("roof:levels");
	if (valueRoof != "") {
		double valueRoofDouble = std::stoi(valueRoof);
		if (valueRoofDouble > 0) m_height += valueRoofDouble * m_roofHeight;
	}

	std::string valueHeight = element.getValueFromKey("height");
	if (valueHeight != "") {
		double valueHeightDouble = std::stoi(valueHeight);
		m_height = valueHeightDouble;
	}

	std::string valueMinLevel = element.getValueFromKey("building:min_level");
	if (valueMinLevel != "") {
		double valueMinLevelDouble = std::stoi(valueMinLevel);
		if (valueMinLevelDouble > 0) m_minHeight = valueMinLevelDouble * m_levelHeight;
	}

	std::string valueMinHeight = element.getValueFromKey("min_height");
	if (valueMinHeight != "") {
		double valueMinHeightDouble = std::stoi(valueMinHeight);
		m_minHeight = valueMinHeightDouble;
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
													0);
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

			m_dirtyTriangulation = false;
		}
		for (auto& geometryData : m_geometryData) {
			data.push_back(&geometryData);
		}
	}
	catch (IBK::Exception &ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error generating plane geometries for 'DrawingOSM::LineFromPlanes' element.\n%1").arg(ex.what()), FUNC_ID);
	}
}

QColor DrawingOSM::Land::setColor()
{
	QColor color("#c8facc");

	if (m_value == "residential"){
		color = QColor("#f2dad9");
	} else if (m_value == "forest") {
		color = QColor("#add19e");
	} else if (m_value == "industrial") {
		color = QColor("#ebdbe8");
	} else if (m_value == "orchard") {
		color = QColor("#aedfa3");
	} else if (m_value == "village_green") {
		color = QColor("#cdebb0");
	} else if (m_value == "construction") {
		color = QColor("#c7c7b4");
	} else if (m_value == "grass") {
		color = QColor("#cdebb0");
	} else if (m_value == "retail") {
		color = QColor("#ffd6d1");
	} else if (m_value == "cemetery") {
		color = QColor("#aacbaf");
	} else if (m_value == "commercial") {
		color = QColor("#f2dad9");
	} else if (m_value == "public_administration") {
		color = QColor("#f2efe9");
	} else if (m_value == "railway") {
		color = QColor("#ebdbe8");
	} else if (m_value == "farmyard") {
		color = QColor("#f5dcba");
	} else if (m_value == "meadow") {
		color = QColor("#cdebb0");
	} else if (m_value == "religious") {
		color = QColor("#d0d0d0");
	} else if (m_value == "flowerbed") {
		color = QColor("#cdebb0");
	} else if (m_value == "recreation_ground") {
		color = QColor("#dffce2");
	} else if (m_value == "brownfield") {
		color = QColor("#c7c7b4");
	}

	return color;
}



const void DrawingOSM::AbstractOSMObject::addGeometryData(std::vector<GeometryData *> & data) const
{
	for (auto& area : m_areas) {
		area.addGeometryData(data);
	}
	for (auto& lineFromPlanes : m_linesFromPlanes) {
		lineFromPlanes.addGeometryData(data);
	}
	for (auto& circle : m_circles) {
		circle.addGeometryData(data);
	}
}

bool DrawingOSM::AbstractOSMObject::initialize(VicOSM::AbstractOSMElement & osmElement) {
	if (osmElement.containsKeyValue("location", "underground")) return false;
	if (osmElement.containsKeyValue("location", "underwater")) return false;
	m_value = osmElement.getValueFromKey(m_key);
	std::string layer = osmElement.getValueFromKey("layer");
	assignKeyValue();
	if (layer != "") m_layer = std::stoi(layer);
	return true;
}

void DrawingOSM::AbstractOSMObject::assignKeyValue()
{
	if (m_key == "building") {
		m_keyValue = BUILDING;
	} else if (m_key == "highway") {
		if (m_value == "footway") {
			m_keyValue = HIGHWAY_FOOTWAY;
		} else if (m_value == "steps") {
			m_keyValue = HIGHWAY_STEPS;
		} else if (m_value == "path") {
			m_keyValue = HIGHWAY_PATH;
		}else if (m_value == "service") {
			m_keyValue = HIGHWAY_SERVICE;
		} else if (m_value == "motorway") {
			m_keyValue = HIGHWAY_MOTORWAY;
		}else if (m_value == "primary") {
			m_keyValue = HIGHWAY_PRIMARY;
		}else if (m_value == "secondary") {
			m_keyValue = HIGHWAY_SECONDARY;
		}else if (m_value == "residential") {
			m_keyValue = HIGHWAY_RESIDENTIAL;
		}else if (m_value == "trunk") {
			m_keyValue = HIGHWAY_TRUNK;
		}else if (m_value == "pedestrian") {
			m_keyValue = HIGHWAY_PEDESTRIAN;
		}else {
			m_keyValue = HIGHWAY;
		}
	} else if (m_key == "landuse") {
		if (m_value == "village_green") {
			m_keyValue = LANDUSE_VILLAGE_GREEN;
		} else if (m_value == "grass") {
			m_keyValue = LANDUSE_GRASS;
		} else if (m_value == "brownfield") {
			m_keyValue = LANDUSE_BROWNFIELD;
		} else if (m_value == "forest") {
			m_keyValue = LANDUSE_FOREST;
		} else if (m_value == "farmyard") {
			m_keyValue = LANDUSE_FARMYARD;
		} else if (m_value == "construction") {
			m_keyValue = LANDUSE_CONSTRUCTION;
		} else if (m_value == "industrial") {
			m_keyValue = LANDUSE_INDUSTRIAL;
		} else if (m_value == "orchard") {
			m_keyValue = LANDUSE_ORCHARD;
		} else if (m_value == "retail") {
			m_keyValue = LANDUSE_RETAIL;
		} else if (m_value == "commercial") {
			m_keyValue = LANDUSE_COMMERCIAL;
		} else if (m_value == "residential") {
			m_keyValue = LANDUSE_RESIDENTIAL;
		} else if (m_value == "railway") {
			m_keyValue = LANDUSE_RAILWAY;
		} else if (m_value == "religious") {
			m_keyValue = LANDUSE_RELIGIOUS;
		} else if (m_value == "recreation_ground") {
			m_keyValue = LANDUSE_RECREATION_GROUND;
		} else if (m_value == "cemetery") {
			m_keyValue = LANDUSE_CEMETERY;
		} else if (m_value == "meadow") {
			m_keyValue = LANDUSE_MEADOW;
		} else if (m_value == "flowerbed") {
			m_keyValue = LANDUSE_FLOWERBED;
		} else {
			m_keyValue = LANDUSE;
		}
	} else if (m_key == "leisure") {
		if (m_value == "park") {
			m_keyValue = LEISURE_PARK;
		} else {
			m_keyValue = LEISURE;
		}
	} else if (m_key == "natural") {
		if (m_value == "tree_row") {
			m_keyValue = NATURAL_TREE_ROW;
		} else if (m_value == "water") {
			m_keyValue = NATURAL_WATER;
		} else if (m_value == "tree") {
			m_keyValue = NATURAL_TREE;
		} else {
			m_keyValue = NATURAL;
		}
	} else if (m_key == "place") {
		m_keyValue = PLACE;
	} else if (m_key == "heritage") {
		m_keyValue = HERITAGE;
	} else if (m_key == "amenity") {
		if (m_value == "kindergarten") {
			m_keyValue = AMENITY_KINDERGARTEN;
		} else if (m_value == "school") {
			m_keyValue = AMENITY_SCHOOL;
		} else if (m_value == "social_facility") {
			m_keyValue = AMENITY_SOCIAL_FACILITY;
		} else {
			m_keyValue = AMENITY;
		}
	} else if (m_key == "waterway") {
		m_keyValue = WATERWAY;
	} else if (m_key == "water") {
		m_keyValue = WATER;
	} else if (m_key == "bridge") {
		m_keyValue = BRIDGE;
	} else if (m_key == "tourism") {
		m_keyValue = TOURISM;
	} else if (m_key == "barrier") {
		m_keyValue = BARRIER;
	}else {
		m_keyValue = NUM_KV;
	}
}

const void DrawingOSM::Circle::addGeometryData(std::vector<GeometryData *> & data) const
{
	FUNCID(DrawingOSM::Circle::addGeometryData);
	try {
		if (m_dirtyTriangulation) {
			std::vector<IBKMK::Vector3D> circlePoints;

			const double TWO_PI = 2 * M_PI;
			double angleStep = TWO_PI / SEGMENT_COUNT_ELLIPSE;

			circlePoints.resize(SEGMENT_COUNT_ELLIPSE);

			for (int i = 0; i < SEGMENT_COUNT_ELLIPSE; ++i) {
				double currentAngle = i * angleStep;
				double x = m_radius * 0.5 * cos(currentAngle);
				double y = m_radius * 0.5 * sin(currentAngle);

				IBKMK::Vector3D p = IBKMK::Vector3D(x + m_center.m_x,
													y + m_center.m_y,
													0);

				QVector3D vec = m_drawing->m_rotationMatrix.toQuaternion() * IBKVector2QVector(p);
				vec += IBKVector2QVector(m_drawing->m_origin);
				circlePoints[i] = QVector2IBKVector(vec);
			}
\
			std::vector<PlaneGeometry> planeGeometry;
			if (m_drawing->generatePlanesFromPolyline(circlePoints, true,
															   m_radius,
													  planeGeometry)) {
				GeometryData geometryData;
				geometryData.m_planeGeometry = planeGeometry;
				geometryData.m_color = m_color;
				m_geometryData.push_back(geometryData);
			}

			m_dirtyTriangulation = false;
		}
		for (auto& geometryData : m_geometryData) {
			data.push_back(&geometryData);
		}
	}
	catch (IBK::Exception &ex) {
		throw IBK::Exception( ex, IBK::FormatString("Error generating plane geometries for 'DrawingOSM::Circle' element.\n%1").arg(ex.what()), FUNC_ID);
	}
}

const void DrawingOSM::BoundingBox::addGeometryData(const DrawingOSM* drawing, std::vector<GeometryData *> & data) const
{
	std::vector<IBKMK::Vector3D> polyline;
	std::vector<IBKMK::Vector3D> areaPoints;
	polyline.push_back(IBKMK::Vector3D(drawing->convertLatLonToVector2D(drawing->m_boundingBox.maxlat, drawing->m_boundingBox.minlon)));
	polyline.push_back(IBKMK::Vector3D(drawing->convertLatLonToVector2D(drawing->m_boundingBox.minlat, drawing->m_boundingBox.minlon)));
	polyline.push_back(IBKMK::Vector3D(drawing->convertLatLonToVector2D(drawing->m_boundingBox.minlat, drawing->m_boundingBox.maxlon)));
	polyline.push_back(IBKMK::Vector3D(drawing->convertLatLonToVector2D(drawing->m_boundingBox.maxlat, drawing->m_boundingBox.maxlon)));

	for (auto &p : polyline) {
		QVector3D vec = drawing->m_rotationMatrix.toQuaternion() * QVector3D((float)p.m_x, (float)p.m_y, (float)p.m_z);
		vec += QVector3D((double)drawing->m_origin.m_x, (double)drawing->m_origin.m_y, (double)drawing->m_origin.m_z);

		areaPoints.push_back(IBKMK::Vector3D((double)vec.x(), (double)vec.y(), (double)vec.z()));
	}

	m_geometryData.m_color = QColor("#f2efe9");
	m_geometryData.m_planeGeometry.push_back(VICUS::PlaneGeometry(areaPoints));
	data.push_back(&m_geometryData);
}

} // namespace VICUS
