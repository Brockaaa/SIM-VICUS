#ifndef VicOSM_ABSTRACTDRAWINGOBJECT_H
#define VicOSM_ABSTRACTDRAWINGOBJECT_H

#include <vector>
#include "VicOSM_Multipolygon.h"

namespace VicOSM {
/*! Abstract Class for basic geometry objects like areas, lines, circles */
class AbstractDrawingObject {
public:
	/*! if called, will triangulate this drawing object again */
	void updatePlaneGeometry() {
		m_dirtyTriangulation = true;
	}

	/*! Flag to indictate recalculation of points. */
	mutable bool								m_dirtyPoints = true;
	/*! Flag to indictate recalculation triangulation. */
	mutable bool								m_dirtyTriangulation = true;
	/*! Points of objects. */
	mutable std::vector<IBKMK::Vector2D>		m_pickPoints;
};

} // namespace VicOSM

#endif // VicOSM_ABSTRACTDRAWINGOBJECT_H
