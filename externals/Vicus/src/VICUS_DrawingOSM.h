#ifndef VICUS_DRAWINGOSM_H
#define VICUS_DRAWINGOSM_H

#include "VICUS_Constants.h"
#include "tinyxml.h"

#include <IBKMK_Vector2D.h>
#include <VICUS_Object.h>
#include <string>
#include <vector>

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

	enum MainTag{
		T_building,
		T_highway,
		T_waterway,
		T_natural,
		NumT,
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

	struct BoundingBox{
		double minlat;
		double maxlat;
		double minlon;
		double maxlon;
	};

	/* Abstract class for all OSM XML elements */
	struct AbstractOSMElement {

		void readXML(const TiXmlElement * element);

		bool containsKey(const std::string& key) const;

		bool containsValue(const std::string& value) const;

		bool containsKeyValue(const std::string& key, const std::string& value) const;

		unsigned int                    m_id = VICUS::INVALID_ID; // unique id

		std::vector<Tag>				m_tags; // stores all tags. Does not make an effort to interpret them

		bool                            m_visible = true; // visibility flag
	};

	/*! A single point on the mapo */
	struct Node : public AbstractOSMElement {

		void readXML(const TiXmlElement * element);

		/*! Point coordinate */
		double                          m_lon;
		double                          m_lat;
	};

	/*! List of Nodes that make up a way. A way describes a polylines */
	struct Way : public AbstractOSMElement {

		void readXML(const TiXmlElement * element);

		std::vector<Nd>				m_nd;
	};

	/*! Stores both LW and normal polyline */
	struct Relation : public AbstractOSMElement {

		void readXML(const TiXmlElement * element);

		std::vector<Member>				m_members;
	};


	struct GeometryData {
		std::vector<VICUS::PlaneGeometry>	m_planeGeometry;
		QColor								m_color;
	};

	struct AbstractDrawingObject {

		AbstractDrawingObject(const DrawingOSM * drawing)
			: m_drawing(drawing)
		{}

		const virtual void addGeometryData(std::vector<VICUS::DrawingOSM::GeometryData*> &data) const = 0;

		void updatePlaneGeometry() {
			m_dirtyTriangulation = true;
		}

		unsigned int m_zPosition = 0;

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

	struct AreaBorder : AbstractDrawingObject {

		AreaBorder(const DrawingOSM * drawing)
			: AbstractDrawingObject(drawing)
		{}

		/*! polyline coordinates */
		std::vector<IBKMK::Vector2D>		m_polyline;
		std::vector<std::vector<IBKMK::Vector2D>>		m_innerPolylines;
		QColor								m_colorArea	  = QColor("#2f302f");
		QColor								m_colorBorder = QColor("#c7b7b0");

		bool								m_multipolygon = false;

		const void addGeometryData(std::vector<VICUS::DrawingOSM::GeometryData*> &data) const override;
	};

	struct AreaNoBorder : AbstractDrawingObject {

		AreaNoBorder(const DrawingOSM * drawing)
			: AbstractDrawingObject(drawing)
		{}

		/*! polyline coordinates */
		std::vector<IBKMK::Vector2D>		m_polyline;
		std::vector<IBKMK::Vector2D>		m_innerPolylines;
		QColor								m_color = QColor(Qt::black);

		bool								m_multipolygon = false;

		const void addGeometryData(std::vector<VICUS::DrawingOSM::GeometryData*> &data) const override;
	};

	struct LineFromPlanes : AbstractDrawingObject {

		LineFromPlanes(const DrawingOSM * drawing)
			: AbstractDrawingObject(drawing)
		{}

		/*! polyline coordinates */
		std::vector<IBKMK::Vector2D>		m_polyline;

		double								m_lineThickness = 0.3;

		QColor								m_color = QColor(Qt::black);

		const void addGeometryData(std::vector<VICUS::DrawingOSM::GeometryData*> &data) const override;
	};

	struct AbstractOSMObject {
		const virtual void addGeometryData(std::vector<VICUS::DrawingOSM::GeometryData*> &data) const = 0;
	};

	// https://wiki.openstreetmap.org/wiki/Simple_3D_Buildings#How_to_map
	/*! Building Object. Contains only 2D information. */
	struct Building : AbstractOSMObject {
		std::vector<AreaBorder>				m_areaBorders;

		const void addGeometryData(std::vector<VICUS::DrawingOSM::GeometryData*> &data) const override;
	};

	struct Highway : AbstractOSMObject {
		std::vector<LineFromPlanes>			m_linesFromPlanes;

		double								m_lineThickness = 0.3;

		const void addGeometryData(std::vector<VICUS::DrawingOSM::GeometryData*> &data) const override;
	};

	struct Water : AbstractOSMObject {
		std::vector<AreaNoBorder>			m_areaNoBorder;

		const void addGeometryData(std::vector<VICUS::DrawingOSM::GeometryData*> &data) const override;

	};


	// *** PUBLIC MEMBER FUNCTIONS ***

	/*! Fills m_nodes, m_ways, m_relations, m_boundingBox with values from a OSM XML */
	void readXML(const TiXmlElement * element);

	/*! calls readXML. Afterwards calculates m_utmZone and m_origin */
	bool readOSMFile(QString filePath);
	void constructObjects();

	/*! Updates all planes, when transformation operations are applied.
		MIND: Always call this function, when the drawing transformation
		(translation, rotation) were changed, since the triangulation is
		redone.
	*/
	void updatePlaneGeometries();


	const Node* findNodeFromId(unsigned int id) const;
	const Way* findWayFromId(unsigned int id) const;
	const Relation* findRelationFromId(unsigned int id) const;
	inline IBKMK::Vector2D convertLatLonToVector2D(double lat, double lon);

	// *** Methods to create Buildings streets. etc. ***

	// creates complete buildings from ways relations etc.
	void createBuilding(Way &way);
	void createBuilding(Relation &relation);

	// extracts streets from ways relations etc.
	void createHighway(Way &way);
	void createHighway(Relation &relation);

	// extracts water body from ways relations etc.
	void createWater(Way &way);

	// *** PUBLIC MEMBER VARIABLES ***

	// *** List of OSM XML Elements ***
	/*! list of nodes */
	std::vector<Node>								m_nodes;
	/*! list of ways */
	std::vector<Way>								m_ways;
	/*! lists of relations */
	std::vector<Relation>							m_relations;
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

	// *** List of OSM Objects like buildings, streets with all relevant information ***
	std::vector<Building>							m_buildings;
	std::vector<Highway>							m_highways;
	std::vector<Water>								m_waters;

	/*! path of the OSM File */
	QString											m_filePath;

private:
	void processRelation(const Relation& relation, std::vector<const Node*>& nodes, std::vector<const Way*>& ways, bool& outline);

	/*! Function to generate plane geometries from a polyline. */
	bool generatePlanesFromPolyline(const std::vector<IBKMK::Vector3D> & polyline,
									bool connectEndStart, double width, std::vector<PlaneGeometry> &planes) const;

	/*! Flag to indictate recalculation triangulation. */
	mutable bool								m_dirtyTriangulation = true;

};

} // namespace VICUS



#endif // VICUS_DRAWINGOSM_H
