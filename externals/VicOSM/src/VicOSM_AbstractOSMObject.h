#ifndef VicOSM_ABSTRACTOSMOBJECT_H
#define VicOSM_ABSTRACTOSMOBJECT_H

#include <vector>

#include "VicOSM_AbstractOSMElement.h"

#include "VicOSM_Area.h"
#include "VicOSM_LineFromPlanes.h"
#include "VicOSM_Circle.h"

namespace VicOSM {

/*! Provides enum for key value pairs. Also defines the order in which objects are drawn when overlapping */
enum KeyValue {
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
	PLACE_SQUARE,
	LANDUSE_RELIGIOUS,
	HIGHWAY_GENERALAREA,
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
	RAILWAY,
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

/*! Abstract class for an osm object like buildings, highways, landuse etc. Holds all basid geometry objects like areas, lines etc.
	Also contains the key and value that defines this particular osm object. E.g. for a building it might be m_key="building", m_value="residential" */
class AbstractOSMObject {
public:
	void readXML(const TiXmlElement * element);
	TiXmlElement * writeXML(TiXmlElement * parent) const;
	/*! if called, will retriangulate all DrawingObjects in this OSM Object */
	void updatePlaneGeometry();
	/*! initializes an AbstractOSMObject. Checks if it might be underground, assigns m_value and sets the appropriate keyValue enum */
	bool initialize(AbstractOSMElement& osmElement);
	/*! assigns a keyValue enum based on the set m_key and m_value */
	void assignEnum();

	/*! Contains all areas in the OSM Object */
	std::vector<Area>					m_areas;				// XML:E
	/*! Contains all lines in the OSM Object */
	std::vector<LineFromPlanes>			m_linesFromPlanes;		// XML:E
	/*! Contains all circles in the OSM Object */
	std::vector<Circle>					m_circles;				// XML:E
	/*! Unique ID of the OSM object defined by the relation, way or node describing this OSM object. The ID space is described by openstreetmap and is unique for every osm element
		in Planet.osm */
	unsigned int						m_id = 0xFFFFFFFF;		// XML:A
	/*! Key that defines this OSM Object. */
	std::string							m_key = "";				// XML:A
	/*! Value of the key that defines this OSM Object. */
	std::string							m_value = "";			// XML:A
	/*! Display name of Building, visible in navigation tree */
	std::string							m_displayName = "";		// XML:A

	// *** runtime only used in contructObjects
	/*! Key and value enum that define this OSM Object. Only relevant for the order which the OSMObjects overlap.
		If a type of OSMObject should be higher or lower, the KeyValue enum should be modified */
	KeyValue							m_keyValue = NUM_KV;
	/*! z value. Only relevant for the order which the OSMObjects overlap. */
	double								m_zPosition = 0;
	/*! Layer of the OSM Object. Only relevant for the order which the OSMObjects overlap. */
	int									m_layer = 0;

	/*! Flag to indictate recalculation of points. */
	mutable bool						m_dirtyPoints = true;

	/*! Indicates whether object is visible in the scene. */
	mutable bool						m_visible = true;				// XML:A

	/*! Indicates whether object is selected. */
	mutable bool						m_selected = false;
};

} // namespace VicOSM

#endif // VicOSM_ABSTRACTOSMOBJECT_H
