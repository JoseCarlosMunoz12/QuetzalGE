#pragma once
#include "ColShapes.h"
namespace CoatlPhysicsEngine{

	class COATL_API Triangles : public ColShapes
	{
	private:
		glm::vec3 Points[3];
	public:
		Triangles(std::vector<glm::vec3> InitPoints);
		~Triangles();
		std::vector<glm::vec3> GetSegments(glm::vec3 pos, glm::quat quatAngle);
		glm::vec3 GetClosestPoint(glm::vec3 Point, glm::vec3 pos, glm::quat quatAngle);
		glm::vec3 Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle) override;
		glm::vec3 EPA_Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle) override;
		std::vector<glm::vec3> GetVertices(glm::vec3 pos, glm::quat quatAngle) override;
		std::vector<glm::vec3> GetNormals(glm::vec3 pos, glm::quat quatAngle) override;
	};

}
