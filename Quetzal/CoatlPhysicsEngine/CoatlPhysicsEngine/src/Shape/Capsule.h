#pragma once
#include "Shape.h"
namespace CoatlPhysicsEngine {

	class COATL_API Capsule : public Shape
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
		std::vector<Vec3D> GetVertices() override;
		std::vector<Vec3D> GetNormals() override;
		Vec3D Support(Vec3D dir) override;
		Vec3D EPA_Support(Vec3D dir) override;
	};
}
