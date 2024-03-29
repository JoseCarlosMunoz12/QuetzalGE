#pragma once
#include "../Shapes/ColShapes.h"
#include "../CollisionResolution/Col_Resolution.h"
namespace CoatlPhysicsEngine {
	class SAT
	{
	private:
		static float ProjPen(glm::vec3& Normal, std::vector<glm::vec3> Sh_Vert0, std::vector<glm::vec3> Sh_Vert1);
		static float SAT_Algo(std::vector<glm::vec3> Norm0, std::vector<glm::vec3> Norm1,
			std::vector<glm::vec3> Pnts0, std::vector<glm::vec3> Pnts1,
			glm::vec3& Norm);
		static void SAT_Point_Cul(glm::vec3 Norm, std::vector<glm::vec3>& Vert0, std::vector<glm::vec3>& Vert1);
	public:
		SAT() {};
		~SAT() {};
		static float GetPenetrationContacts(std::shared_ptr<ColShapes> Bod0, std::shared_ptr<ColShapes> Bod1, glm::vec3& Norm);
		static bool SAT_Check(std::shared_ptr<ColShapes> Bod0, std::shared_ptr<ColShapes> Bod1);
		std::vector<std::shared_ptr<Contact>> SAT_CreateContacts(std::shared_ptr<ColShapes> Bod0, std::shared_ptr<ColShapes> Bod1,
			glm::vec3 Norm, float Pen);
	};
}