#pragma once
#include "../define.h"
#include "../Maths/Maths.h"
#include "../Maths/Matrix.h"
#include "../Maths/Vectors.h"
namespace CoatlPhysicsEngine {
	class COATL_API Body
	{
	protected:
		double MassInv;
		Matrix3x3 InertiaInv;
		Vec3D Position;
		Quat Rotation;
		Vec3D Velocity;
		Vec3D AngularVelocity;
		void DisplayInternals();
		std::string GetInternals();
	public:
		Body(double initMass, Matrix3x3 initIntert,
			Vec3D initPos, Quat initRot);
		Body(Vec3D initPos, Quat initRot);
		~Body();
		double GetInvMass();
		void SetMass(double newMass);
		void SetMassInfinite();
		Matrix3x3 GetInvInertia();
		void SetInertia(Matrix3x3 newInertia);
		void SetIntertiaInfinite();
		Vec3D GetPosition();
		void SetPosition(Vec3D newPos);
		Quat GetRotation();
		void SetRotation(Quat newRot);
		Vec3D GetVelocity();
		void SetVelocity(Vec3D newVel);
		Vec3D GetAngularVelocity();
		void SetAngularVelocity(Vec3D newVel);
		virtual void DisplayInfo();
		virtual std::string GetStr();
		virtual std::vector<Vec3D> GetNormals();
		virtual std::vector<Vec3D> GetVertices();
	};
}

