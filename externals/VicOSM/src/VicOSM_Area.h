#ifndef VicOSM_AREA_H
#define VicOSM_AREA_H

#include <QColor>
#include "VicOSM_AbstractDrawingObject.h"
#include "tinyxml.h"

namespace VicOSM {

class Area : public AbstractDrawingObject {
public:
	void readXML(const TiXmlElement * element);
	TiXmlElement * writeXML(TiXmlElement * parent) const;

	Multipolygon						m_multiPolygon;					// XML:E
	bool								m_extrudingPolygon = false;		// XML:A
	double								m_height = 3;					// XML:A
	double							    m_minHeight = 0;				// XML:A
	QColor								m_color	  = QColor("#2f302f");	// XML:A
};

} // namespace VicOSM

#endif // VicOSM_AREA_H
