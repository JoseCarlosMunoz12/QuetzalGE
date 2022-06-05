#pragma once
#include "../Shapes/Capsule.h"
#include "../Shapes/OBB.h"
namespace CoatlPhysicsEngine {
	class CapsuleColOBB
	{
	protected:
		static bool CapColOBB(S_P<Capsule> Cap, S_P<OBB> Obj,
			glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1);
	public:
		CapsuleColOBB();
		~CapsuleColOBB();
	};
}