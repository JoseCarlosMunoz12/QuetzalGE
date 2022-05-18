#pragma once
#include "ColShapes.h"
namespace CoatlPhysicsEngine{
	class COATL_API Capsule: public ColShapes
	{
		float Radius;
		glm::vec3 APos;
		glm::vec3 BPos;
		//Rotation information
		glm::vec3 UnitVec;
	public:
		Capsule(float InitRadius,float InitLength);
		~Capsule();
		float GetRadius();
		glm::vec3 ClosestPoint_P(glm::vec3 Point, glm::vec3 pos, glm::quat quatAngle);
		float Distance(glm::vec3 Point, glm::vec3 pos, glm::quat quatAngle);
		float Distance(std::vector<glm::vec3> Segment, glm::vec3 pos, glm::quat quatAngle);
		std::vector<glm::vec3> GetSegment(glm::vec3 pos, glm::quat quatAngle);
		//Getter and setters
		glm::vec3 GetUnitVec();
		void SetVec(glm::vec3 NewVec);
		glm::vec3 Support(glm::vec3 Dir,glm::vec3 pos, glm::quat quatAngle) override;
		glm::vec3 EPA_Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle) override;
		std::vector<glm::vec3> GetVertices(glm::vec3 pos, glm::quat quatAngle) override;
		std::vector<glm::vec3> GetNormals(glm::vec3 pos, glm::quat quatAngle) override;
		glm::mat3 GetInertia(float Mass) override;
	};
}