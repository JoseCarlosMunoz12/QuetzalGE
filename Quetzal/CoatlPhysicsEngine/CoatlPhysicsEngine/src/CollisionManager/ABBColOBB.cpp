#include "ABBColOBB.h"
using namespace CoatlPhysicsEngine;
bool ABBColOBB::ABBColsOBB(S_P<AABB_Obj> ABB, S_P<OBB> Obj,
	glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
{
	std::vector<glm::vec3> ABB_Segs = ABB->GetSegs(Pos0, Rot0);
	std::vector<glm::vec3> Obj_Segs = Obj->GetSegments(Pos1, Rot1);

	std::vector<glm::vec3> ABB_N = { glm::normalize(ABB_Segs[1] - ABB_Segs[0]),
		glm::normalize(ABB_Segs[3] - ABB_Segs[0]) ,
		glm::normalize(ABB_Segs[4] - ABB_Segs[0]) };
	std::vector<glm::vec3> Obj_N = { glm::normalize(Obj_Segs[1] - Obj_Segs[0]),
		glm::normalize(Obj_Segs[3] - Obj_Segs[0]) ,
		glm::normalize(Obj_Segs[4] - Obj_Segs[0]) };
	return MATH::SATColCheck(ABB_N, Obj_N, ABB_Segs, Obj_Segs);
}

ABBColOBB::ABBColOBB()
{
}

ABBColOBB::~ABBColOBB()
{
}
