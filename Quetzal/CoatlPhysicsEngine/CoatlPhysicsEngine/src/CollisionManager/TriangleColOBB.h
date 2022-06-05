#pragma once
#include "../Shapes/OBB.h"
#include "../Shapes/Triangles.h"
#include "../Shapes/SimpleShapes.h"
namespace CoatlPhysicsEngine {
	class TriangleColOBB
	{
	protected:
		static bool TriColOBB(S_P<Triangles> Tr, S_P<OBB> Obj,
			glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1);
	public:
		TriangleColOBB();
		~TriangleColOBB();
	};
}