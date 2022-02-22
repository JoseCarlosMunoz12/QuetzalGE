#pragma once
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