// TestingCoatl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "CoatlPhysicsEngine.h"
using namespace CPE;
int main()
{
	Quat Rot;
	Rot.SetZeroDegree();
	Vec3D Pos(0.0);
	Vec3D dim(1.0, 2.0, 1.0);
	BB r(dim,Pos,Rot);
	r.DisplayInfo();
}