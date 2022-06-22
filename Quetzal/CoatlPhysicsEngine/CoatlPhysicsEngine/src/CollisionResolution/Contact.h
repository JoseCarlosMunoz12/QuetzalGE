#pragma once
#include <string>
#include <iostream>
#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\type_ptr.hpp>
#include <vector>
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
