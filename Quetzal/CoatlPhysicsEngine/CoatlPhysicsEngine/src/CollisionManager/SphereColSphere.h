#pragma once
#include "../Shapes/Sphere.h"
namespace CoatlPhysicsEngine {
	class SphereColSphere
	{
	protected:
		static bool SphereSphere(S_P<Sphere> Sphere0, S_P<Sphere> Sphere1,
			glm::vec3 Pos0, 
			glm::vec3 Pos1);
	public:
		SphereColSphere();
		~SphereColSphere();
	};
}
