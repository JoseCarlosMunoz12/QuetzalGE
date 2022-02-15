#pragma once
#include "Body.h"
namespace CoatlPhysicsEngine {

	class COATL_API Capsule : public Body
	{
	private:
		Vec3D Seg0;
		Vec3D Seg1;
		double Radius;
	public:
	};
}

