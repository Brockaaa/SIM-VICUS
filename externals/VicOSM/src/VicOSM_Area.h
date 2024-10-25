#ifndef VicOSM_AREA_H
#define VicOSM_AREA_H

#include <QColor>
#include "VicOSM_AbstractDrawingObject.h"
#include "tinyxml.h"

namespace VicOSM {

/*! Class Area inherits from AbstractDrawingObject and describes a single polygon optionally with holes.
	Can have minHeight and Height specified and can be drawn as a 3d extructing polygon */
class Area : public AbstractDrawingObject {
public:
	void readXML(const TiXmlElement * element);
	TiXmlElement * writeXML(TiXmlElement * parent) const;

	/*! Contains the (single) polygon with optional holes*/
	Multipolygon						m_multiPolygon;					// XML:E
	/*! Specifies if area should be drawn as an extruding polygon */
	bool								m_extrudingPolygon = false;		// XML:A
	/*! Specifies the height of the top face of the extruding polygon if drawn in 3d */
	double								m_height = 3;					// XML:A
	/*! Specifies the height of the bottom face of the extruding polygon if drawn in 3d */
	double							    m_minHeight = 0;				// XML:A
	/*! Specifies the color of the polygon */
	QColor								m_color	  = QColor("#2f302f");	// XML:A
};

} // namespace VicOSM

#endif // VicOSM_AREA_H
