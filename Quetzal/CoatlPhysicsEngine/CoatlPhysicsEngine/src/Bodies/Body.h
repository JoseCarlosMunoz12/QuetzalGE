#pragma once
#include "../define.h"
#include "../Maths/Matrix.h"
#include "../Maths/Vectors.h"
namespace CoatlPhysicsEngine {
	class COATL_API Body
	{
	protected:
		Matrix3x3 MassInv;
		Matrix3x3 InertiaInv;
		Vec3D Position;
		Quat Rotation;
	public:
		Body();
	};
}

