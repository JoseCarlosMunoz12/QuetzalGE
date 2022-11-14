#pragma once
#include "../Bodies/Bodies.h"
#include "../Bodies/Bod_Collection.h"
namespace CoatlPhysicsEngine {
	class Contact
	{
	public:
		S_P<Bodies> BodA;
		S_P<Bodies> BodB;
		glm::vec3 ContactPoint;
		glm::vec3 Dir;
		float Pen;
		float Friction;
		float Restitution;
		float dt0;
		float dt1;
	};
}
