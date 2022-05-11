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

#include "../Maths/Maths.h"
#include "../Physics/Particle.h"
namespace CoatlPhysicsEngine
{
	class COATL_API ColShapes
	{
	public:
		ColShapes();
		virtual ~ColShapes();
		virtual glm::vec3 Support(glm::vec3 Dir);
		virtual glm::vec3 EPA_Support(glm::vec3 Dir);
		virtual std::vector<glm::vec3> GetVertices();
		virtual std::vector<glm::vec3> GetNormals();
	};
}