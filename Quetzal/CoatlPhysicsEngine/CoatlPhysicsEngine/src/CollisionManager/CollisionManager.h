#pragma once
#include "../Bodies/Capsule.h"
#include "../Bodies/BB.h"
#include "../Bodies/Sphere.h"
namespace CoatlPhysicsEngine {
	class CollisionManager
	{
	private:
	public:
		CollisionManager();
		~CollisionManager();
		template<typename _T, typename _N>
		bool CheckCollide(_T R, _T N);
	};
}