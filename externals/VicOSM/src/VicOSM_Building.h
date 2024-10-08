#ifndef VicOSM_BUILDING_H
#define VicOSM_BUILDING_H

#include "VicOSM_AbstractOSMObject.h"
#include "VicOSM_Way.h"
#include "VicOSM_Relation.h"

namespace VicOSM {

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

	void calculateHeight(AbstractOSMElement& element);

	static bool createBuilding(Way &way, OSMBuilding &building, bool enable3D = false);
	static bool createBuilding(Relation &relation, OSMBuilding &building, bool enable3D = false);

	double								m_height = 3;						// XML:A

	double								m_minHeight = 0;					// XML:A

	double								m_levelHeight = 3;					// XML:A

	double								m_roofHeight = 3;					// XML:A
};

} // namespace VicOSM

#endif // VicOSM_BUILDING_H
