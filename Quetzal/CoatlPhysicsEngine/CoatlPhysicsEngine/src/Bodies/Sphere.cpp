#include "Sphere.h"

using namespace CoatlPhysicsEngine;

Sphere::Sphere(double initRadius, Vec3D initPos, Quat initRot)
	:Body(initPos, initRot), Radius(initRadius)
{
}
