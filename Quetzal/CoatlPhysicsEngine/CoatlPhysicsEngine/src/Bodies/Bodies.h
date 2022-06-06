#pragma once
#include <vector>
#include "../Shapes/ColShapes.h"
#include "../Physics/Particle.h"
#include "../Physics/RigidBodies.h"
#include "Joints/Joints.h"
namespace CoatlPhysicsEngine {
	class COATL_API Bodies
	{
	private:
		Vec<glm::vec3> Units = { glm::vec3(0.f, 0.f, 1.f),glm::vec3(0.f, 1.f, 0.f),glm::vec3(1.f, 0.f, 0.f),
										glm::vec3(0.f, 0.f,-1.f),glm::vec3(0.f,-1.f, 0.f),glm::vec3(-1.f, 0.f, 0.f) };
		int ID;
		S_P<ColShapes> BodPart;
		S_P<Bod_Base> BodParticle;
		glm::vec3 Max;
		glm::vec3 Min;
		glm::vec3 Mid;
		bool IsCollided;
	public:
		Bodies(int InitID);
		Bodies(S_P<ColShapes> InitShapes, int InitID);
		~Bodies();
		void AddShapes(S_P<ColShapes> NewShape);
		int GetID();
		//Parts of Body
		void SetParticle(int ShapeID);
		void SetRigidBody(int ShapeID);
		//For base Parents
		void SetPosition(glm::vec3 NewPos);
		void MovePosition(glm::vec3 Add);
		void SetQuat(glm::quat NewQuat);
		bool HasCollided();
		glm::vec3 GetPos();
		glm::quat GetQuat();
		S_P<ColShapes> GetShapes();
		S_P<Bod_Base> GetParticle();
		bool IsValid();
		//Update Function
		void UpdateAABB();
		void UpdatePos(float dt);
		//get AABB Hierarchy
		glm::vec3 GetMax() { return this->Max; };
		glm::vec3 GetMin() { return this->Min; };
		glm::vec3 GetMid() { return this->Mid; };
		//Support Vectors
		glm::vec3 Support(glm::vec3 Dir);
		glm::vec3 EPA_Support(glm::vec3 Dir);

	};
}
