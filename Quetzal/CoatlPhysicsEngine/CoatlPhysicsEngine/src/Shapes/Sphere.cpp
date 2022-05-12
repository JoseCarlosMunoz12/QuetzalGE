#include "Sphere.h"
using namespace CoatlPhysicsEngine;
Sphere::Sphere(float SetRadius)
	:ColShapes()
{
	this->Radius = SetRadius;
}

Sphere::~Sphere()
{
}

float Sphere::GetRadius()
{
	return this->Radius;
}

void Sphere::SetRadius(float NewR)
{
	this->Radius = NewR;
}

glm::vec3 Sphere::Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle)
{
	glm::vec3 Norm = glm::normalize(Dir);
	return pos + (this->Radius) * Norm;
}

glm::vec3 Sphere::EPA_Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle)
{
	return pos;
}

std::vector<glm::vec3> Sphere::GetVertices(glm::vec3 pos, glm::quat quatAngle)
{
	std::vector<glm::vec3> Temp;
	Temp.push_back(pos);
	return Temp;
}

glm::mat3 Sphere::GetInertia(float mass)
{
	float mid = 2.5 / 5.f * Radius * Radius;
	glm::vec3 col0 = glm::vec3(mid, 0.f, 0.f);
	glm::vec3 col1 = glm::vec3(0.f,mid, 0.f);
	glm::vec3 col2 = glm::vec3(0.f, 0.f, mid);
	return mass * glm::mat3(col0, col1, col2);
}
