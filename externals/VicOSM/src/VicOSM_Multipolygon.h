#ifndef VicOSM_MULTIPOLYGON_H
#define VicOSM_MULTIPOLYGON_H

#include <vector>
#include <IBKMK_Vector2D.h>
#include <tinyxml.h>

namespace VicOSM {
/*! Class describing a polygon using polylines with optional holes */
class Multipolygon {
public:
	void readXML(const TiXmlElement * element);
	TiXmlElement * writeXML(TiXmlElement * parent) const;

	/*! Outer polyline of a single Polygon */
	std::vector<IBKMK::Vector2D> m_outerPolyline;
	/*! Holes in the polygon. Coordinates are in the local coordinates of the polygon */
	std::vector<std::vector<IBKMK::Vector2D>> m_innerPolylines;
};

} // namespace VicOSM

#endif // VicOSM_MULTIPOLYGON_H
