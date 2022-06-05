#pragma once
#include <algorithm>
#include "../Shapes/Triangles.h"
#include "../Shapes/AABB_Obj.h"
#include "../Shapes/SimpleShapes.h"
namespace CoatlPhysicsEngine {
	class TriangleColAABB
	{
	private:
		static bool PlaneABB(Plane Pl, S_P<AABB_Obj> Obj);
	protected:
		static bool TrColAABB(S_P<Triangles> Tr, S_P<AABB_Obj> AABB,
			glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1);
	public:
		TriangleColAABB();
		~TriangleColAABB();
	};
}
