#pragma once
#include "ColShapes.h"
namespace CoatlPhysicsEngine {
	class COATL_API Sphere :public ColShapes
	{
		float Radius;
	public:
		Sphere(glm::vec3 SetPos,float SetRadius);
		~Sphere();
		float GetRadius();
		void SetRadius(float NewR);
		void SetQuat(glm::quat NewQuat) override;
		glm::vec3 Support(glm::vec3 Dir) override;
		glm::vec3 EPA_Support(glm::vec3 Dir) override;
		std::vector<glm::vec3> GetVertices() override;
		glm::mat3 GetInertia(float Mass) override;
	};
}
