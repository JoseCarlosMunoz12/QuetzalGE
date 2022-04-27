#include "KinematicCollisions.h"

using namespace CoatlPhysicsEngine;

void KinematicCollisions::UpdateBodies(double dt)
{
	for (auto& jj : this->Bodies)
		jj->UpdateRotPos(dt);
}
