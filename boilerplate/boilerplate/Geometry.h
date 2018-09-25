#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <vector>

class Geometry {

public:
	Geometry();

	GLuint drawMode;

	GLuint vao;
	GLuint vertexBuffer;
	GLuint colourBuffer;
	std::vector<glm::vec3> verts;
	std::vector<glm::vec3> colours;
	glm::mat4 modelMatrix;

	static Geometry makeCircle(float radius, float uInc);
};

