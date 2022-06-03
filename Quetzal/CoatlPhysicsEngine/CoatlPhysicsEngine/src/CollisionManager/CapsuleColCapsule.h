#pragma once
#include "../Shapes/Capsule.h"
namespace CoatlPhysicsEngine {
	class CapsuleColCapsule
	{
	protected:
		static bool CapsuleCols(S_P<Capsule> Cap0, S_P<Capsule> Cap1,
			glm::vec3 Pos0, glm::quat Rot0,
			glm::vec3 Pos1, glm::quat Rot1);
	public:
		CapsuleColCapsule();
	};
}
