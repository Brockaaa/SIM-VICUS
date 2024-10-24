#ifndef VicOSM_MULTIPOLYGON_H
#define VicOSM_MULTIPOLYGON_H

#include <vector>
#include <IBKMK_Vector2D.h>
#include <tinyxml.h>

namespace VicOSM {

class Multipolygon {
public:
	void readXML(const TiXmlElement * element);
	TiXmlElement * writeXML(TiXmlElement * parent) const;

	std::vector<IBKMK::Vector2D> m_outerPolyline;					// IBKMK Vector2D TODO
	std::vector<std::vector<IBKMK::Vector2D>> m_innerPolylines;
};

} // namespace VicOSM

#endif // VicOSM_MULTIPOLYGON_H
