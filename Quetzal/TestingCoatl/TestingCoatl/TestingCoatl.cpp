// TestingCoatl.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "CoatlPhysicsEngine.h"
using namespace CPE;
int main()
{
    std::cout << "Hello World!\n";
    VecXD ls(3, 1.9);
    ls[0] = 23;
    for (int ii = 0; ii < 3; ii++)
        std::cout << ls[ii] << "\n";
}