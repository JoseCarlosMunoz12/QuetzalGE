// Testing Ground for the Coatl Physics engine.
//
#include <iostream>
#include "CoatlPhysicsEngine.h"
using namespace CPE;
int main()
{
	Vec3D Dimen(1.0,2.0,1.0);
	Vec3D Pos(1.0, 0.0, 1.0);
	Vec3D Pos0(1.0, 1.0, 1.0);
	Quat r;
	r.SetZeroDegree();
	S_P<BB> R = std::make_shared<BB>(Dimen, Pos, r);
	S_P<BB> RS = std::make_shared<BB>(Dimen, Pos0, r);
	CollisionManager Col;
	bool rs = Col.CheckCollideBB(R, RS);
	bool sr = Col.CheckCollide(R, RS);
	if (rs)
		std::cout << "asd\n";
	if (sr)
		std::cout << "asd";
}