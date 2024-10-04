#ifndef VicOSM_AREA_H
#define VicOSM_AREA_H

#include <QColor>
#include "VicOSM_AbstractDrawingObject.h"

namespace VicOSM {

struct Area : AbstractDrawingObject {
	Multipolygon						m_multiPolygon;
	bool								m_extrudingPolygon = false;
	double								m_height = 3;
	double							    m_minHeight = 0;
	QColor								m_color	  = QColor("#2f302f");
};

} // namespace VicOSM

#endif // VicOSM_AREA_H
