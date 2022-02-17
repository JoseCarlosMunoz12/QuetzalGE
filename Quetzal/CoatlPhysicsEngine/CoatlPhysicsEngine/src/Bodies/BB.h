#pragma once
#include "Body.h"
namespace CoatlPhysicsEngine {
	class COATL_API BB : public Body
	{
	private:
		Vec3D Dimensions;
	public:
		BB(Vec3D initDimen, Vec3D initPos, Quat initRot);
		~BB();
		Vec3D GetDimensions();
		void SetDimensions(Vec3D newDimen);
		void DisplayInfo() override;
		std::string GetStr() override;
	};
}
