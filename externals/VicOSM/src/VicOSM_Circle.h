#ifndef VicOSM_CIRCLE_H
#define VicOSM_CIRCLE_H

#include <QColor>
#include "VicOSM_AbstractDrawingObject.h"
#include "tinyxml.h"

namespace VicOSM {

class Circle : public AbstractDrawingObject {
public:
	void readXML(const TiXmlElement * element);
	TiXmlElement * writeXML(TiXmlElement * parent) const;

	double								m_x = 0;						// XML:A
	double								m_y = 0;						// XML:A
	double								m_radius = 1;					// XML:A
	QColor								m_color = QColor("#b8d4a7");	// XML:A
};

} // namespace VicOSM

#endif // VicOSM_CIRCLE_H
