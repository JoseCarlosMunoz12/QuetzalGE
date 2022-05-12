#pragma once
#include "ColShapes.h"
namespace CoatlPhysicsEngine {
	class COATL_API Sphere :public ColShapes
	{
		float Radius;
	public:
		Sphere(float SetRadius);
		~Sphere();
		float GetRadius();
		void SetRadius(float NewR);
		glm::vec3 Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle) override;
		glm::vec3 EPA_Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle) override;
		std::vector<glm::vec3> GetVertices(glm::vec3 pos, glm::quat quatAngle) override;
		glm::mat3 GetInertia(float mass) override;
	};
}
