#pragma once
#include "Body.h"
namespace CoatlPhysicsEngine {
	class COATL_API Sphere: public Body
	{
	private:
		double Radius;
	public:
		Sphere(double initRadius, Vec3D initPos, Quat initRot);
		//Getters and Setters
		double GetRadius();
		void SetRadius(double newRadius);
		void DisplayInfo() override;
		std::string GetStr() override;
		std::vector<Vec3D> GetVertices() override;
	};
}
