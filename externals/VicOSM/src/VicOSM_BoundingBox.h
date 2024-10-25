#ifndef VicOSM_BOUNDINGBOX_H
#define VicOSM_BOUNDINGBOX_H

#include "VicOSM_AbstractOSMObject.h"

namespace VicOSM {
/*! Describes the bounding box of the .osm file. Will be drawn as a rectangular below the map in the scene */
class BoundingBox {
public:
	void readXML(const TiXmlElement * element);
	TiXmlElement * writeXML(TiXmlElement * parent) const;

	/*! Minimum Latitude of the bounding box */
	double m_minlat;										// XML:A
	/*! Maximum Latitude of the bounding box */
	double m_maxlat;										// XML:A
	/*! Minimum Longitude of the bounding box */
	double m_minlon;										// XML:A
	/*! Maximum Latitude of the bounding box */
	double m_maxlon;										// XML:A
	/*! z value. Only relevant for the order which the OSMObjects overlap. */
	double								m_zPosition = 0;	// XML:A
};

} // namespace VicOSM

#endif // VicOSM_BOUNDINGBOX_H
