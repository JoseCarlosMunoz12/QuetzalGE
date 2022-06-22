#pragma once
#include "../Contact.h"
#include "../../Shapes/Sphere.h"
namespace CoatlPhysicsEngine {
	class SphereRelSphere
	{
	protected:
		static Vec_SH<Contact> SphRelSph(S_P<Sphere> Sph0,S_P<Sphere> Sph1);
	public:
		SphereRelSphere();
		~SphereRelSphere();
	};
}