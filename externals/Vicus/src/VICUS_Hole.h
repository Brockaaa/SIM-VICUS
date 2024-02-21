#ifndef VICUS_HoleH
#define VICUS_HoleH

#include "VICUS_CodeGenMacros.h"
#include "VICUS_Polygon2D.h"

namespace VICUS {

/*! Represents a surface hole and its associated properties. */
class Hole {
public:
	VICUS_READWRITE

	/*! C'tor */
	Hole() {}

	/*! C'tor with Hole Polygon. */
	Hole(const Polygon2D &holePolygon) :
		m_holePolygon(holePolygon)
	{}

	/*! Hole geometry relative to parent geometry. */
	Polygon2D			m_holePolygon;						// XML:E
};

}
#endif // VICUS_SURFACEHOLE_H
