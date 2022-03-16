#pragma once
#include "../Shape/Shape.h"
#include "../Body/Body.h"

 namespace CoatlPhysicsEngine {
	 class Contact
	 {
	 private:
		 S_P<Body> Bod0;
		 S_P<Body> Bod1;
		 Vec3D Pos;
		 Vec3D Dir;
		 double Penetration;
	 public:
		 Contact(S_P<Body> Bod0, S_P<Body> Bod1, Vec3D initPos, Vec3D initDir, double initPen);
	 };

 }
