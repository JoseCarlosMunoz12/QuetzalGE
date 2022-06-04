#include "TriangleColTriangle.h"

bool TriangleColTriangle::TrColTr(S_P<Triangles> Tr0, S_P<Triangles> Tr1,
	glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
{
	//Check Normal vectors  if they are parrallel
	std::vector<glm::vec3> Tr0Seg = Tr0->GetSegments(Pos0, Rot0);
	std::vector<glm::vec3> Tr1Seg = Tr1->GetSegments(Pos1, Rot1);
	//make And Check planes are on the same side
	C_Plane Tr0_P(Tr0Seg);
	if (Tr0_P.SameLocPl(Tr1Seg))
		return false;
	C_Plane Tr1_P(Tr1Seg);
	if (Tr1_P.SameLocPl(Tr0Seg))
			return false;
	
	//Find Plane Intersection normal and project
	glm::vec3 PlSegDir = glm::cross(Tr0_P.Normal, Tr1_P.Normal);	
	if (MATH::ProjColl({ glm::vec3(0.f),PlSegDir }, Tr0Seg, Tr1Seg))
		return false;
	return true;
}

TriangleColTriangle::TriangleColTriangle()
{
}

TriangleColTriangle::~TriangleColTriangle()
{
}
