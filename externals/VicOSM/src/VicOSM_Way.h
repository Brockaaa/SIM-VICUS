#ifndef VicOSM_WAY_H
#define VicOSM_WAY_H

#include "VicOSM_AbstractOSMElement.h"

namespace VicOSM {

/*! List of Nodes that make up a way. A way describes a polyline */
class Way : public AbstractOSMElement {
public:
	/*! readXML (handwritten) to read a way in a .osm file */
	void readXML(const TiXmlElement * element);
};

} // namespace VicOSM

#endif // VicOSM_WAY_H
