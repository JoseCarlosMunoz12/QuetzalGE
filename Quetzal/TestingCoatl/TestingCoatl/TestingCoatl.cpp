// Testing Ground for the Coatl Physics engine.
//
#include "CoatlPhysicsEngine.h"
using namespace CPE;
int main()
{
	CollisionWorldSetup l;
	CollisionWorld ls(l);
	ls.CreateDynamicCol("Test Name");
	ls.UpdateWorld(1.f);
	ls.UpdateWorld(1.f);
	ls.UpdateWorld(1.f);
}