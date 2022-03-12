#pragma once
#include "../Bodies/Capsule.h"
#include "../Bodies/BB.h"
#include "../Bodies/Sphere.h"
namespace CoatlPhysicsEngine {
	class COATL_API CollisionManager
	{
	private:
	public:
		bool CheckCollideBB(BB R,BB N);
		bool CheckCollideCC(Capsule R, Capsule N);
		bool CheckCollideSS(Sphere R, Sphere N);
		bool CheckCollideBC(BB R, Capsule N);
		bool CheckCollideBS(BB R, Sphere N);
		bool CheckCollideCS(Capsule R, Sphere N);
	};
}