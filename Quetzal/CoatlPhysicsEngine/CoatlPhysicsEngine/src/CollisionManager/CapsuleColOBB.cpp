#include "CapsuleColOBB.h"
using namespace CoatlPhysicsEngine;

bool CapsuleColOBB::CapColOBB(S_P<Capsule> Cap, S_P<OBB> Obj,
	glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
{
	std::vector<int> Ind = { 0,1,1,2,2,3,3,0,
		4,5,5,6,6,7,7,4,
		0,4,1,5,2,6,3,7 };
	std::vector<glm::vec3> Points = Obj->GetSegments(Pos1, Rot1);
	float R = Cap->GetRadius();
	for (int ii = 0; ii < 12; ii++)
	{
		int JJ = ii * 2;
		int KK = JJ + 1;
		float Dis = MATH::Distance_Seg(Cap->GetSegment(Pos0, Rot1), {Points[Ind[JJ]] ,Points[Ind[KK]] });
		if (R > Dis)
		{	
			return true;
		}
	}
	return false;
}

CapsuleColOBB::CapsuleColOBB()
{
}

CapsuleColOBB::~CapsuleColOBB()
{
}
