#pragma once
#include "Shape.h"
namespace CoatlPhysicsEngine {
	class COATL_API BB : public Shape
	{
	private:
		Vec3D Dimensions;
	public:
		BB(Vec3D initDimen, Vec3D initPos, Quat initRot);
		~BB();
		Vec3D GetDimensions();
		void SetDimensions(Vec3D newDimen);
		Vec3D GetClosestPoint(Vec3D pnt);
		void DisplayInfo() override;
		std::string GetStr() override;
		std::vector<Vec3D> GetVertices() override;
		std::vector<Vec3D> GetNormals() override;
		Vec3D Support(Vec3D dir) override;
		Vec3D EPA_Support(Vec3D dir) override;
	};
}
