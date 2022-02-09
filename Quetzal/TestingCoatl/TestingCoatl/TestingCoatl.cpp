// TestingCoatl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "CoatlPhysicsEngine.h"
using namespace CPE;
int main()
{
    std::cout << "Hello World!\n";
    VectorXD ls(3, 1.9);
    ls[0] = 23;
    for (int ii = 0; ii < 3; ii++)
        std::cout << ls[ii] << "\n";
    Vector3D rs(2.0);
    std::cout << "----\n";
    for (int ii = 0; ii < 3; ii++)
        std::cout << rs[ii] << "\n";
}