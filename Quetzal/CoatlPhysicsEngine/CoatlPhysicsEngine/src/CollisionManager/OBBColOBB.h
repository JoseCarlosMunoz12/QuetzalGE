#pragma once
#include "../Shapes/OBB.h"
namespace CoatlPhysicsEngine {
	class OBBColOBB
	{
	protected:
		static bool OBBCol(S_P<OBB> Ob0, S_P<OBB> Ob1,
			glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1);
	public:
		OBBColOBB();
		~OBBColOBB();
	};
}