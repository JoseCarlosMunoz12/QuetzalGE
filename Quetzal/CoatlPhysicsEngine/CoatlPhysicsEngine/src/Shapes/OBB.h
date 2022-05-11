#pragma once
#include "ColShapes.h"
namespace CoatlPhysicsEngine {
	class COATL_API OBB : public ColShapes
	{
	private:
		glm::vec3 Ex;
	public:
		//Upright OBB
		OBB(float DimXYZ);
		OBB(float DimX, float DimYZ);
		OBB(float DimX, float DimY, float DimZ);
		~OBB();
		std::vector<glm::vec3> GetSegments(glm::vec3 pos, glm::quat quatAngle);
		glm::vec3 GetLenghts();
		glm::vec3 GetClosestPoint(glm::vec3 Point, glm::vec3 pos, glm::quat quatAngle);
		glm::vec3 Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle) override;
		glm::vec3 EPA_Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle) override;
		std::vector<glm::vec3> GetVertices(glm::vec3 pos, glm::quat quatAngle) override;
		std::vector<glm::vec3> GetNormals(glm::vec3 pos, glm::quat quatAngle) override;
	};
}
