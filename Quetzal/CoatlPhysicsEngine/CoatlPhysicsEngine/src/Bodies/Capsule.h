#pragma once
#include "Body.h"
namespace CoatlPhysicsEngine {

	class COATL_API Capsule : public Body
	{
	private:
		Vec3D Seg0;
		Vec3D Seg1;
		double Radius;
	public:
		Capsule(double initRadius,Vec3D initSeg0, Vec3D initSeg1, Vec3D initPos, Quat initRot);
		//Getters and Setters
		void SetRadius(double newRadius);
		double GetRadius();
		void GetSegment(Vec3D& outSeg0, Vec3D outSeg1);
		void SetSegment(Vec3D newSeg0, Vec3D newSeg1);
		double GetLength();
		void DisplayInfo() override;
		std::string GetStr() override;
	};
}

