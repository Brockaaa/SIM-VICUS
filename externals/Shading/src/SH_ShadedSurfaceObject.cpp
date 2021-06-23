#include "SH_ShadedSurfaceObject.h"

#include <IBK_Exception.h>
#include <IBK_assert.h>

#include <IBKMK_2DCalculations.h>
#include <IBKMK_3DCalculations.h>

namespace SH {

void ShadedSurfaceObject::setPolygon(const IBKMK::Polygon3D & surface, double gridWidth) {
	IBK_ASSERT(gridWidth > 0);

	//find min and max in x and y direction
	m_minX = std::numeric_limits<double>::max();
	m_minY = std::numeric_limits<double>::max();
	m_maxX = std::numeric_limits<double>::min();
	m_maxY = std::numeric_limits<double>::min();
	const std::vector<IBKMK::Vector2D> & polyline = surface.polyline().vertexes();
	for (size_t i=0; i<polyline.size(); ++i) {
		const IBKMK::Vector2D &p = polyline[i];
		m_minX = std::min(m_minX, p.m_x);
		m_minY = std::min(m_minY, p.m_y);
		m_maxX = std::max(m_maxX, p.m_x);
		m_maxY = std::max(m_maxY, p.m_y);
	}

	double distanceX = m_maxX - m_minX;
	double distanceY = m_maxY - m_minY;

	for (size_t xSteps=0, xM=(size_t)std::ceil(distanceX/gridWidth); xSteps<xM; ++xSteps) {
		for (size_t ySteps=0; ySteps<std::ceil(distanceY/gridWidth); ++ySteps) {
			// determine grid point in grid
			IBKMK::Vector2D newMiddlePoint(m_minX + (xSteps + 0.5)*gridWidth, m_minY + (ySteps + 0.5)*gridWidth);
			// only store grid point if it is inside the polygon
			if (IBKMK::pointInPolygon(polyline, newMiddlePoint) >= 0) {
				// store original point
				m_gridPoints.push_back( surface.vertexes()[0] + surface.localX() * newMiddlePoint.m_x + surface.localY() * newMiddlePoint.m_y);
			}
		}
	}

	//if no middlepoint was good enough, just check all boundary points
	if (m_gridPoints.empty())
		m_gridPoints = surface.vertexes();
}


double ShadedSurfaceObject::calcShadingFactor(const IBKMK::Vector3D &sunNormal, const std::vector<IBKMK::Polygon3D> & m_obstacles) const {
	unsigned int counterShadedPoints=0;

	unsigned int sizeMiddlePoints = m_gridPoints.size();
	// process all grid points
	for (size_t i=0; i<sizeMiddlePoints; ++i) {

		// process all obstacles
		for (size_t j=0; j<m_obstacles.size(); ++j) {

			// compute intersection point of sun beam onto obstacle's plane
			const IBKMK::Vector3D & offset = m_obstacles[j].vertexes()[0];
			IBKMK::Vector3D intersectionPoint;
			double dist;
			if (!IBKMK::linePlaneIntersection(offset, m_obstacles[j].normal(), // plane
											  m_gridPoints[i], sunNormal, // line
											  intersectionPoint, dist))
				continue; // no intersection, next obstacle plane

			// compute local coordinates of intersection point with obstacle
			double x,y;
			if (!IBKMK::planeCoordinates(offset, m_obstacles[j].localX(), m_obstacles[j].localY(), intersectionPoint, x, y))
				continue; // projection not possible - this shouldn't happen, really!

			// now test if x,y coordinates are inside obstacle's polyline
			if (IBKMK::pointInPolygon(m_obstacles[j].polyline().vertexes(), IBK::point2D<double>(x,y))) {
				++counterShadedPoints;
				break; // we are shaded, stop searching
			}
		}
	}

	double sf = double(counterShadedPoints)/sizeMiddlePoints;
	return sf;
}


} // namespace SH

