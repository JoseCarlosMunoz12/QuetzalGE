#pragma once
#include "../define.h"
#include "../Body/Body.h"
#include "KinematicCollisions.h"

namespace CoatlPhysicsEngine {
	class COATL_API DynamicCollisions : public KinematicCollisions
	{
	private:

	public:
		void UpdateBodies(S_P<KinematicCollisions> Kin, S_P<StaticCollisions> Static, double dt);
	};
}
