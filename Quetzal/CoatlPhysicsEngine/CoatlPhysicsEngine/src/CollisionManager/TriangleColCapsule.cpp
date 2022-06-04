#include "TriangleColCapsule.h"
#include <algorithm>
using namespace CoatlPhysicsEngine;

bool TriangleColCapsule::TrColCap(S_P<Triangles> Tr, S_P<Capsule> Cap,
	glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
{
	std::vector<glm::vec3> TrPoints = Tr->GetSegments(Pos0, Rot0);
	std::vector<glm::vec3> CapPoints = Cap->GetSegment(Pos1, Rot1);
	float R = Cap->GetRadius();
	std::vector<float> DisVals;
	DisVals.push_back(MATH::Distance_Seg({ TrPoints[0],TrPoints[1] }, Pos0, CapPoints));
	DisVals.push_back(MATH::Distance_Seg({ TrPoints[1],TrPoints[2] }, Pos0, CapPoints));
	DisVals.push_back(MATH::Distance_Seg({ TrPoints[2],TrPoints[0] }, Pos0, CapPoints));
	DisVals.push_back(MATH::Distance_Tr_Pnt(TrPoints, Pos0, CapPoints[0]));
	DisVals.push_back(MATH::Distance_Tr_Pnt(TrPoints, Pos0, CapPoints[1]));
	
	float MinVal = *std::min_element(DisVals.begin(), DisVals.end());
	return  R > MinVal;
}

TriangleColCapsule::TriangleColCapsule()
{
}

TriangleColCapsule::~TriangleColCapsule()
{
}
