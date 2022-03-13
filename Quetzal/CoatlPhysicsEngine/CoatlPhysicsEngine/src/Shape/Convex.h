#pragma once
#include "Shape.h"
namespace CoatlPhysicsEngine {
	class Convex : Shape
	{
	private:
		std::vector<Vec3D> Pnts;
	public:
		Convex(std::vector<Vec3D> initPnts, Vec3D initPos, Quat initRot);
		~Convex();
		void DisplayInfo() override;
		std::string GetStr() override;
		std::vector<Vec3D> GetVertices() override;
		std::vector<Vec3D> GetNormals() override;
		Vec3D Support(Vec3D dir) override;
		Vec3D EPA_Support(Vec3D dir) override;

	};
}