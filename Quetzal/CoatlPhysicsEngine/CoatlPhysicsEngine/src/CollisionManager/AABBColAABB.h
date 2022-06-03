#pragma once
#include "../Shapes/AABB_Obj.h"
namespace CoatlPhysicsEngine {

	class AABBColAABB
	{
	protected:
		static bool AABBAABB(S_P<AABB_Obj> Obj0, S_P<AABB_Obj> Obj1,
			glm::vec3 Pos0, glm::vec3 Pos1);
	public:
		AABBColAABB();
		~AABBColAABB();		
	};

}