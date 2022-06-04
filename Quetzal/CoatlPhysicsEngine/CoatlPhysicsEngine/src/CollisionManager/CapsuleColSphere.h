#pragma once
#include "../Shapes/Capsule.h"
#include "../Shapes/Sphere.h"

namespace CoatlPhysicsEngine{
class CapsuleColSphere
{
protected:
	static bool CapColSphere(S_P<Capsule> Cap0,S_P<Sphere> Sph0,
		glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1);
public:
	CapsuleColSphere();
};
}
