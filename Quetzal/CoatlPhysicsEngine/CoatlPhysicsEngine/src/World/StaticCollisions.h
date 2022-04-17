#pragma once
#include "../define.h"
#include "../Body/Body.h"
#include "../CollisionManager/CollisionManager.h"

namespace CoatlPhysicsEngine {
	class COATL_API StaticCollisions
	{
	protected:
		Vec_SH<Body> Bodies;
	public:
		StaticCollisions();
		~StaticCollisions();
		void AddBody(S_P<Body> initBody);
		Vec_SH<Body> GetBodies();
	};
}