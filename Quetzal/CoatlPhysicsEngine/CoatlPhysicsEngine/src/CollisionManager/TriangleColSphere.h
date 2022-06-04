#pragma once
#include "../Shapes/Sphere.h"
#include "../Shapes/Triangles.h"
namespace CoatlPhysicsEngine {
	class TriangleColSphere
	{
	protected:
		static bool TrColSphere(S_P<Triangles> Tr, S_P<Sphere> Sph,
			glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1);
	public:
		TriangleColSphere();
		~TriangleColSphere();
	};
}
