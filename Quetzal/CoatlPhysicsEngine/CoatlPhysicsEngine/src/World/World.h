#pragma once
#include "../define.h"

namespace CoatlPhysicsEngine {
	class COATL_API World
	{
	private:
	public:
		World();
		~World();
		void UpdateRun(double dt);
	};
}