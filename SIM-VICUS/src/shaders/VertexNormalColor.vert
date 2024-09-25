#version 330

// GLSL version 3.3
// vertex shader

layout(location = 0) in vec3 position; // input:  attribute with index '0' with 3 elements per vertex (coordinates)
layout(location = 1) in vec3 normal;   // input:  attribute with index '1' with 3 elements per vertex (normal)
layout(location = 2) in vec4 color;    // input:  attribute with index '2' with 4 elements (=rgba) per vertex

out vec4 fragColor;                    // output: fragment color
out vec3 fragNormal;                   // output: fragment normal vector
out vec3 fragPos;                      // output: fragment position in world coords

uniform mat4 worldToView;              // parameter: the world-to-view matrix
uniform float zAltering = 0.0;	       // parameter:

void main() {
  // Mind multiplication order for matrixes
  gl_Position = worldToView * vec4(position, 1.0);
  gl_Position.z -= zAltering;
  fragPos = position;
  fragColor = color;
  fragNormal = normal; // do not rotate normals - light position is also given in world coordinates
  // TODO : add test for alpha value in color, if less than 0.1, discard vertex and thus triangle
}


