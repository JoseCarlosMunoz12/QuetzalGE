// Testing Ground for the Coatl Physics engine.
//
#include <iostream>
#include "CoatlPhysicsEngine.h"
using namespace CPE;
int main()
{
	S_P<World> world = std::make_shared<World>();
	world->CreateAllWorlds();
	auto k = world->GetKinematicWorld();
	auto s = world->GetStaticWorld();
	auto d = world->GetDynamicWorld();
	if (k)
		std::cout << "test0\n";
	if (s)
		std::cout << "test1\n";
	if (d)
		std::cout << "test2\n";
	world->DeleteAllWorlds();
	if (k)
		std::cout << "test0\n";
	if (s)
		std::cout << "test1\n";
	if (d)
		std::cout << "test2\n";
}