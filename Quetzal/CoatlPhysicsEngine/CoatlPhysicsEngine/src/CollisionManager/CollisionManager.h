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
		//Just Collision Checks
		//
		bool CheckCollide(S_P<Shape> L, S_P<Shape> R);
		bool CheckCollide(S_P<Shape> L, S_P<Shape> R, std::vector<Vec3D> Seg0, std::vector<Vec3D> Seg1);
		//
		bool CheckCollideBB(S_P<BB> L,S_P<BB> R);
		bool CheckCollideCC(S_P<Capsule> L, S_P<Capsule> R);
		bool CheckCollideSS(S_P<Sphere> L, S_P<Sphere> R);
		//
		bool CheckCollideBC(S_P<BB> L, S_P<Capsule> R);
		bool CheckCollideBS(S_P<BB> L, S_P<Sphere> R);
		bool CheckCollideCS(S_P<Capsule> L, S_P<Sphere> R);
		//Collision as well as Penetration

	};
}