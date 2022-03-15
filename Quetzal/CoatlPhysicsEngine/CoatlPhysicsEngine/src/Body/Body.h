#pragma once
#include "../define.h"
#include "../Shape/Shape.h"
namespace CoatlPhysicsEngine {
	class Body
	{
	private:
		S_P<Shape> _Shape;
		double MassInv;
		Matrix3x3 InertiaInv;
		Vec3D Velocity;
		Vec3D AngularVelocity;
		void DisplayInternals();
		std::string GetInternals();
	public:
		Body(S_P<Shape> initShape, double initMass, Matrix3x3 initInert);
		double GetInvMass();
		void SetMass(double newMass);
		void SetMassInfinite();
		Matrix3x3 GetInvInertia();
		void SetInertia(Matrix3x3 newInertia);
		void SetIntertiaInfinite();
		void DisplayInfo();
		std::string GetStr();
		Vec3D GetVelocity();
		void SetVelocity(Vec3D newVel);
		Vec3D GetAngularVelocity();
		void SetAngularVelocity(Vec3D newVel);
		S_P<Shape> GetShape();
	};
}