#include "CapsuleColSphere.h"
using namespace CoatlPhysicsEngine;

bool CapsuleColSphere::CapColSphere(S_P<Capsule> Cap0, S_P<Sphere> Sph0, glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
{

	float Sph_R = Sph0->GetRadius();
	float Cp_R = Cap0->GetRadius();

	glm::vec3 T = MATH::ClosestPoint_Seg(Cap0->GetSegment(Pos0, Rot1), Pos1);
	float DisSqr = glm::distance(Pos1, T);
	float R_Sqr = Sph_R + Cp_R;

	return R_Sqr > DisSqr;
}

CapsuleColSphere::CapsuleColSphere()
{
}
