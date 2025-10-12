#include <array>
#include <shape.hpp>
#include <glad.h>

std::array<float, 6> shape::triangle::getVertices()
{
	auto vertices = std::array<float, 6>();
	// Line 1
	vertices[0] = first.x;
	vertices[1] = first.y;
	// Line 2
	vertices[2] = second.x;
	vertices[3] = second.y;
	// Line 3
	vertices[4] = third.x;
	vertices[5] = third.y;
	return vertices;
}

std::array<unsigned int, 3> shape::triangle::getIndices()
{
	auto indices = std::array<unsigned int, 3>();
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	return indices;
}

void shape::triangle::draw(unsigned int programId, unsigned int index)
{
	auto uniformId = glGetUniformLocation(programId, "Color");
	if (uniformId == -1)
	{
		return;
	}

	glUniform4f(uniformId, this->color[0], this->color[1], this->color[2], this->color[3]);
	glDrawElementsBaseVertex(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, 0, index * 3);
}

std::array<float, 8> shape::plane::getVertices()
{
	auto vertices = std::array<float, 8>();
	// Line 1
	vertices[0] = lowerLeft.x;
	vertices[1] = lowerLeft.y;
	// Line 2
	vertices[2] = lowerRight.x;
	vertices[3] = lowerRight.y;
	// Line 3
	vertices[4] = upperLeft.x;
	vertices[5] = upperLeft.y;
	// Line 3
	vertices[6] = upperRight.x;
	vertices[7] = upperRight.y;
	return vertices;
}

std::array<unsigned int, 6> shape::plane::getIndices()
{
	auto indices = std::array<unsigned int, 6>();
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 1;
	return indices;
}

void shape::plane::draw(unsigned int programId, unsigned int index)
{
	auto uniformId = glGetUniformLocation(programId, "Color");
	if (uniformId == -1)
	{
		return;
	}

	glUniform4f(uniformId, this->color[0], this->color[1], this->color[2], this->color[3]);
	glad_glLineWidth(2.0f);
	// index * 4 correspond to the shift in the vertices position, not indices themselves.
	glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, index * 4);
}