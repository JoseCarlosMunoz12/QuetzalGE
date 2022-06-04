#pragma once

#include "../Shapes/AABB_Obj.h"
#include "../Shapes/Capsule.h"

namespace CoatlPhysicsEngine {
	class CapsuleColAABB
	{
	private:
	protected:
		static bool CapColAABB(S_P<Capsule> Cap, S_P<AABB_Obj> Obj, 
			glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1);
	public:
		CapsuleColAABB();
		~CapsuleColAABB();
	};
}