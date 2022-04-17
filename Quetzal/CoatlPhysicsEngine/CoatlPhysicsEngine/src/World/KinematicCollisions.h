#pragma once
#include "../define.h"
#include "../Body/Body.h"
#include "StaticCollisions.h"

namespace CoatlPhysicsEngine {
	class COATL_API KinematicCollisions : public StaticCollisions
	{
	private:
		
	public:
		void UpdateBodies(double dt);
	};
}