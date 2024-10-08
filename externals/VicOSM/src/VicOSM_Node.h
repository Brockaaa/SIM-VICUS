#ifndef VicOSM_NODE_H
#define VicOSM_NODE_H

#include "VicOSM_AbstractOSMElement.h"

namespace VicOSM {

/*! A single point on the map */
class Node : public AbstractOSMElement {
public:
	void readXML(const TiXmlElement * element);

	/*! Point coordinate */
	double                          m_lon;
	double                          m_lat;
};

} // namespace VicOSM

#endif // VicOSM_NODE_H
