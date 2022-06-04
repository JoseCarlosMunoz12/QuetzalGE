#pragma once
#include "../Shapes/Sphere.h"
#include "../Shapes/AABB_Obj.h"
namespace CoatlPhysicsEngine {
	class SphereColAABB
	{
	public:
		SphereColAABB();
		~SphereColAABB();
		static bool SphereColsAABB(S_P<Sphere> Sph0, S_P<AABB_Obj> Obj0,
			glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1);
	};
}
