#ifndef VicOSM_RELATION_H
#define VicOSM_RELATION_H

#include "VicOSM_AbstractOSMElement.h"

namespace VicOSM {

/*! List of Nodes that make up a way. A way describes a polyline */
class Relation : public AbstractOSMElement {
public:
	/*! readXML (handwritten) to read a relation in a .osm file */
	void readXML(const TiXmlElement * element);
};

} // namespace VicOSM

#endif // VicOSM_RELATION_H
