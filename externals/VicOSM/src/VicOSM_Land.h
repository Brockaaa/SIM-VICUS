#ifndef VicOSM_LAND_H
#define VicOSM_LAND_H

#include "VicOSM_AbstractOSMObject.h"
#include "VicOSM_Way.h"
#include "VicOSM_Relation.h"

namespace VicOSM {
/*! Land class in the VicOSM library. Represents a type of object visible in the scene */
class Land : public AbstractOSMObject {
public:
	void readXML(const TiXmlElement * element);
	TiXmlElement * writeXML(TiXmlElement * parent) const;

	//:inherited	std::string						m_key = "";				// XML:A
	//:inherited	std::string						m_value = "";			// XML:A
	//:inherited	double							m_zPosition = 0;		// XML:A
	//:inherited	std::vector<Area>				m_areas;				// XML:E
	//:inherited	std::vector<LineFromPlanes>		m_linesFromPlanes;		// XML:E
	//:inherited	std::vector<Circle>				m_circles;				// XML:E

	/*! Helper function to set the color for a given key value combination of a landuse object */
	QColor	setColor();
	/*! Creates land object from way */
	bool createLand(Way &way);
	/*! Creates land object from relation */
	bool createLand(Relation &relation);

};

} // namespace VicOSM

#endif // VicOSM_LAND_H
