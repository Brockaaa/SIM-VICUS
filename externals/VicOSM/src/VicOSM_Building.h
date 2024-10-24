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
	//:inherited	double							m_zPosition = 0;		// XML:A
	//:inherited	std::vector<Area>				m_areas;				// XML:E
	//:inherited	std::vector<LineFromPlanes>		m_linesFromPlanes;		// XML:E
	//:inherited	std::vector<Circle>				m_circles;				// XML:E

	void calculateHeight(const AbstractOSMElement& element, Area& area);
	/*! Creates building object from way */
	bool createBuilding(Way &way, bool enable3D = false);
	/*! Creates building object from relation */
	bool createBuilding(Relation &relation, bool enable3D = false);
	bool initializeSimple3DBuilding(Relation &relation);

	Area createArea(const AbstractOSMElement & element, bool enable3D);

	double								m_levelHeight = 3;					// XML:A

	double								m_roofHeight = 3;					// XML:A
};

} // namespace VicOSM

#endif // VicOSM_BUILDING_H
