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

#include "Vic3DTrimmingObject.h"

#include <QOpenGLShaderProgram>

#include <vector>

#include <VICUS_GridPlane.h>

#include <IBKMK_3DCalculations.h>

#include "SVConversions.h"

#include "Vic3DGeometryHelpers.h"
#include "Vic3DShaderProgram.h"
#include "Vic3DTransform3D.h"

#include "SVSettings.h"
#include "SVViewStateHandler.h"

namespace Vic3D {


TrimmingObject::TrimmingObject() :
	m_vertexBufferObject(QOpenGLBuffer::VertexBuffer), // VertexBuffer is the default, so default constructor would have been enough
	m_colorBufferObject(QOpenGLBuffer::VertexBuffer),
	m_indexBufferObject(QOpenGLBuffer::IndexBuffer), // make this an Index Buffer
	m_planePoint(IBKMK::Vector3D(0,0,0)),
	m_planeNormal(IBKMK::Vector3D(1,0,0))
{
	SVViewStateHandler::instance().m_trimmingObject = this;
}

void TrimmingObject::create(ShaderProgram * shaderProgram) {
	m_trimmingShader = shaderProgram;

	// *** create buffers on GPU memory ***

	// create a new buffer for the vertices and colors, separate buffers because we will modify colors way more often than geometry
	m_vertexBufferObject.create();
	m_vertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw); // usage pattern will be used when tranferring data to GPU

	m_colorBufferObject.create();
	m_colorBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);

	// create a new buffer for the indexes
	m_indexBufferObject = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer); // Note: make sure this is an index buffer
	m_indexBufferObject.create();
	m_indexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);


	// *** create and bind Vertex Array Object ***

	// Note: VAO must be bound *before* the element buffer is bound,
	//       because the VAO remembers associated element buffers.
	m_vao.create();
	m_vao.bind(); // now the VAO is active and remembers states modified in following calls

	m_indexBufferObject.bind(); // this registers this index buffer in the currently bound VAO


	// *** set attribute arrays for shader fetch stage ***

#define VERTEX_ARRAY_INDEX 0
#define NORMAL_ARRAY_INDEX 1
#define COLOR_ARRAY_INDEX 2

	m_vertexBufferObject.bind(); // this registers this buffer data object in the currently bound vao; in subsequent
				  // calls to shaderProgramm->setAttributeBuffer() the buffer object is associated with the
				  // respective attribute array that's fed into the shader. When the vao is later bound before
				  // rendering, this association is remembered so that the vertex fetch stage pulls data from
				  // this vbo

	// coordinates
	m_trimmingShader->shaderProgram()->enableAttributeArray(VERTEX_ARRAY_INDEX);
	m_trimmingShader->shaderProgram()->setAttributeBuffer(VERTEX_ARRAY_INDEX, GL_FLOAT, 0, 3 /* vec3 */, sizeof(Vertex));

	// normals
	m_trimmingShader->shaderProgram()->enableAttributeArray(NORMAL_ARRAY_INDEX);
	m_trimmingShader->shaderProgram()->setAttributeBuffer(NORMAL_ARRAY_INDEX, GL_FLOAT, offsetof(Vertex, m_normal), 3 /* vec3 */, sizeof(Vertex));


	m_colorBufferObject.bind(); // now color buffer is active in vao

	// colors
	m_trimmingShader->shaderProgram()->enableAttributeArray(COLOR_ARRAY_INDEX);
	m_trimmingShader->shaderProgram()->setAttributeBuffer(COLOR_ARRAY_INDEX, GL_UNSIGNED_BYTE, 0, 4, 4 /* bytes = sizeof(char) */);

	// Release (unbind) all

	// Mind: you can release the buffer data objects (vbo and vboColors) before or after releasing vao. It does not
	//       matter, because the buffers are associated already with the attribute arrays.
	//       However, YOU MUST NOT release the index buffer (ebo) before releasing the vao, since this would remove
	//       the index buffer association with the vao and when binding the vao before rendering, the element buffer
	//       would not be known and a call to glDrawElements() crashes!
	m_vao.release();

	m_vertexBufferObject.release();
	m_colorBufferObject.release();
	m_indexBufferObject.release();
}


void TrimmingObject::destroy() {
	m_vao.destroy();
	m_vertexBufferObject.destroy();
	m_colorBufferObject.destroy();
	m_indexBufferObject.destroy();

	m_trimmingShader = nullptr;
}


void TrimmingObject::render() {
	if (!m_trimmingPlaneVisible)
		return;

	// trimming plane is hidden
	if (m_vertexCount == 0)
		return;

	// draw plane with vao
	m_vao.bind();
	glDrawElements(GL_TRIANGLES, (GLsizei)m_indexBufferData.size(), GL_UNSIGNED_INT, nullptr);
	m_vao.release();
}

void TrimmingObject::setTrimmingPlaneNormal(const IBKMK::Vector3D &planeNormal) {
	//m_transformation.setRotation(0, IBKVector2QVector(planeNormal));
	m_planeNormal = planeNormal.normalized();

//	qDebug() << "Plane point: " << planePoint.m_x << " " << planePoint.m_y << " " << planePoint.m_z;
}

void TrimmingObject::setTrimmingPlanePoint(const IBKMK::Vector3D &planePoint) {
	// m_transformation.setTranslation(IBKVector2QVector(planePoint));
	m_planePoint = planePoint;
}


void TrimmingObject::setBoundingBoxDimension(const IBKMK::Vector3D &center, const IBKMK::Vector3D &dimension) {
	m_bbCenter = IBKVector2QVector(center);
	m_bbDimension = IBKVector2QVector(dimension);
}

void TrimmingObject::updateTrimmingPlane() {
	updateTrimmingPlane(m_planeNormal);
}

void TrimmingObject::updateTrimmingPlane(const IBKMK::Vector3D &normal) {
	// destroy();
	m_vertexCount = 0;

	m_vertexBufferData.clear();
	m_indexBufferData.clear();
	m_colorBufferData.clear();

	m_vertexBufferData.reserve(100000);
	m_colorBufferData.reserve(100000);
	m_indexBufferData.reserve(100000);

	std::vector<IBKMK::Vector3D> intersectionPoints, intersectionPointsSorted;

	QVector3D xAxis(1,0,0);
	QVector3D yAxis(0,1,0);
	QVector3D zAxis(0,0,1);

	QVector3D points[8];

	unsigned int COUNT = 2;
	for (unsigned int i=0; i < COUNT; ++i) {
		for (unsigned int j=0; j < COUNT; ++j) {
			for (unsigned int k=0; k < COUNT; ++k) {

				double x = (- 1.0 + 2 * i) * (m_bbDimension.x() + 1.0) / 2 ;
				double y = (- 1.0 + 2 * j) * (m_bbDimension.y() + 1.0) / 2 ;
				double z = (- 1.0 + 2 * k) * (m_bbDimension.z() + 1.0) / 2 ;

				points[4*i+2*j+k] = m_bbCenter + x * xAxis + y * yAxis + z * zAxis;
			}
		}
	}
	// All possible edges of a rectangular cuboid
	std::array<int, 2> edges[12] { {0, 1}, {0, 2}, {0, 4},
								   {3, 1}, {3, 2}, {3, 7},
								   {4, 5}, {4, 6}, {2, 6},
								   {7, 6}, {7, 5}, {1, 5} };
	for (unsigned int i=0; i < 12; ++i) {
		IBKMK::Vector3D p1 = QVector2IBKVector(points[edges[i][0]]);
		IBKMK::Vector3D p2 = QVector2IBKVector(points[edges[i][1]]);

		IBKMK::Vector3D p;
		double dist;
		bool intersected = IBKMK::linePlaneIntersection(m_planePoint, normal, p1, p2-p1, p, dist);

		if (intersected && dist > 0 && dist < 1)
			intersectionPoints.push_back(p);
	}

	if (intersectionPoints.empty())
		return;

	IBKMK::Vector3D centerPoint;
	for (unsigned int i=0; i < intersectionPoints.size(); ++i) {
		centerPoint += intersectionPoints[i];
	}
	centerPoint /= intersectionPoints.size();

	IBKMK::Vector3D perpendicularVector1 = m_planePoint.crossProduct(m_planeNormal);
	IBKMK::Vector3D referencePoint = m_planePoint + perpendicularVector1;

	intersectionPointsSorted = intersectionPoints;
	std::sort(intersectionPointsSorted.begin(), intersectionPointsSorted.end(), [&centerPoint, &referencePoint, this](const IBKMK::Vector3D& a, const IBKMK::Vector3D &b){
		IBKMK::Vector3D v1 = (referencePoint - centerPoint).normalized();
		IBKMK::Vector3D v2 = (a - centerPoint).normalized();
		IBKMK::Vector3D v3 = (b - centerPoint).normalized();

		double angle1 = IBKMK::angleBetweenVectorsDeg360(v2, v1, m_planeNormal);
		double angle2 = IBKMK::angleBetweenVectorsDeg360(v3, v1, m_planeNormal);

		return angle1 < angle2;
	});

	unsigned int currentVertexIndex = 0;
	unsigned int currentElementIndex = 0;

	// Transparent red
	QColor col(150, 0, 0, 100);
	QColor colBox(150, 0, 0, 0);

	VICUS::PlaneGeometry plane;
	plane.setPolygon(intersectionPointsSorted);
	if (!plane.isValid())
		return;

	// update trimming polygon
	m_trimmingPolygon = intersectionPointsSorted;

	// Add planes to buffers of GPU
	addPlane(plane.triangulationData(), col, currentVertexIndex, currentElementIndex, m_vertexBufferData, m_colorBufferData, m_indexBufferData, false);
	addPlane(plane.triangulationData(), col, currentVertexIndex, currentElementIndex, m_vertexBufferData, m_colorBufferData, m_indexBufferData, true);

	// If no data return
	if (m_indexBufferData.empty())
		return;

	// transfer data stored in m_vertexBufferData and m_indexBufferObject
	m_vertexBufferObject.bind();
	m_vertexBufferObject.allocate(m_vertexBufferData.data(), m_vertexBufferData.size()*sizeof(Vertex));
	m_vertexBufferObject.release();

	m_indexBufferObject.bind();
	m_indexBufferObject.allocate(m_indexBufferData.data(), m_indexBufferData.size()*sizeof(GLuint));
	m_indexBufferObject.release();

	// No color buffer data
	if (m_colorBufferData.empty())
		return;

	m_colorBufferObject.bind();
	m_colorBufferObject.allocate(m_colorBufferData.data(), m_colorBufferData.size()*sizeof(ColorRGBA) );
	m_colorBufferObject.release();

	// update vertex count
	m_vertexCount =  m_vertexBufferData.size();
}

const IBKMK::Vector3D &TrimmingObject::planeNormal() const {
	return m_planeNormal;
}

const IBKMK::Polygon3D &TrimmingObject::trimmingPolygon() const {
	return m_trimmingPolygon;
}

} // namespace Vic3D
