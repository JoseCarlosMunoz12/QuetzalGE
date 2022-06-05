#pragma once
#include "../Contact.h"
#include "../../Shapes/Sphere.h"
namespace CoatlPhysicsEngine {
	class SphereRelSphere
	{
	protected:
		static std::vector<std::shared_ptr<Contact>> SphRelSph(Sphere Sph0,Sphere Sph1);
	public:
		SphereRelSphere();
		~SphereRelSphere();
	};
}