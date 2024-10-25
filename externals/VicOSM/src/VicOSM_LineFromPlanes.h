#ifndef VicOSM_LINEFROMPLANES_H
#define VicOSM_LINEFROMPLANES_H

#include <QColor>
#include "VicOSM_AbstractDrawingObject.h"
#include "tinyxml.h"

namespace VicOSM {
/*! Class LineFromPlanes inherits from AbstractDrawingObject and describes a line defined by a (open or closed) polyline with a line Thickness.*/
class LineFromPlanes : public AbstractDrawingObject {
public:
	void readXML(const TiXmlElement * element);
	TiXmlElement * writeXML(TiXmlElement * parent) const;

	/*! polyline coordinates */
	Multipolygon						m_multiPolygon;					// XML:E
	/*! Thickness of the line */
	double								m_lineThickness = 1;			// XML:A
	/*! Color of the line */
	QColor								m_color = QColor("#78909c");	// XML:A
};

} // namespace VicOSM

#endif // VicOSM_LINEFROMPLANE_H
