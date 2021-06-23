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

#ifndef Vic3DNewSubSurfaceObjectH
#define Vic3DNewSubSurfaceObjectH

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "Vic3DVertex.h"

#include <VICUS_PlaneGeometry.h>
#include <VICUS_Surface.h>

QT_BEGIN_NAMESPACE
class QOpenGLShaderProgram;
QT_END_NAMESPACE

class SVPropVertexListWidget;

namespace Vic3D {


/*! This object is painted when new subsurfaces are being created.

	Uses the same shader for opaque and transparent geometries.

	Buffer contains data for the partially-transparent geometries (those are
	painted with a little offset to avoid z-level fighting). Also, the outlines
	of the geometries are drawn (with lines) and the base-lines of the selected
	surfaces.

	Vertex-buffer holds first vertexes of generated surfaces. Then vertexes of the
	base-line polygons. Color buffer contains associated colors.

	Index-buffer order is:
	- triangle indexes for m_nTriangles triangles of transparent new surfaces (drawn in
	  renderTransparent()
	- line indexes for m_nLines lines (drawn in renderOpaque())
*/
class NewSubSurfaceObject {
public:

	/*! Encapsulates all data needed for window generation. */
	struct WindowComputationData {
		WindowComputationData() {
			for (int i=0; i<4; ++i)  m_priorities[i] = i+1;
		}

		int		m_priorities[4];
		double	m_width; // in m
		double	m_height; // in m
		double	m_windowSillHeight; // in m
		double	m_distance; // in m
		bool	m_byPercentage;
		double	m_percentage; // in percent 0..100
		double	m_baseLineOffset; // in m
	};

	NewSubSurfaceObject();

	/*! The function is called during OpenGL initialization, where the OpenGL context is current.
		This only initializes the buffers and vertex array object, but does not allocate data.
	*/
	void create(QOpenGLShaderProgram * shaderProgram);

	/*! Destroys allocated resources. */
	void destroy();


	// Functions related to modifying the stored geometry

	void clear() { generateSubSurfaces(std::vector<const VICUS::Surface*>(), WindowComputationData());  }

	/*! This function pupulates/updates m_surfaceGeometries based on the currently selected surfaces and
		parametrization data.
	*/
	void generateSubSurfaces(const std::vector<const VICUS::Surface*> & sel, const WindowComputationData & inputData);

	/*! Renders opaque parts of geometry. */
	void renderOpaque();
	/*! Renders transparent parts of geometry. */
	void renderTransparent();

private:
	/*! Populates the color and vertex buffer with data for the "last segment" line and the polygon.
		Resizes vertex and element buffers on GPU memory and copies data from locally stored vertex/element arrays to GPU.

		Basically transfers data in m_vertexBufferData, m_colorBufferData and m_elementBufferData to GPU memory.

		\param onlyLocalCSMoved Performance enhancement parameter - indicated that only the position
			of the local coordinate system has changed, and thus only a smaller part of the
			buffer may be needed to be redrawn.
	*/
	void updateBuffers();


	/*! Stores the modified geometries of the selected surfaces with windows.
		These are then drawn with this object.
	*/
	std::vector<VICUS::PlaneGeometry>	m_surfaceGeometries;

	/*! This list holds all points a the drawing method (even points of collinear segments).
		This list may not give a valid polygon or a polygon at all.
	*/
	std::vector<IBKMK::Vector3D>	m_vertexList;

	/*! Vertex buffer in CPU memory, holds data of all vertices (coords and normals). */
	std::vector<Vertex>				m_vertexBufferData;
	/*! Color buffer in CPU memory, holds colors of all vertices (same size as m_vertexBufferData). */
	std::vector<ColorRGBA>			m_colorBufferData;
	/*! Index buffer on CPU memory. */
	std::vector<GLuint>				m_indexBufferData;

	/*! Start element index for transparent planes. */
	unsigned int					m_transparentStartIndex = 0;

	/*! Start element index for line numbers. */
	unsigned int					m_lineIndex = 0;


	/*! VertexArrayObject, references the vertex, color and index buffers. */
	QOpenGLVertexArrayObject		m_vao;

	/*! Handle for vertex buffer on GPU memory. */
	QOpenGLBuffer					m_vertexBufferObject;
	/*! Handle for color buffer on GPU memory. */
	QOpenGLBuffer					m_colorBufferObject;
	/*! Handle for index buffer on GPU memory */
	QOpenGLBuffer					m_indexBufferObject;
};

} // namespace Vic3D

#endif // Vic3DNewSubSurfaceObjectH
