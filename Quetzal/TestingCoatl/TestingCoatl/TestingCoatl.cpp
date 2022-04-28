// Testing Ground for the Coatl Physics engine.
//
#include <iostream>
#include "CoatlPhysicsEngine.h"
using namespace CPE;
int main()
{
	CollisionWorldSetup l;
	CollisionWorld ls(l);
	ls.CreateDynamicCol("");
}