#ifndef VicOSM_NATURAL_H
#define VicOSM_NATURAL_H

#include "VicOSM_AbstractOSMObject.h"
#include "VicOSM_Node.h"
#include "VicOSM_Way.h"

namespace VicOSM {

class Natural : public AbstractOSMObject {
public:
	void readXML(const TiXmlElement * element);
	TiXmlElement * writeXML(TiXmlElement * parent) const;

	//:inherited	std::string						m_key = "";				// XML:A
	//:inherited	std::string						m_value = "";			// XML:A
	//:inherited	double							m_zPosition = 0;		// XML:A
	//:inherited	std::vector<Area>				m_areas;				// XML:E
	//:inherited	std::vector<LineFromPlanes>		m_linesFromPlanes;		// XML:E
	//:inherited	std::vector<Circle>				m_circles;				// XML:E

	static bool createNatural(Node &node, Natural& natural);
	static bool createNatural(Way &way, Natural& natural);

};

} // namespace VicOSM

#endif // VicOSM_NATURAL_H
