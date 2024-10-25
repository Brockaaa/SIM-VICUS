#ifndef VicOSM_NODE_H
#define VicOSM_NODE_H

#include "VicOSM_AbstractOSMElement.h"

namespace VicOSM {

/*! A single point on the map */
class Node : public AbstractOSMElement {
public:
	/*! readXML (handwritten) to read a node in a .osm file */
	void readXML(const TiXmlElement * element);

	/*! Longitude */
	double                          m_lon;
	/*! Latitude */
	double                          m_lat;
};

} // namespace VicOSM

#endif // VicOSM_NODE_H
