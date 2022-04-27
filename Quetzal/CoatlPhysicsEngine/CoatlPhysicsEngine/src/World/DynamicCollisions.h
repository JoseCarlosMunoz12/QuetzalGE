#pragma once
#include "../define.h"
#include "../Body/Body.h"
#include "KinematicCollisions.h"

namespace CoatlPhysicsEngine {
	class COATL_API DynamicCollisions : public KinematicCollisions
	{
	private:
		const double EPSILON = 0.0001;
		S_P<CollisionManager> ColMan;
		bool BinaryCollisionDetection(S_P<Body> Bod0, S_P<Body> Bod1,double t0, double t1, double& newDt);
	public:
		DynamicCollisions();
		void UpdateBodies(S_P<KinematicCollisions> Kin, S_P<StaticCollisions> Static, double dt);
	};
}
