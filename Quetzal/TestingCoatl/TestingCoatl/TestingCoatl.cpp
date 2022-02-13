// TestingCoatl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "CoatlPhysicsEngine.h"
using namespace CPE;
int main()
{
    std::cout << "Hello World!\n";
    Vec3D R(0.0, 1.0,0.0);
    Vec3D L(1.0, 0.0, 0.0);
    Vec3D Dir = MATH::CreateNormal({ L,R });
    Dir.DisplayAns();

}