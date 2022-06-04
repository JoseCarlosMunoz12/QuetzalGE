#include "SphereColAABB.h"
using namespace CoatlPhysicsEngine;

SphereColAABB::SphereColAABB()
{
}

SphereColAABB::~SphereColAABB()
{
}

bool SphereColAABB::SphereColsAABB(S_P<Sphere> Sph0, S_P<AABB_Obj> Obj0,
	glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
{	
	glm::vec3 ClsPoint = Obj0->GetClosesPoint(Pos0, Pos1, Rot1);
	float Rad = Sph0->GetRadius();
	glm::vec3 V = ClsPoint - Pos0;
	float Dot = glm::dot(V,V);
	Rad = Rad * Rad;
	return  Dot <= Rad;
}
