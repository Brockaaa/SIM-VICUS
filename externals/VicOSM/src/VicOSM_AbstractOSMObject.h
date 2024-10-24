#ifndef VicOSM_ABSTRACTOSMOBJECT_H
#define VicOSM_ABSTRACTOSMOBJECT_H

#include <vector>

#include "VicOSM_AbstractOSMElement.h"

#include "VicOSM_Area.h"
#include "VicOSM_LineFromPlanes.h"
#include "VicOSM_Circle.h"

namespace VicOSM {

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

class AbstractOSMObject {
public:
	void updatePlaneGeometry();
	void readXML(const TiXmlElement * element);
	TiXmlElement * writeXML(TiXmlElement * parent) const;
	bool initialize(AbstractOSMElement& osmElement);

	void assignEnum();

	std::vector<Area>					m_areas;				// XML:E
	std::vector<LineFromPlanes>			m_linesFromPlanes;		// XML:E
	std::vector<Circle>					m_circles;				// XML:E

	unsigned int						m_id = 0xFFFFFFFF;		// XML:A

	std::string							m_key = "";				// XML:A

	std::string							m_value = "";			// XML:A

	// *** runtime only used in contructObjects
	KeyValue							m_keyValue = NUM_KV;

	double								m_zPosition = 0;

	int									m_layer = 0;

	/*! Flag to indictate recalculation of points. */
	mutable bool								m_dirtyPoints = true;
};

} // namespace VicOSM

#endif // VicOSM_ABSTRACTOSMOBJECT_H
