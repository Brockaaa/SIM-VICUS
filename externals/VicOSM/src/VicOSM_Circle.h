#ifndef VicOSM_CIRCLE_H
#define VicOSM_CIRCLE_H

#include <QColor>
#include "VicOSM_AbstractDrawingObject.h"

namespace VicOSM {

struct Circle : AbstractDrawingObject {
		IBKMK::Vector2D						m_center;
		double								m_radius = 1;
		QColor								m_color = QColor("#b8d4a7");
};

} // namespace VicOSM

#endif // VicOSM_CIRCLE_H
