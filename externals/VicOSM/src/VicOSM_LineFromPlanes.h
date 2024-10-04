#ifndef VicOSM_LINEFROMPLANES_H
#define VicOSM_LINEFROMPLANES_H

#include <QColor>
#include "VicOSM_AbstractDrawingObject.h"

namespace VicOSM {

struct LineFromPlanes : AbstractDrawingObject {
	/*! polyline coordinates */
	std::vector<IBKMK::Vector2D>		m_polyline;

	double								m_lineThickness = 1;

	QColor								m_color = QColor("#78909c");
};

} // namespace VicOSM

#endif // VicOSM_LINEFROMPLANE_H
