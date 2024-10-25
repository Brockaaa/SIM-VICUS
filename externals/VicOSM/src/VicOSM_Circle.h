#ifndef VicOSM_CIRCLE_H
#define VicOSM_CIRCLE_H

#include <QColor>
#include "VicOSM_AbstractDrawingObject.h"
#include "tinyxml.h"

namespace VicOSM {
/*! Class Circle inherits from AbstractDrawingObject and contains a simple point with a radius to describe a circle.*/
class Circle : public AbstractDrawingObject {
public:
	void readXML(const TiXmlElement * element);
	TiXmlElement * writeXML(TiXmlElement * parent) const;

	/*! x coordinate of the center point of the circle */
	double								m_x = 0;						// XML:A
	/*! y coordinate of the center point of the circle */
	double								m_y = 0;						// XML:A
	/*! radius of the circle */
	double								m_radius = 1;					// XML:A
	/*! Color of the circle */
	QColor								m_color = QColor("#b8d4a7");	// XML:A
};

} // namespace VicOSM

#endif // VicOSM_CIRCLE_H
