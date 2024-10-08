#ifndef VicOSM_BOUNDINGBOX_H
#define VicOSM_BOUNDINGBOX_H

#include "VicOSM_AbstractOSMObject.h"

namespace VicOSM {

class BoundingBox {
public:
	void readXML(const TiXmlElement * element);
	TiXmlElement * writeXML(TiXmlElement * parent) const;

	double m_minlat;										// XML:A
	double m_maxlat;										// XML:A
	double m_minlon;										// XML:A
	double m_maxlon;										// XML:A

	double								m_zPosition = 0;	// XML:A
};

} // namespace VicOSM

#endif // VicOSM_BOUNDINGBOX_H
