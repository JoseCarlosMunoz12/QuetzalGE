#pragma once
#include <glm.hpp>
#include <iostream>
#include <string>
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
	glm::vec3 normal;
};
struct AnimVertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
	glm::vec3 normal;
	glm::ivec4 MatId;
	glm::vec4 Weights;
};