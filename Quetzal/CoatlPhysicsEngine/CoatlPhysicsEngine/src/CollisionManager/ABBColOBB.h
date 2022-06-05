#pragma once
#include "../Shapes/OBB.h"
#include "../Shapes/AABB_Obj.h"
namespace CoatlPhysicsEngine {
	class ABBColOBB
	{
	protected:
		static bool ABBColsOBB(S_P<AABB_Obj> ABB, S_P<OBB> Obj,
			glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1);
	public:
		ABBColOBB();
		~ABBColOBB();
	};
}
