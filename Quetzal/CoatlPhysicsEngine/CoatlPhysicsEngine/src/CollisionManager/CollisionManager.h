#pragma once
#include "GJK.h"
#include "../Shape/Capsule.h"
#include "../Shape/BB.h"
#include "../Shape/Sphere.h"
#include "../Shape/Convex.h"
namespace CoatlPhysicsEngine {
	class COATL_API CollisionManager : public GJK
	{
	private:
	public:
		CollisionManager();
		~CollisionManager();
		//
		bool CheckCollide(Shape R, Shape N);
		//
		bool CheckCollideBB(BB R,BB N);
		bool CheckCollideCC(Capsule R, Capsule N);
		bool CheckCollideSS(Sphere R, Sphere N);
		bool CheckCollideCvCv(Convex R, Convex N);
		//
		bool CheckCollideBC(BB R, Capsule N);
		bool CheckCollideBS(BB R, Sphere N);
		bool CheckCollisdBCv(BB r, Convex);
		bool CheckCollideCS(Capsule R, Sphere N);
		bool CheckCollideCCv(Capsule R, Convex N);
		bool CheckCollideSCv(Sphere R, Convex n);
	};
}