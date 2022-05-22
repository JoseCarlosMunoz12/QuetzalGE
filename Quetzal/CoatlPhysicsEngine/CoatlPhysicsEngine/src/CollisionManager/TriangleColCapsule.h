#pragma once
#include "../Shapes/Capsule.h"
#include "../Shapes/Triangles.h"
namespace CoatlPhysicsEngine {
	class TriangleColCapsule
	{
	protected:
		static bool TrColCap(Triangles Tr, Capsule Cap);
	public:
		TriangleColCapsule();
		~TriangleColCapsule();
	};
}
