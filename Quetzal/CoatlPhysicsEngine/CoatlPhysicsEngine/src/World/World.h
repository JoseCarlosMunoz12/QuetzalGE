#pragma once
#include "../define.h"
#include "DynamicCollisions.h"

namespace CoatlPhysicsEngine {
	class COATL_API World
	{
	private:
		Vec3D Gravity;
		S_P<StaticCollisions> StaticWorld;
		S_P<KinematicCollisions> KinWorld;
		S_P<DynamicCollisions> DynWorld;
	public:
		World();
		~World();
		void UpdateRun(double dt);
		void SetGravity(Vec3D initGrav);

		void CreateStaticWorld();
		void CreateKinematicWorld();
		void DynamicWorld();

		void DeleteStatic();
		void DeleteKinematic();
		void DeleteDynamic();

		S_P<StaticCollisions> GetStaticWorld();
		S_P<KinematicCollisions> GetKinematicWorld();
		S_P<DynamicCollisions> GetDynamicWorld();
	};
}