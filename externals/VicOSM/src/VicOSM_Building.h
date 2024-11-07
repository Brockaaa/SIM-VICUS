#ifndef VicOSM_BUILDING_H
#define VicOSM_BUILDING_H

#include "VicOSM_AbstractOSMObject.h"
#include "VicOSM_Way.h"
#include "VicOSM_Relation.h"

namespace VicOSM {
/*! Building class in the VicOSM library. Represents a type of object visible in the scene */
class OSMBuilding : public AbstractOSMObject {
public:
	void readXML(const TiXmlElement * element);
	TiXmlElement * writeXML(TiXmlElement * parent) const;

	//:inherited	std::string						m_key = "";				// XML:A
	//:inherited	std::string						m_value = "";			// XML:A
	//:inherited	std::string						m_displayName = "";		// XML:A
	//:inherited	double							m_zPosition = 0;		// XML:A
	//:inherited	std::vector<Area>				m_areas;				// XML:E
	//:inherited	std::vector<LineFromPlanes>		m_linesFromPlanes;		// XML:E
	//:inherited	std::vector<Circle>				m_circles;				// XML:E

	/*! Calculates the m_height and m_minHeight of an area in this building */
	void calculateHeight(const AbstractOSMElement& element, Area& area) const;
	/*! Creates building object from way */
	bool createBuilding(Way &way, bool enable3D = false);
	/*! Creates building object from relation */
	bool createBuilding(Relation &relation, bool enable3D = false);
	/*! Helper function to initialize a building relation if 3D geometry is enabled */
	bool initializeSimple3DBuilding(Relation &relation);
	/*! Helper function to initialze an area from a way or relation. Does not read in geometry data like the coordinates of a node */
	Area createArea(const AbstractOSMElement & element, bool enable3D);
	/*! Helper function to set the display name in the navigation tree */
	void setDisplayName(const AbstractOSMElement& element);
	/*! setter for m_visible */
	void setVisible(bool visible);
	/*! setter for m_selected */
	void setSelected(bool selected);
	/*! Specifies the default height of a building level. Value 3 taken from the osm wiki. Can be specified for an individual OSM object */
	double								m_levelHeight = 3;					// XML:A
	/*! Specifies the default height of roof. Value 3 taken from the osm wiki. Can be specified for an individual OSM Element */
	double								m_roofHeight = 3;					// XML:A
	/*! Specifies the position of the area that describes the outline of the building in the m_areas std::vector. Used for switching between 2D and 3D rendering of buildings */
	Area								m_outline;							// XML:E
};

} // namespace VicOSM

#endif // VicOSM_BUILDING_H
