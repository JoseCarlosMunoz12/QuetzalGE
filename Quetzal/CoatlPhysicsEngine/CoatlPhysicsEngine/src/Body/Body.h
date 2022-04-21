#pragma once
#include "../define.h"
#include "../Shape/Shape.h"
namespace CoatlPhysicsEngine {
	class COATL_API Body
	{
	private:
		int Id;
		S_P<Shape> _Shape;
		double MassInv;
		Matrix3x3 InertiaInv;
		Vec3D Velocity;
		Vec3D AngularVelocity;

		Vec3D Force_External;
		Vec3D Force_Constraint;
		Vec3D Torque_External;
		Vec3D Torque_Constraint;

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
		std::vector<Vec3D> GetTotalForce();
		void SetAngularVelocity(Vec3D newVel);
		S_P<Shape> GetShape();
		int GetID();
		void SetID(int newId);
		//update classes
		void UpdateExternal(Vec3D newForce, Vec3D newTorque);
		void UpdateConstraint(Vec3D newForce, Vec3D newTorque);
		void UpdateVels(double dt);
		void UpdateRotPos(double dt);

	};
}