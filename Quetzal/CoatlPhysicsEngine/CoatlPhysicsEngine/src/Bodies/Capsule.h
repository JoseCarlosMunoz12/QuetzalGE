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
		Capsule(double initRadius,Vec3D initSeg0, Vec3D initSeg1, Vec3D initPos, Quat initRot);
	};
}

