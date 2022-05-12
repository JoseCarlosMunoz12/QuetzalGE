#pragma once
#include "ColShapes.h"
namespace CoatlPhysicsEngine {

	class COATL_API AABB_Obj :
		public ColShapes
	{
		float XLength;
		float YLength;
		float ZLength;
		float GetPoint(float P, float Max,float Min);
		float LocPoint(float P, float Max, float Min); 
	public: 
		AABB_Obj(float DimXYZ);
		AABB_Obj(float DimX, float DimYZ);
		AABB_Obj(float DimX, float DimY,float DimZ);
		~AABB_Obj();
		glm::vec3 GetLengths();
		std::vector<glm::vec3> GetPoints(glm::vec3 pos, glm::quat quatAngle);
		std::vector<glm::vec3> GetSegs(glm::vec3 pos, glm::quat quatAngle);
		std::vector<int> GetSegmentsID();
		void SetLengths(glm::vec3 NewLengths);
		glm::vec3 GetClosesPoint(glm::vec3 Point, glm::vec3 pos, glm::quat quatAngle);
		bool Inside(glm::vec3 Point, glm::vec3 pos, glm::quat quatAngle);
		glm::vec3 Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle) override;
		glm::vec3 EPA_Support(glm::vec3 Dir, glm::vec3 pos, glm::quat quatAngle) override;
		std::vector<glm::vec3> GetVertices(glm::vec3 pos, glm::quat quatAngle) override;
		std::vector<glm::vec3> GetNormals(glm::vec3 pos, glm::quat quatAngle) override;
		glm::mat3 GetInertia(float mass) override;
	};
}
