#include "SphereColSphere.h"
using namespace CoatlPhysicsEngine;
SphereColSphere::SphereColSphere()
{
}

SphereColSphere::~SphereColSphere()
{
}

bool SphereColSphere::SphereSphere(S_P<Sphere> Sphere0, S_P<Sphere> Sphere1,
	glm::vec3 Pos0,
	glm::vec3 Pos1)
{
	float R_Total = Sphere0->GetRadius() + Sphere1->GetRadius();
	R_Total = R_Total * R_Total;
	glm::vec3 Vec_Total = Pos0 - Pos1;
	float Mid_Dis = glm::dot(Vec_Total,Vec_Total);
	return R_Total >= Mid_Dis;
}
