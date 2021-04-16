#pragma once
#include <glm.hpp>
#include <iostream>
#include <string>
#include <vector>
//Universal Data Structures

//Data Structure for static models
struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
	glm::vec3 normal;
};
class Nodes
{
private:
	//Children
	std::vector<std::shared_ptr<Nodes>> Children;
	//basic information
	glm::vec3 Position;
	glm::vec3 Offset;
	glm::vec3 Scale;
	glm::quat Rot;
};
//Data Structures for dynamic models
struct AnimVertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
	glm::vec3 normal;
	glm::ivec4 MatId;
	glm::vec4 Weights;
};
