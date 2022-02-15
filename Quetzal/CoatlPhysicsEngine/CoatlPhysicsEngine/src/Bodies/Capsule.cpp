#include "Capsule.h"
using namespace CoatlPhysicsEngine;

Capsule::Capsule(double initRadius, Vec3D initSeg0, Vec3D initSeg1, Vec3D initPos, Quat initRot)
	:Body(initPos, initRot), Seg0(initSeg0), Seg1(initSeg1), Radius(initRadius)
{
}
