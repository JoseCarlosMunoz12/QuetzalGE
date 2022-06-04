#pragma once
#include "../Shapes/Triangles.h"
#include "../Shapes/SimpleShapes.h"
namespace CoatlPhysicsEngine {
	class TriangleColTriangle
	{
	protected:
	public:
		TriangleColTriangle();
		~TriangleColTriangle();
		static bool TrColTr(S_P<Triangles> Tr0, S_P<Triangles> Tr1,
			glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1);
	};
}
