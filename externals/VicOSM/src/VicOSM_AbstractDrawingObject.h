#ifndef VicOSM_ABSTRACTDRAWINGOBJECT_H
#define VicOSM_ABSTRACTDRAWINGOBJECT_H

#include <vector>
#include "VicOSM_Multipolygon.h"

namespace VicOSM {

struct AbstractDrawingObject {
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
