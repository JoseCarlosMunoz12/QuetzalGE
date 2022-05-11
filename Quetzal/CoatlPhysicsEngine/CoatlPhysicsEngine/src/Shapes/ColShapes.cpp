#include "ColShapes.h"
using namespace CoatlPhysicsEngine;

ColShapes::ColShapes()
{

}

ColShapes::~ColShapes()
{
}

glm::vec3 ColShapes::Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle)
{
	return glm::vec3(0.f);
}

glm::vec3 ColShapes::EPA_Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle)
{
	return glm::vec3();
}

std::vector<glm::vec3> ColShapes::GetVertices(glm::vec3 pos, glm::quat quatAngle)
{
	return std::vector<glm::vec3>();
}

std::vector<glm::vec3> ColShapes::GetNormals(glm::vec3 pos, glm::quat quatAngle)
{
	return std::vector<glm::vec3>();
}
