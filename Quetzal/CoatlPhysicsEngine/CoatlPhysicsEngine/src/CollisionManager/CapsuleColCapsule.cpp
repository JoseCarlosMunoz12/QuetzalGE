#include "CapsuleColCapsule.h"
using namespace CoatlPhysicsEngine;

bool CapsuleColCapsule::CapsuleCols(S_P<Capsule> Cap0, S_P<Capsule> Cap1,
	glm::vec3 Pos0, glm::quat Rot0,
	glm::vec3 Pos1, glm::quat Rot1)
{
	float Cap0R = Cap0->GetRadius();
	float Cap1R = Cap1->GetRadius();
	float RDis = Cap0R + Cap1R;

	float Dis = Cap0->Distance(Cap1->GetSegment(Pos1, Rot1),Pos0, Rot0);

	return RDis > Dis;
}

CapsuleColCapsule::CapsuleColCapsule()
{
}
