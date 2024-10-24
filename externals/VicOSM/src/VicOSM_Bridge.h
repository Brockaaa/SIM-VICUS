#ifndef VicOSM_BRIDGE_H
#define VicOSM_BRIDGE_H

#include "VicOSM_AbstractOSMObject.h"
#include "VicOSM_Way.h"
#include "VicOSM_Relation.h"

namespace VicOSM {
/*! Bridge class in the VicOSM library. Represents a type of object visible in the scene */
class Bridge : public AbstractOSMObject {
public:
	void readXML(const TiXmlElement * element);
	TiXmlElement * writeXML(TiXmlElement * parent) const;

	//:inherited	std::string						m_key = "";				// XML:A
	//:inherited	std::string						m_value = "";			// XML:A
	//:inherited	double							m_zPosition = 0;		// XML:A
	//:inherited	std::vector<Area>				m_areas;				// XML:E
	//:inherited	std::vector<LineFromPlanes>		m_linesFromPlanes;		// XML:E
	//:inherited	std::vector<Circle>				m_circles;				// XML:E
	/*! Creates bridge object from way */
	bool createBridge(Way &way);
	bool createBridge(Relation &relation);

};

} // namespace VicOSM

#endif // VicOSM_BRIDGE_H
