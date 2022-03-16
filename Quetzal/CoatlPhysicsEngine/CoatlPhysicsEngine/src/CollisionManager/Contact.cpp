#include "Contact.h"
using namespace CoatlPhysicsEngine;

Contact::Contact(S_P<Body> initBod0, S_P<Body> initBod1, Vec3D initPos, Vec3D initDir, double initPen)
	:Bod0(initBod0), Bod1(initBod1), Pos(initPos), Dir(initDir), Penetration(initPen)
{

}
