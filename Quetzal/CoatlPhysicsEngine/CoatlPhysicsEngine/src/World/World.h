#pragma once
#include "../define.h"
#include "DynamicCollisions.h"

namespace CoatlPhysicsEngine {
	class COATL_API World
	{
	private:
		S_P<StaticCollisions> StaticWorld;
		S_P<KinematicCollisions> KinWorld;
		S_P<DynamicCollisions> DynWorld;
	public:
		World();
		~World();
		void UpdateRun(double dt);
	};
}