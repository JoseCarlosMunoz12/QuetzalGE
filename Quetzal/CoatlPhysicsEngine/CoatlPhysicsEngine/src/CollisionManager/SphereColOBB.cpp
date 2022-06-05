#include "SphereColOBB.h"
using namespace CoatlPhysicsEngine;

bool SphereColOBB::SphColOBB(S_P<Sphere> Sph, S_P<OBB> Obj,
	glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
{
	glm::vec3 ClsPoint = Obj->GetClosestPoint(Pos0, Pos1, Rot1);
	float Rad = Sph->GetRadius();
	glm::vec3 V = ClsPoint - Pos0;
	float Dot = glm::dot(V, V);
	Rad = Rad * Rad;
	return Dot <= Rad;
}

SphereColOBB::SphereColOBB()
{
}

SphereColOBB::~SphereColOBB()
{
}
