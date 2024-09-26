#ifndef VIC3DOSMOBJECT_H
#define VIC3DOSMOBJECT_H

#include <Vic3DOpaqueGeometryObject.h>
#include <memory>

namespace Vic3D {

class ShaderProgram;

class OSMObject {
public:
	OSMObject();

	struct VAOWithBufferStruct {
		/*! Vertex buffer in CPU memory, holds data of all vertices (coords and normals). */
		std::vector<Vertex>			m_vertexBufferData;
		/*! Color buffer in CPU memory, holds colors of all vertices (same size as m_vertexBufferData). */
		std::vector<ColorRGBA>		m_colorBufferData;
		/*! Index buffer on CPU memory. */
		std::vector<GLuint>			m_indexBufferData;

		// We have one set of buffers, the vertexBufferObject holds all vertexes of opaque
		// and transparent planes alike. Same applies to the color and index buffer.
		// The variable m_transparentStartIndex holds the index position where the
		// transparent planes start.
		GLsizei						m_transparentStartIndex = 0;


		/*! Maps unique surface/node ID to vertex start index in m_vertexBufferData. */
		std::map<unsigned int, unsigned int>	m_vertexStartMap;

		/*! VertexArrayObject, references the vertex, color and index buffers. */
		QOpenGLVertexArrayObject	m_vao;

		/*! Handle for vertex buffer on GPU memory. */
		QOpenGLBuffer				m_vertexBufferObject;
		/*! Handle for color buffer on GPU memory. */
		QOpenGLBuffer				m_colorBufferObject;
		/*! Handle for index buffer on GPU memory */
		QOpenGLBuffer				m_indexBufferObject;

		double						m_layer;
	};

	/*! The function is called during OpenGL initialization, where the OpenGL context is current. */
	void create(ShaderProgram * shaderProgram);
	void destroy();

	void configureNewVAOWithBuffer(VAOWithBufferStruct * VAOWithBuffer);

	void generateOSMGeometry();

	/*! Binds the buffer and paints. */
	void render(float z);

	void updateBuffers();

	/*! Shader program, that the osm objects are painted with. */
	QOpenGLShaderProgram		*m_shaderProgram = nullptr;
	ShaderProgram				*m_buildingShader = nullptr;

	 //std::vector<std::unique_ptr<OpaqueGeometryObject>>	m_drawingOSMGeometryObjects;
	 //std::vector<double>									m_layers;

	std::vector<VAOWithBufferStruct*>			m_VAOWithBuffers;

};

}

#endif // VIC3DOSMOBJECT_H
