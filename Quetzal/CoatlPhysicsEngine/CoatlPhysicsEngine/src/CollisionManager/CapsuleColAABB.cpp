#include "CapsuleColAABB.h"
using namespace CoatlPhysicsEngine;

bool CapsuleColAABB::CapColAABB(S_P<Capsule> Cap, S_P<AABB_Obj> Obj,
	glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
{
	std::vector<int> ID = Obj->GetSegmentsID();
	int Size = ID.size() / 2;
	std::vector<glm::vec3> Points = Obj->GetSegs(Pos1, Rot1);
	float R = Cap->GetRadius();
	glm::vec3 PosA;
	glm::vec3 PosB;
	MATH::ClosestSeg_Seg(Cap->GetSegment(Pos0, Rot1), { Points[ID[0]], Points[ID[1]] },PosA,PosB);
	glm::vec3 Cls_Pnt = Pos0;
	float TempDis = glm::distance(PosA, PosB);
	float Dis;
	for (int ii = 0; ii < Size; ii++)
	{
		int JJ = ii * 2;
		int KK = JJ + 1;
		MATH::ClosestSeg_Seg(Cap->GetSegment(Pos0, Rot0), { Points[ID[JJ]], Points[ID[KK]] }, PosA, PosB);
		Dis = glm::distance(PosA, PosB);
		if (Dis < TempDis)
		{
			Dis = TempDis;
			Cls_Pnt = Pos0;
		}
	}
	glm::vec3 ClsPoint = Obj->GetClosesPoint(Cls_Pnt,Pos1, Rot1);
	float Rad = Cap->GetRadius();
	float Dot = glm::distance(ClsPoint, Cls_Pnt);
	return  Dot <= Rad;

}

CapsuleColAABB::CapsuleColAABB()
{
}

CapsuleColAABB::~CapsuleColAABB()
{
}
