#ifndef VicOSM_LINEFROMPLANES_H
#define VicOSM_LINEFROMPLANES_H

#include <QColor>
#include "VicOSM_AbstractDrawingObject.h"
#include "tinyxml.h"

namespace VicOSM {

class LineFromPlanes : public AbstractDrawingObject {
public:
	void readXML(const TiXmlElement * element);
	TiXmlElement * writeXML(TiXmlElement * parent) const;

	/*! polyline coordinates */
	Multipolygon						m_multiPolygon;		// XML:E
	double								m_lineThickness = 1;			// XML:A
	QColor								m_color = QColor("#78909c");	// XML:A
};

} // namespace VicOSM

#endif // VicOSM_LINEFROMPLANE_H
