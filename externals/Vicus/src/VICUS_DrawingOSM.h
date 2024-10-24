#ifndef VICUS_DRAWINGOSM_H
#define VICUS_DRAWINGOSM_H

#include "VICUS_Constants.h"
#include "tinyxml.h"

#include "IBK_NotificationHandler.h"
#include <IBKMK_Vector2D.h>
#include <VICUS_Object.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "VICUS_PlaneGeometry.h"
#include "VICUS_RotationMatrix.h"
#include "VICUS_Drawing.h"

#include "VicOSM_AbstractOSMElement.h"
#include "VicOSM_Amenity.h"
#include "VicOSM_Barrier.h"
#include "VicOSM_BoundingBox.h"
#include "VicOSM_Bridge.h"
#include "VicOSM_Building.h"
#include "VicOSM_Highway.h"
#include "VicOSM_Land.h"
#include "VicOSM_Leisure.h"
#include "VicOSM_Natural.h"
#include "VicOSM_Place.h"
#include "VicOSM_Tourism.h"
#include "VicOSM_Water.h"
#include "VicOSM_Railway.h"

#include "VicOSM_AbstractOSMElement.h"
#include "VicOSM_Node.h"
#include "VicOSM_Relation.h"
#include "VicOSM_Way.h"

#include "VicOSM_AbstractDrawingObject.h"
#include "VicOSM_Area.h"
#include "VicOSM_LineFromPlanes.h"
#include "VicOSM_Circle.h"

#include <IBKMK_Vector2D.h>
#include <IBKMK_UTM.h>

#include <QQuaternion>
#include <QMatrix4x4>
#include <QColor>

using namespace VicOSM;

namespace IBK {
class NotificationHandler;
}

namespace VICUS {

/*!
 *  DrawingOSM class. Reads an OSM file. Generates all osm AbstractOSMElements from it (nodes, ways, relations). Then constructs all AbstractOSMObject (buildings, highways etc.) from osm elements  and holds these objects.
 *  Objects can be saved to xml. An object can hold AbstractDrawingGeometry (circles, areas and lineFromPlanes). These geomentries will be saved as 2d polylines ( or a 2D vector in the case of the circle) with additional information like radius etc.
 *  The objects, elements and geometryobjects are defined in the library VicOSM.
 *  TriangulationData and PlaneGeometry of a DrawingObject is held in m_geometryData in this class, outside of OSMObjects
 */
class DrawingOSM : public Object {

public:

	/*! Type-info string. */
	const char * typeinfo() const override {
		return "DrawingOSM";
	}

	/*! Groups together planeGeometry with data like color, height etc. PlaneGeometry will
	 *  be held in this struct. This struct is held in m_geometryData in VICUS::DrawingOSM */
	struct GeometryData {
		std::vector<VICUS::PlaneGeometry>	m_planeGeometry;
		std::vector<Multipolygon>			m_multipolygons;
		QColor								m_color;
		bool								m_extrudingPolygon = false;
		double								m_height = 3;
		double_t							m_minHeight = 0;
	};

	std::vector<IBKMK::Vector2D> convertHoleToLocalCoordinates(const std::vector<IBKMK::Vector3D> & globalVertices, const IBKMK::Vector3D & offset, const IBKMK::Vector3D & localX, const IBKMK::Vector3D & localY) const;

	// *** Methods and Helper Functions To Create Polygons ***
	void createMultipolygonFromWay(const Way &way, Multipolygon &multipolygon);

	/*! Struct only used in createMultipolygon, ringAssignment, ringGrouping */
	struct WayWithMarks {
		std::vector<int> refs;
		bool assigned = false;
		bool selected = false;
		bool reversedOrder = false;
	};

	/*! Used in createMultipolygonsFromRelation. Small helper function to
		convert a way to a polyline std::vector<IBKMK::Vector2D */
	std::vector<IBKMK::Vector2D> convertVectorWayWithMarksToVector2D(const std::vector<WayWithMarks*>& ways);

	/*! Used in createMultipolygonsFromRelation. Creates complete areas/rings
		from a set of open and closed polylines */
	void ringAssignment(std::vector<WayWithMarks>& ways, std::vector<std::vector<WayWithMarks*>>& allRings);

	/*! Used in createMultipolygonsFromRelation. Creates multiple polygons
		with holes from a set of closed polylines */
	void ringGrouping(std::vector<std::vector<WayWithMarks*>>& rings, std::vector<Multipolygon>& multipolygons);

	/*! takes a relation as an input and tries to create (many) Multipolygons with holes */
	void createMultipolygonsFromRelation(const Relation &relation, std::vector<Multipolygon>& multipolygons);

	// *** PUBLIC MEMBER FUNCTIONS ***

	void readXML(const TiXmlElement * element);
	TiXmlElement * writeXML(TiXmlElement * parent) const;

	/*! Fills m_nodes, m_ways, m_relations, m_boundingBox with values from a OSM XML */
	void readOSM(const TiXmlElement * element, IBK::NotificationHandler *notifyer = nullptr);

	/*! writes .vicosm to filename */
	void writeOSM(const IBK::Path & filename);

	/*! calls readOSM. Afterwards calculates m_utmZone and m_origin */
	bool import(const QString filePath, IBK::NotificationHandler *notifyer = nullptr);

	/*! Updates all planes, when transformation operations are applied.
		MIND: Always call this function, when the drawing transformation
		(translation, rotation) were changed, since the triangulation is
		redone.
	*/
	void updatePlaneGeometries();

	/*! creates all PlaneGeometry objects from one OSMObject by iterating over all DrawingObjects int the OSMObject and creates a GeometryData object from it.
	 *  Saves the resulting GeometryData object in a map with the address of the DrawingObject as key. Inserts the created GeometryData object to the geometryData Vector */
	void addGeometryData(const AbstractOSMObject& object, std::vector<GeometryData *>& geometryData) const;

	/*! Iterates over all OSMObjects and adds geometryData to the geometryData map. The map takes as a key the z-value of an object to define the order of the objects. */
	void geometryData(std::map<double, std::vector<VICUS::DrawingOSM::GeometryData*>>& geometryData) const;

	/*! Searches in m_nodes for node with id. If no node was found, a nullptr is returned */
	const Node* findNodeFromId(unsigned int id) const;
	/*! Searches in m_ways for way with id. If no way was found, a nullptr is returned */
	const Way* findWayFromId(unsigned int id) const;
	/*! Searches in m_relations for relation with id. If no relation was found, a nullptr is returned */
	const Relation* findRelationFromId(unsigned int id) const;
	/*! converts latitude, longitude to UTM mercator projection coordinates. Uses the UTM zone defined by the bounding box */
	inline IBKMK::Vector2D convertLatLonToVector2D(double lat, double lon) const;

	// *** Methods to create Buildings streets. etc. ***
	/*! Creates all OSMObjects (buildings, highways, landuse) from OSMElements */
	void constructObjects(IBK::NotificationHandler *notifyer = nullptr);

	// *** List of OSM XML Elements ***
	/*! list of nodes */
	std::unordered_map<unsigned int, Node>			m_nodes;
	/*! list of ways */
	std::unordered_map<unsigned int, Way>			m_ways;
	/*! lists of relations */
	std::unordered_map<unsigned int, Relation>		m_relations;
	/*! Stores the bounding box of the drawing */
	BoundingBox										m_boundingBox;		// XML:E


	/*! UTM zone defined by the longitude (minlon) of the bounding box */
	int												m_utmZone = 0;		// XML:A
	double											m_centerX = 0;		// XML:A
	double											m_centerY = 0;		// XML:A

	/*! point of origin */
	IBKMK::Vector3D									m_origin			= IBKMK::Vector3D(0,0,0);
	/*! rotation matrix */
	RotationMatrix									m_rotationMatrix	= RotationMatrix(QQuaternion(1.0,0.0,0.0,0.0));

	bool											m_enable3DBuildings			= true;	// XML:A

	// *** List of OSM Objects like buildings, streets with all relevant information ***
	std::vector<OSMBuilding>						m_buildings;		// XML:E
	std::vector<Highway>							m_highways;			// XML:E
	std::vector<Water>								m_waters;			// XML:E
	std::vector<Land>								m_land;				// XML:E
	std::vector<Leisure>							m_leisure;			// XML:E
	std::vector<Natural>							m_natural;			// XML:E
	std::vector<Amenity>							m_amenities;		// XML:E
	std::vector<Place>								m_places;			// XML:E
	std::vector<Bridge>								m_bridges;			// XML:E
	std::vector<Tourism>							m_tourism;			// XML:E
	std::vector<Barrier>							m_barriers;			// XML:E
	std::vector<Railway>							m_railways;			// XML:E

	/*! Function to generate plane geometries from a polyline. */
	bool generatePlanesFromPolyline(const std::vector<IBKMK::Vector3D> & polyline,
									bool connectEndStart, double width, std::vector<PlaneGeometry> &planes) const;

	/*! Flags and Objects used for getting geometryData and rendering. Can be set externally */
	mutable std::map<const AbstractDrawingObject*, GeometryData>	m_geometryData;
	mutable GeometryData											m_geometryDataBoundingBox;
	mutable bool													m_dirtyTriangulation = true;
	mutable bool													m_firstTriangulation = true;

};

} // namespace VICUS



#endif // VICUS_DRAWINGOSM_H
