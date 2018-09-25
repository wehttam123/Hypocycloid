#define _USE_MATH_DEFINES
#include "Geometry.h"

#include <cmath>

Geometry::Geometry() {
	drawMode = GL_TRIANGLES;
	vao = 0;
	vertexBuffer = 0;
	colourBuffer = 0;
	modelMatrix = glm::mat4(1.f);
}

Geometry Geometry::makeCircle(float radius, float uInc) {

	Geometry circle;

	for (double u = 0.0; u <= 2.0 * M_PI; u += uInc) {
		circle.verts.push_back(radius * glm::vec3(cos(u), sin(u), 0));
		circle.colours.push_back(glm::vec3(0.f, 1.f, 0.f));
	}
	circle.drawMode = GL_LINE_STRIP;
	return circle;
}
