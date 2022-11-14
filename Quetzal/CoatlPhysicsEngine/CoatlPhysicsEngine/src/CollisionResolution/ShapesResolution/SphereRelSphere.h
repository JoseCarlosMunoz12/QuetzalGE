#pragma once
#include "../Contact.h"
#include "../../Shapes/Sphere.h"
namespace CoatlPhysicsEngine {
	class SphereRelSphere
	{
	protected:
		static Vec_SH<Contact> SphRelSph(Sphere Sph0,Sphere Sph1);
	public:
		SphereRelSphere();
		~SphereRelSphere();
	};
}