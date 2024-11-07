#include "Vic3DOSMObject.h"

#include <QOpenGLShaderProgram>

#include <QProgressDialog>
#include <QApplication>
#include <QCoreApplication>

#include <SVMainWindow.h>

#include <Vic3DOpaqueGeometryObject.h>
#include <SVProjectHandler.h>
#include <Vic3DShaderProgram.h>
#include <Vic3DGeometryHelpers.h>

#include <VICUS_DrawingOSM.h>
#include <VICUS_Project.h>

#include <vector>

namespace Vic3D {

OSMObject::OSMObject() {}

void OSMObject::create(ShaderProgram * shaderProgram) {
	if (m_shaderProgram != nullptr) return;
	m_shaderProgram = shaderProgram->shaderProgram();
	m_buildingShader = shaderProgram;
}

void OSMObject::destroy()
{
	for (auto VAOWithBuffer : m_VAOWithBuffers) {
		VAOWithBuffer->m_vao.destroy();
		VAOWithBuffer->m_vertexBufferObject.destroy();
		VAOWithBuffer->m_colorBufferObject.destroy();
		VAOWithBuffer->m_indexBufferObject.destroy();
		delete(VAOWithBuffer);
	}
	m_VAOWithBuffers.clear();
}

void OSMObject::configureNewVAOWithBuffer(VAOWithBufferStruct * VAOWithBuffer)
{
	if (VAOWithBuffer->m_vao.isCreated())
		return;

	// *** create buffers on GPU memory ***
	VAOWithBuffer->m_vertexBufferObject = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer); // VertexBuffer is the default, so default constructor would have been enough
	VAOWithBuffer->m_colorBufferObject = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	VAOWithBuffer->m_indexBufferObject = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

	// create a new buffer for the vertices and colors, separate buffers because we will modify colors way more often than geometry
	VAOWithBuffer->m_vertexBufferObject.create();
	VAOWithBuffer->m_vertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw); // usage pattern will be used when tranferring data to GPU

	VAOWithBuffer->m_colorBufferObject.create();
	VAOWithBuffer->m_colorBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);

	// create a new buffer for the indexes
	VAOWithBuffer->m_indexBufferObject = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer); // Note: make sure this is an index buffer
	VAOWithBuffer->m_indexBufferObject.create();
	VAOWithBuffer->m_indexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);


	// *** create and bind Vertex Array Object ***

	// Note: VAO must be bound *before* the element buffer is bound,
	//       because the VAO remembers associated element buffers.
	VAOWithBuffer->m_vao.create();
	VAOWithBuffer->m_vao.bind(); // now the VAO is active and remembers states modified in following calls

	VAOWithBuffer->m_indexBufferObject.bind(); // this registers this index buffer in the currently bound VAO


// *** set attribute arrays for shader fetch stage ***

#define VERTEX_ARRAY_INDEX 0
#define NORMAL_ARRAY_INDEX 1
#define COLOR_ARRAY_INDEX 2

	VAOWithBuffer->m_vertexBufferObject.bind(); // this registers this buffer data object in the currently bound vao; in subsequent
		// calls to shaderProgramm->setAttributeBuffer() the buffer object is associated with the
		// respective attribute array that's fed into the shader. When the vao is later bound before
		// rendering, this association is remembered so that the vertex fetch stage pulls data from
		// this vbo

	// coordinates
	m_shaderProgram->enableAttributeArray(VERTEX_ARRAY_INDEX);
	m_shaderProgram->setAttributeBuffer(VERTEX_ARRAY_INDEX, GL_FLOAT, 0, 3 /* vec3 */, sizeof(Vertex));

	// normals
	m_shaderProgram->enableAttributeArray(NORMAL_ARRAY_INDEX);
	m_shaderProgram->setAttributeBuffer(NORMAL_ARRAY_INDEX, GL_FLOAT, offsetof(Vertex, m_normal), 3 /* vec3 */, sizeof(Vertex));


	VAOWithBuffer->m_colorBufferObject.bind(); // now color buffer is active in vao

	// colors
	m_shaderProgram->enableAttributeArray(COLOR_ARRAY_INDEX);
	m_shaderProgram->setAttributeBuffer(COLOR_ARRAY_INDEX, GL_UNSIGNED_BYTE, 0, 4, 4 /* bytes = sizeof(char) */);

	// Release (unbind) all

	// Mind: you can release the buffer data objects (vbo and vboColors) before or after releasing vao. It does not
	//       matter, because the buffers are associated already with the attribute arrays.
	//       However, YOU MUST NOT release the index buffer (ebo) before releasing the vao, since this would remove
	//       the index buffer association with the vao and when binding the vao before rendering, the element buffer
	//       would not be known and a call to glDrawElements() crashes!
	VAOWithBuffer->m_vao.release();

	VAOWithBuffer->m_vertexBufferObject.release();
	VAOWithBuffer->m_colorBufferObject.release();
	VAOWithBuffer->m_indexBufferObject.release();

}

void OSMObject::generateOSMGeometry() {

	const VICUS::Project & p = project();


	if (p.m_drawingsOSM.empty())
		destroy();

	// displays progressDialog on first triangulation after import of a new DrawingOSM
	QProgressDialog * progress = nullptr;
	bool openDialog = false;

	for (const VICUS::DrawingOSM & drawing : p.m_drawingsOSM) {
		openDialog = openDialog || drawing.m_firstTriangulation;
		drawing.m_firstTriangulation = false;
	}

	if (openDialog) {
		progress = new QProgressDialog("Triangulation in Process.", QString(), 0, 0, nullptr);
		progress->setWindowTitle("Triangulation");
		progress->setWindowModality(Qt::WindowModal);
		progress->setCancelButton(nullptr);
		progress->setAutoClose(true);
		progress->open();
		// to keep progressbar and UI responsive
		QCoreApplication::processEvents();
	}

	// collecting all geometryData from Objects
	for (const VICUS::DrawingOSM & drawing : p.m_drawingsOSM) {
		QCoreApplication::processEvents();
		drawing.m_firstTriangulation = false;
		std::map<double, std::tuple<std::vector<VICUS::DrawingOSM::GeometryData *>, bool>> geometryDataWithLayer; // std::map sorts by key
		drawing.geometryData(geometryDataWithLayer);


		for (std::map<double, std::tuple<std::vector<VICUS::DrawingOSM::GeometryData *>, bool>>::iterator it = geometryDataWithLayer.begin(); it != geometryDataWithLayer.end(); ++it) {
			if (!std::get<1>(it->second)) continue;
			// to keep progressbar and UI responsive
			VAOWithBufferStruct* VAOWithBuffer;
			bool notInVector = true;

			for (int i = 0; i < m_VAOWithBuffers.size(); i++) {
				if (m_VAOWithBuffers[i] != nullptr && m_VAOWithBuffers[i]->m_layer == it->first) {
					m_VAOWithBuffers[i]->m_vao.destroy();
					m_VAOWithBuffers[i]->m_vertexBufferObject.destroy();
					m_VAOWithBuffers[i]->m_colorBufferObject.destroy();
					m_VAOWithBuffers[i]->m_indexBufferObject.destroy();
					delete(m_VAOWithBuffers[i]);
					m_VAOWithBuffers[i] = new VAOWithBufferStruct();
					VAOWithBuffer = m_VAOWithBuffers[i];
					notInVector = false;
					break;
				}
			}
			if (notInVector) {
				VAOWithBuffer = new VAOWithBufferStruct();
				m_VAOWithBuffers.push_back(VAOWithBuffer);
			}
			QCoreApplication::processEvents();
			VAOWithBuffer->m_layer = it->first;
			configureNewVAOWithBuffer(VAOWithBuffer);

			VAOWithBuffer->m_vertexBufferData.clear();
			VAOWithBuffer->m_colorBufferData.clear();
			VAOWithBuffer->m_indexBufferData.clear();
			VAOWithBuffer->m_vertexStartMap.clear();

			VAOWithBuffer->m_vertexBufferData.reserve(500000);
			VAOWithBuffer->m_colorBufferData.reserve(500000);
			VAOWithBuffer->m_indexBufferData.reserve(500000);

			unsigned int currentVertexIndex = 0;
			unsigned int currentElementIndex = 0;

			// adding geometry data to GeometryObject
			for (const auto& data : std::get<0>(geometryDataWithLayer[it->first])) {
				QCoreApplication::processEvents();
				if (data->m_extrudingPolygon) {
					for (const auto &multipolygon : data->m_multipolygons) {
						std::vector<IBKMK::Vector3D> areaPoints;
						for (unsigned int i = 1; i < multipolygon.m_outerPolyline.size(); i++) {
							IBKMK::Vector3D p = IBKMK::Vector3D(multipolygon.m_outerPolyline[i].m_x,
																multipolygon.m_outerPolyline[i].m_y,
																data->m_minHeight);
							QVector3D vec = drawing.m_rotationMatrix.toQuaternion() * QVector3D((float)p.m_x, (float)p.m_y, (float)p.m_z);
							vec += QVector3D((double)drawing.m_origin.m_x, (double)drawing.m_origin.m_y, (double)drawing.m_origin.m_z);
							areaPoints.push_back(IBKMK::Vector3D((double)vec.x(), (double)vec.y(), (double)vec.z()));
						}
						try {
							addPolygonExtrusion(areaPoints, data->m_height - data->m_minHeight, data->m_color, currentVertexIndex, currentElementIndex,
												VAOWithBuffer->m_vertexBufferData,
												VAOWithBuffer->m_colorBufferData,
												VAOWithBuffer->m_indexBufferData,
												&multipolygon.m_innerPolylines);
						}
						catch (const IBK::Exception& e) {
							// Handle exception (e.g., log error, skip this polygon, etc.)
							std::cerr << "Error in addPolygonExtrusion: " << e.what() << std::endl;
						}
					}
				} else {
					for (const VICUS::PlaneGeometry &plane : data->m_planeGeometry) {
						try {
							addPlane(plane.triangulationData(), data->m_color, currentVertexIndex, currentElementIndex,
									 VAOWithBuffer->m_vertexBufferData,
									 VAOWithBuffer->m_colorBufferData,
									 VAOWithBuffer->m_indexBufferData,
									 false);
							addPlane(plane.triangulationData(), data->m_color, currentVertexIndex, currentElementIndex,
									 VAOWithBuffer->m_vertexBufferData,
									 VAOWithBuffer->m_colorBufferData,
									 VAOWithBuffer->m_indexBufferData,
									 true);
						}
						catch (const IBK::Exception& e) {
							// Handle exception (e.g., log error, skip this plane, etc.)
							std::cerr << "Error in addPlane: " << e.what() << std::endl;
						}
					}
				}
			}
			VAOWithBuffer->m_transparentStartIndex = VAOWithBuffer->m_indexBufferData.size();
		}
	}

	if (progress) {
		progress->close();
		delete progress;
	}
}

void OSMObject::render(float zCamera) {
	if (m_buildingShader == nullptr) return;
	if (!project().m_drawingsOSM.empty() && !project().m_drawingsOSM.back().m_visible) return;
	if (abs(zCamera) < 1000) zCamera > 0 ? zCamera = 1000 : zCamera = -1000; // z needs to stay above a threshold. Value arbitrary, through observing in scene

	for(auto VAOWithBuffer : m_VAOWithBuffers) {
		m_buildingShader->shaderProgram()->setUniformValue(m_buildingShader->m_uniformIDs[4], (float)VAOWithBuffer->m_layer * zCamera / 20000/* value arbitrary */);
		// bind all buffers ("position", "normal" and "color" arrays)
		VAOWithBuffer->m_vao.bind();
		// now draw the geometry
		glDrawElements(GL_TRIANGLES, VAOWithBuffer->m_transparentStartIndex, GL_UNSIGNED_INT, nullptr);
		// release buffers again
		VAOWithBuffer->m_vao.release();
	}

	m_buildingShader->shaderProgram()->setUniformValue(m_buildingShader->m_uniformIDs[4], 0);
}

void OSMObject::updateBuffers() {
	for(auto VAOWithBuffer : m_VAOWithBuffers) {
		if (VAOWithBuffer->m_indexBufferData.empty())
			continue;

		// transfer data stored in m_vertexBufferData
		VAOWithBuffer->m_vertexBufferObject.bind();
		VAOWithBuffer->m_vertexBufferObject.allocate(VAOWithBuffer->m_vertexBufferData.data(), VAOWithBuffer->m_vertexBufferData.size()*sizeof(Vertex));
		VAOWithBuffer->m_vertexBufferObject.release();

		VAOWithBuffer->m_indexBufferObject.bind();
		VAOWithBuffer->m_indexBufferObject.allocate(VAOWithBuffer->m_indexBufferData.data(), VAOWithBuffer->m_indexBufferData.size()*sizeof(GLuint));
		VAOWithBuffer->m_indexBufferObject.release();

		if (VAOWithBuffer->m_colorBufferData.empty())
			continue;
		VAOWithBuffer->m_colorBufferObject.bind();
		// if color buffer size differs, do a full re-allocate : this expands/shrinks the memory on GPU when
		// new projects are loaded or objects are created/removed
		if ((unsigned int)VAOWithBuffer->m_colorBufferObject.size() != VAOWithBuffer->m_colorBufferData.size()*sizeof(ColorRGBA))
			VAOWithBuffer->m_colorBufferObject.allocate(VAOWithBuffer->m_colorBufferData.data(), VAOWithBuffer->m_colorBufferData.size()*sizeof(ColorRGBA) );
		else  {
			auto ptr = VAOWithBuffer->m_colorBufferObject.mapRange(0, VAOWithBuffer->m_colorBufferData.size() * sizeof(ColorRGBA),
																   QOpenGLBuffer::RangeInvalidateBuffer | QOpenGLBuffer::RangeWrite);
			std::memcpy(ptr, VAOWithBuffer->m_colorBufferData.data(),  VAOWithBuffer->m_colorBufferData.size()*sizeof(ColorRGBA));
			VAOWithBuffer->m_colorBufferObject.unmap();
		}
		VAOWithBuffer->m_colorBufferObject.release();
	}
}

}
