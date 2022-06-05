#pragma once
#include "../Shapes/Sphere.h"
#include "../Shapes/OBB.h"
namespace CoatlPhysicsEngine {
	class SphereColOBB
	{
	protected:
		static bool SphColOBB(S_P<Sphere> Sph, S_P<OBB> Obj,
			glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1);
	public:
		SphereColOBB();
		~SphereColOBB();
	};

}