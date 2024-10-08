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

	void readXML(const TiXmlElement * element);
	TiXmlElement * writeXML(TiXmlElement * parent) const;

	/*! Fills m_nodes, m_ways, m_relations, m_boundingBox with values from a OSM XML */
	void readOSM(const TiXmlElement * element);
	void writeOSM(const IBK::Path & filename);

	/*! calls readXML. Afterwards calculates m_utmZone and m_origin */
	bool readOSMFile(QString filePath);

	/*! Updates all planes, when transformation operations are applied.
		MIND: Always call this function, when the drawing transformation
		(translation, rotation) were changed, since the triangulation is
		redone.
	*/
	void updatePlaneGeometries();
	void addGeometryData(const AbstractOSMObject& object, std::vector<GeometryData *>& geometryData) const;
	const void geometryData(std::map<double, std::vector<VICUS::DrawingOSM::GeometryData*>>& geometryData) const;


	const Node* findNodeFromId(unsigned int id) const;
	const Way* findWayFromId(unsigned int id) const;
	const Relation* findRelationFromId(unsigned int id) const;
	inline IBKMK::Vector2D convertLatLonToVector2D(double lat, double lon) const;

	// *** Methods to create Buildings streets. etc. ***
	void constructObjects();

	// *** PUBLIC MEMBER VARIABLES ***

	// *** List of OSM XML Elements ***
	/*! list of nodes */
	std::unordered_map<unsigned int, Node>			m_nodes;
	/*! list of ways */
	std::unordered_map<unsigned int, Way>			m_ways;
	/*! lists of relations */
	std::unordered_map<unsigned int, Relation>		m_relations;
	/*! Stores the bounding box of the drawing */
	BoundingBox										m_boundingBox;		// XML:E
	mutable GeometryData									m_geometryDataBoundingBox;


	/*! UTM zone defined by the longitude (minlon) of the bounding box */
	int												m_utmZone = 0;				// XML:A
	double											m_centerX = 0;				// XML:A
	double											m_centerY = 0;				// XML:A

	/*! point of origin */
	IBKMK::Vector3D									m_origin			= IBKMK::Vector3D(0,0,0);
	/*! rotation matrix */
	RotationMatrix									m_rotationMatrix	= RotationMatrix(QQuaternion(1.0,0.0,0.0,0.0));
	/*! scale factor */
	double											m_scalingFactor		= 1.0;

	bool											m_enable3D			= true;	// XML:A

	// *** List of OSM Objects like buildings, streets with all relevant information ***
	std::vector<OSMBuilding>								m_houses;		// XML:E
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

	mutable std::map<const AbstractDrawingObject*, GeometryData>	m_geometryData;
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
