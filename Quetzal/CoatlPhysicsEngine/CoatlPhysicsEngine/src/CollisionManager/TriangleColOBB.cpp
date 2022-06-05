#include "TriangleColOBB.h"
using namespace CoatlPhysicsEngine;

bool TriangleColOBB::TriColOBB(S_P<Triangles> Tr, S_P<OBB> Obj,
	glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
{
	//Get Needed Info
	std::vector<glm::vec3> TrSeg = Tr->GetSegments(Pos0, Rot0);
	std::vector<glm::vec3> ObjSeg = Obj->GetSegments(Pos1, Rot1);	
	std::vector<glm::vec3> Obj_N = { glm::normalize(ObjSeg[1] - ObjSeg[0]),
	glm::normalize(ObjSeg[3] - ObjSeg[0]) ,
	glm::normalize(ObjSeg[4] - ObjSeg[0]) };
	//Check if Points are not in the plane
	C_Plane TrPlane(TrSeg);
	if (TrPlane.SameLocPl(ObjSeg))
	{
		return false;
	}
	// SAT Test
	
	return MATH::SATColCheck({ TrPlane.Normal }, Obj_N, TrSeg, ObjSeg);
}

TriangleColOBB::TriangleColOBB()
{
}

TriangleColOBB::~TriangleColOBB()
{
}
