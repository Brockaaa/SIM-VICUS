/*	SIM-VICUS - Building and District Energy Simulation Tool.

	Copyright (c) 2020-today, Institut für Bauklimatik, TU Dresden, Germany

	Primary authors:
	  Andreas Nicolai  <andreas.nicolai -[at]- tu-dresden.de>
	  Dirk Weiss  <dirk.weiss -[at]- tu-dresden.de>
	  Stephan Hirth  <stephan.hirth -[at]- tu-dresden.de>
	  Hauke Hirsch  <hauke.hirsch -[at]- tu-dresden.de>

	  ... all the others from the SIM-VICUS team ... :-)

	This program is part of SIM-VICUS (https://github.com/ghorwin/SIM-VICUS)

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
*/

#ifndef Vic3DTrimmingObjectH
#define Vic3DTrimmingObjectH

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include <QMatrix4x4>
#include <QVector3D>

#include <IBKMK_Vector3D.h>

#include "IBKMK_Polygon3D.h"
#include "Vic3DVertex.h"
#include "Vic3DTransform3D.h"

QT_BEGIN_NAMESPACE
class QOpenGLShaderProgram;
QT_END_NAMESPACE

namespace VICUS {
	class GridPlane;
}

namespace Vic3D {

class ShaderProgram;

/*! This class holds all data needed to draw a trimming plane on the screen.
*/
class TrimmingObject {
public:
	TrimmingObject();

	/*! The function is called during OpenGL initialization, where the OpenGL context is current. 	*/
	void create(ShaderProgram * shaderProgram);
	void destroy();

	/*! Binds the buffer and paints. */
	void render();

	/*! Sets plane transformation matrix. */
	void setTrimmingPlaneNormal(const IBKMK::Vector3D &planeNormal);

	/*! Sets plane point. */
	void setTrimmingPlanePoint(const IBKMK::Vector3D &planePoint);

	/*! Sets current project bounding box. */
	void setBoundingBoxDimension(const IBKMK::Vector3D &center, const IBKMK::Vector3D &dimension);

	/*! Updates the current trimming plane with specified matrix and bounding box. */
	void updateTrimmingPlane();

	/*! Updates the current trimming plane with specified matrix and bounding box. */
	void updateTrimmingPlane(const IBKMK::Vector3D &normal);

	/*! Returns trimming plane normal. */
	const IBKMK::Vector3D &planeNormal() const;

	/*! Returns the trimming polygon. Is beeing populated in updateTrimmingPlane.
	*/
	const IBKMK::Polygon3D &trimmingPolygon() const;

	/*! Indicates if trimming plane is visible. */
	bool						m_trimmingPlaneVisible = false;

private:

	/*! Shader program, that the trimming is painted with. */
	ShaderProgram				*m_trimmingShader = nullptr;

	/*! Vertex buffer in CPU memory, holds data of all vertices (coords and normals). */
	std::vector<Vertex>			m_vertexBufferData;
	/*! Color buffer in CPU memory, holds colors of all vertices (same size as m_vertexBufferData). */
	std::vector<ColorRGBA>		m_colorBufferData;
	/*! Index buffer on CPU memory. */
	std::vector<GLuint>			m_indexBufferData;

	/*! VertexArrayObject, references the vertex, color and index buffers.
		\note The Vertex Array Object is used, so that vertex, color and index buffer
			  do not have to bind and specify vertex attributes (such as position, color, texture coordinates, etc.)
			  every time you render an object
	*/
	QOpenGLVertexArrayObject	m_vao;

	/*! Handle for vertex buffer on GPU memory. */
	QOpenGLBuffer				m_vertexBufferObject;
	/*! Handle for color buffer on GPU memory. */
	QOpenGLBuffer				m_colorBufferObject;
	/*! Handle for index buffer on GPU memory */
	QOpenGLBuffer				m_indexBufferObject;

	// Bounding box center
	QVector3D					m_bbCenter;

	// Bounding box dimension
	QVector3D					m_bbDimension;

	/*! Holds the number of vertices of plane. */
	GLsizei						m_vertexCount;

	/*! Point of trimming plane. */
	IBKMK::Vector3D				m_planePoint = IBKMK::Vector3D(0,0,0);

	/*! Cached Normal of trimming plane. Used for rotation of plane. */
	IBKMK::Vector3D				m_planeNormal = IBKMK::Vector3D(0,0,1);

	/*! Trimming polygon - is populated in updateTrimmingPlane().
		\note Is used for trimming operations in SVPropEditGeometry
	*/
	IBKMK::Polygon3D			m_trimmingPolygon;

};

} // namespace Vic3D


#endif // Vic3DGridObjectH
