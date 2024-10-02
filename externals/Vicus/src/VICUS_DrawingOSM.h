#ifndef VICUS_DRAWINGOSM_H
#define VICUS_DRAWINGOSM_H

#include "VICUS_Constants.h"
#include "tinyxml.h"

#include <IBKMK_Vector2D.h>
#include <VICUS_Object.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "VICUS_PlaneGeometry.h"
#include "VICUS_RotationMatrix.h"
#include "VICUS_Drawing.h"

#include <IBKMK_Vector2D.h>
#include <IBKMK_UTM.h>

#include <QQuaternion>
#include <QMatrix4x4>
#include <QColor>

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

	enum Types{
		NodeType,
		WayType,
		RelationType
	};

	struct Tag{
		std::string key;
		std::string value;

		void readXML(const TiXmlElement * element);
	};

	struct Member{
		Types type;
		int ref;
		std::string role;

		void readXML(const TiXmlElement * element);
	};

	struct Nd{
		int ref;

		void readXML(const TiXmlElement * element);
	};

	/* Abstract class for all OSM XML elements */
	struct AbstractOSMElement {

		virtual ~AbstractOSMElement() {}

		void readXML(const TiXmlElement * element);

		bool containsKey(const std::string& key) const;

		bool containsValue(const std::string& value) const;

		bool containsKeyValue(const std::string& key, const std::string& value) const;

		std::string getValueFromKey(const std::string& key) const;

		unsigned int                    m_id = VICUS::INVALID_ID; // unique id

		std::vector<Tag>				m_tags; // stores all tags. Does not make an effort to interpret them

		bool                            m_visible = true; // visibility flag
	};

	/*! A single point on the map */
	struct Node : public AbstractOSMElement {

		void readXML(const TiXmlElement * element);

		/*! Point coordinate */
		double                          m_lon;
		double                          m_lat;
	};

	/*! List of Nodes that make up a way. A way describes a polyline */
	struct Way : public AbstractOSMElement {

		void readXML(const TiXmlElement * element);

		std::vector<Nd>				m_nd;
	};

	/*! Stores both LW and normal polyline */
	struct Relation : public AbstractOSMElement {

		void readXML(const TiXmlElement * element);

		std::vector<Member>				m_members;
	};

	struct Multipolygon {
		std::vector<IBKMK::Vector2D> m_outerPolyline;
		std::vector<std::vector<IBKMK::Vector2D>> m_innerPolylines;
	};

	struct GeometryData {
		std::vector<VICUS::PlaneGeometry>	m_planeGeometry;
		std::vector<Multipolygon>			m_multipolygons;
		QColor								m_color;
		bool								m_extrudingPolygon = false;
		double								m_height = 3;
		double_t							m_minHeight = 0;
	};


	struct BoundingBox {
		double minlat;
		double maxlat;
		double minlon;
		double maxlon;

		double								m_zPosition = 0;

		mutable GeometryData				m_geometryData;
		const void addGeometryData(const DrawingOSM* drawing, std::vector<VICUS::DrawingOSM::GeometryData*> &data) const;
	};


	struct AbstractDrawingObject {

		AbstractDrawingObject(const DrawingOSM * drawing)
			: m_drawing(drawing)
		{}

		const virtual void addGeometryData(std::vector<VICUS::DrawingOSM::GeometryData*> &data) const = 0;
		void updatePlaneGeometry() {
			m_dirtyTriangulation = true;
		}

	protected:
		/*! Flag to indictate recalculation of points. */
		mutable bool								m_dirtyPoints = true;
		/*! Flag to indictate recalculation triangulation. */
		mutable bool								m_dirtyTriangulation = true;
		/*! Points of objects. */
		mutable std::vector<IBKMK::Vector2D>		m_pickPoints;
		/*! Plane Geometries with all triangulated data.
		*/
		mutable std::vector<GeometryData>			m_geometryData;
		/*! Pointer to DrawingOSM object this AbstractDrawingObject belongs to */
		const DrawingOSM * m_drawing = nullptr;
	};

	struct Area : AbstractDrawingObject {

		Area(const DrawingOSM * drawing)
			: AbstractDrawingObject(drawing)
		{}

		Multipolygon						m_multiPolygon;
		bool								m_extrudingPolygon = false;
		double								m_height = 3;
		double								m_minHeight = 0;

		QColor								m_color	  = QColor("#2f302f");

		const void addGeometryData(std::vector<VICUS::DrawingOSM::GeometryData*> &data) const override;
	};

	struct LineFromPlanes : AbstractDrawingObject {

		LineFromPlanes(const DrawingOSM * drawing)
			: AbstractDrawingObject(drawing)
		{}

		/*! polyline coordinates */
		std::vector<IBKMK::Vector2D>		m_polyline;

		double								m_lineThickness = 1;

		QColor								m_color = QColor("#78909c");

		const void addGeometryData(std::vector<VICUS::DrawingOSM::GeometryData*> &data) const override;
	};

	struct Circle : AbstractDrawingObject {

		Circle(const DrawingOSM * drawing)
			: AbstractDrawingObject(drawing)
		{}

		/*! polyline coordinates */
		IBKMK::Vector2D						m_center;

		double								m_radius = 1;

		QColor								m_color = QColor("#b8d4a7");

		const void addGeometryData(std::vector<VICUS::DrawingOSM::GeometryData*> &data) const override;
	};

	/*! Provides enum for key value pairs. Also defines the order in which objects are drawn when overlapping */
	enum KeyValue{
		BOUNDINGBOX,
		LAYERLANDUSENEG5,
		LAYERLANDUSENEG4,
		LAYERLANDUSENEG3,
		LAYERLANDUSENEG2,
		LAYERLANDUSENEG1,
		PLACE,
		HERITAGE,
		LANDUSE,
		LANDUSE_BROWNFIELD,
		LEISURE_PARK,
		LANDUSE_FOREST,
		LANDUSE_ORCHARD,
		LANDUSE_FARMYARD,
		LANDUSE_CONSTRUCTION,
		LANDUSE_INDUSTRIAL,
		LANDUSE_RETAIL,
		LANDUSE_COMMERCIAL,
		LANDUSE_RESIDENTIAL,
		LANDUSE_RAILWAY,
		LANDUSE_PUBLIC_ADMINISTRATION,
		LANDUSE_RELIGIOUS,
		LANDUSE_RECREATION_GROUND,
		TOURISM,
		LEISURE,
		LANDUSE_CEMETERY,
		LANDUSE_VILLAGE_GREEN,
		LANDUSE_GRASS,
		NATURAL,
		NATURAL_TREE_ROW,
		AMENITY,
		AMENITY_KINDERGARTEN,
		AMENITY_SCHOOL,
		AMENITY_SOCIAL_FACILITY,
		LANDUSE_MEADOW,
		LANDUSE_FLOWERBED,
		WATERWAY,
		WATER,
		NATURAL_WATER,
		LAYERLANDUSE1,
		LAYERLANDUSE2,
		LAYERLANDUSE3,
		LAYERLANDUSE4,
		LAYERLANDUSE5,
		NATURAL_TREE,
		LAYERHIGHWAYNEG5,
		LAYERHIGHWAYNEG4,
		LAYERHIGHWAYNEG3,
		LAYERHIGHWAYNEG2,
		LAYERHIGHWAYNEG1,
		BARRIER,
		BRIDGE,
		HIGHWAY_MOTORWAY,
		HIGHWAY_PEDESTRIAN,
		HIGHWAY_SERVICE,
		HIGHWAY_RESIDENTIAL,
		HIGHWAY, //TERTIARY
		HIGHWAY_SECONDARY,
		HIGHWAY_PRIMARY,
		HIGHWAY_TRUNK,
		HIGHWAY_FOOTWAY,
		HIGHWAY_STEPS,
		HIGHWAY_PATH,
		BUILDING,
		LAYERHIGHWAY1,
		LAYERHIGHWAY2,
		LAYERHIGHWAY3,
		LAYERHIGHWAY4,
		LAYERHIGHWAY5,
		NUM_KV
	};


	struct AbstractOSMObject {
		const virtual void addGeometryData(std::vector<VICUS::DrawingOSM::GeometryData*> &data) const;

		bool initialize(AbstractOSMElement& osmElement);

		void assignKeyValue();

		std::vector<Area>					m_areas;
		std::vector<LineFromPlanes>			m_linesFromPlanes;
		std::vector<Circle>					m_circles;


		std::string							m_key = "";

		std::string							m_value = "";

		KeyValue							m_keyValue = NUM_KV;

		double								m_zPosition = 0;

		int									m_layer = 0;
	};

	// https://wiki.openstreetmap.org/wiki/Simple_3D_Buildings#How_to_map
	/*! Building Object. Contains only 2D information. */
	struct Building : AbstractOSMObject {

		void								calculateHeight(AbstractOSMElement& element);

		double								m_height = 3;

		double								m_minHeight = 0;

		double								m_levelHeight = 3;

		double								m_roofHeight = 3;
	};

	struct Highway : AbstractOSMObject {};

	struct Water : AbstractOSMObject {};

	struct Land : AbstractOSMObject {
		QColor	setColor();
	};

	struct Leisure : AbstractOSMObject {};

	struct Natural : AbstractOSMObject {};

	struct Amenity : AbstractOSMObject {};

	struct Place : AbstractOSMObject {};

	struct Bridge : AbstractOSMObject {};

	struct Tourism : AbstractOSMObject {};

	struct Barrier : AbstractOSMObject {};

	std::vector<IBKMK::Vector2D> convertHoleToLocalCoordinates(const std::vector<IBKMK::Vector3D> & globalVertices, const IBKMK::Vector3D & offset, const IBKMK::Vector3D & localX, const IBKMK::Vector3D & localY) const;

	// *** Methods and Helper Functions To Create Polygons ***
	void createMultipolygonFromWay(Way &way, Multipolygon &multipolygon);

	struct WayWithMarks {
		std::vector<int> refs;
		bool assigned = false;
		bool selected = false;
		bool reversedOrder = false;
	};
	std::vector<IBKMK::Vector2D> convertVectorWayWithMarksToVector2D(const std::vector<WayWithMarks*>& ways);
	void ringAssignment(std::vector<WayWithMarks>& ways, std::vector<std::vector<WayWithMarks*>>& allRings);
	void ringGrouping(std::vector<std::vector<WayWithMarks*>>& rings, std::vector<Multipolygon>& multipolygons);
	void createMultipolygonsFromRelation(Relation &relation, std::vector<Multipolygon>& multipolygons);

	// *** PUBLIC MEMBER FUNCTIONS ***

	/*! Fills m_nodes, m_ways, m_relations, m_boundingBox with values from a OSM XML */
	void readXML(const TiXmlElement * element);

	/*! calls readXML. Afterwards calculates m_utmZone and m_origin */
	bool readOSMFile(QString filePath);

	/*! Updates all planes, when transformation operations are applied.
		MIND: Always call this function, when the drawing transformation
		(translation, rotation) were changed, since the triangulation is
		redone.
	*/
	void updatePlaneGeometries();
	const void geometryData(std::map<double, std::vector<VICUS::DrawingOSM::GeometryData*>>& geometryData) const;


	const Node* findNodeFromId(unsigned int id) const;
	const Way* findWayFromId(unsigned int id) const;
	const Relation* findRelationFromId(unsigned int id) const;
	inline IBKMK::Vector2D convertLatLonToVector2D(double lat, double lon) const;

	// *** Methods to create Buildings streets. etc. ***
	void constructObjects();

	// creates complete buildings from ways relations etc.
	void createBuilding(Way &way);
	void createBuilding(Relation &relation);

	// extracts streets from ways relations etc.
	void createHighway(Way &way);
	// should be deprecated. All highways that are areas should be some form of place, landuse etc.
	void createHighway(Relation &relation);

	// extracts water body from ways relations etc.
	void createWater(Way &way);
	void createWater(Relation &relation);

	// extracts land from ways, relations etc.
	void createLand(Way &way);
	void createLand(Relation &relation);

	// extracts leisure objects from ways, relations etc.
	void createLeisure(Way &way);

	// extracts natural objects from ways etc.
	void createNatural(Node &node);
	void createNatural(Way &way);

	// extracts amenityobjects from ways etc.
	void createAmenity(Way &way);

	// extracts place objects from ways, relations
	void createPlace(Way &way);
	void createPlace(Relation &relation);

	// extracts bridge objects from ways
	void createBridge(Way &way);

	// extracts tourism objects from ways
	void createTourism(Way &way);

	// extracts tourism objects from ways
	void createBarrier(Way &way);

	// *** PUBLIC MEMBER VARIABLES ***

	// *** List of OSM XML Elements ***
	/*! list of nodes */
	std::unordered_map<unsigned int, Node>			m_nodes;
	/*! list of ways */
	std::unordered_map<unsigned int, Way>			m_ways;
	/*! lists of relations */
	std::unordered_map<unsigned int, Relation>		m_relations;
	/*! Stores the bounding box of the drawing */
	BoundingBox										m_boundingBox;


	/*! UTM zone defined by the longitude (minlon) of the bounding box */
	int												m_utmZone = 0;
	/*! Conversion of minlat, minlon of bounding box in the Universal Transverse Mercator projection. */
	IBKMK::Vector2D									m_centerMercatorProjection;


	/*! point of origin */
	IBKMK::Vector3D									m_origin			= IBKMK::Vector3D(0,0,0);
	/*! rotation matrix */
	RotationMatrix									m_rotationMatrix	= RotationMatrix(QQuaternion(1.0,0.0,0.0,0.0));
	/*! scale factor */
	double											m_scalingFactor		= 1.0;

	bool											m_enable3D			= true;

	// *** List of OSM Objects like buildings, streets with all relevant information ***
	std::vector<Building>							m_buildings;
	std::vector<Highway>							m_highways;
	std::vector<Water>								m_waters;
	std::vector<Land>								m_land;
	std::vector<Leisure>							m_leisure;
	std::vector<Natural>							m_natural;
	std::vector<Amenity>							m_amenities;
	std::vector<Place>								m_places;
	std::vector<Bridge>								m_bridges;
	std::vector<Tourism>							m_tourism;
	std::vector<Barrier>							m_barriers;


	/*! path of the OSM File */
	QString											m_filePath;

	/*! Function to generate plane geometries from a polyline. */
	bool generatePlanesFromPolyline(const std::vector<IBKMK::Vector3D> & polyline,
									bool connectEndStart, double width, std::vector<PlaneGeometry> &planes) const;

	/*! Flag to indictate recalculation triangulation. */
	mutable bool								m_dirtyTriangulation = true;

};

} // namespace VICUS



#endif // VICUS_DRAWINGOSM_H
