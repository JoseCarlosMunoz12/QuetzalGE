#pragma once
#include "../Shapes/Capsule.h"
#include "../Shapes/Triangles.h"
namespace CoatlPhysicsEngine {
	class TriangleColCapsule
	{
	protected:
		static bool TrColCap(S_P<Triangles> Tr, S_P<Capsule> Cap,
			glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1);
	public:
		TriangleColCapsule();
		~TriangleColCapsule();
	};
}
