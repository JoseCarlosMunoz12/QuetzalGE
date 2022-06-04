#include "TriangleColSphere.h"
using namespace CoatlPhysicsEngine;
bool TriangleColSphere::TrColSphere(S_P<Triangles> Tr, S_P<Sphere> Sph,
	glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
{
	float Dis = MATH::Distance_Tr_Pnt(Tr->GetSegments(Pos0, Rot1),Pos1,Pos0);
	float Rad = Sph->GetRadius();	
	return Rad >= Dis; 
}

TriangleColSphere::TriangleColSphere()
{

}

TriangleColSphere::~TriangleColSphere()
{

}
