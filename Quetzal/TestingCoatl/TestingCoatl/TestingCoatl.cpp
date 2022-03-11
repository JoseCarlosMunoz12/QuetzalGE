// TestingCoatl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "CoatlPhysicsEngine.h"
using namespace CPE;
int main()
{
	Vec3D Dimen(1.0,2.0,1.0);
	Vec3D Pos(1.0, 0.0, 1.0);
	Quat r;
	r.SetZeroDegree();
	BB R(Dimen,Pos ,r);
	std::vector<Vec3D> Vecs = R.GetVertices();
	for (auto& ii : Vecs)
		ii.Display();
	CollisionManager Col;
	bool rs = Col.CheckCollideBB(R, R);
	if (rs)
		std::cout << "asd";
}