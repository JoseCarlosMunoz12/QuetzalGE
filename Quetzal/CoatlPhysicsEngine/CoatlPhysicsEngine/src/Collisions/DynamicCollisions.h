#pragma once
#include "BaseCols.h"
#include "StaticCollisions.h"
#include "KinematicsCollisions.h"
#include "../Maths/Maths.h"
#include "../Physics/Phys_Libs.h"

namespace CoatlPhysicsEngine {
	class COATL_API DynamicCollisions : public BaseCols

	{
	private:
		U_P<Queries> AlgoCheck;
		U_P<Col_Resolution> Col_Rel;
		glm::vec3 Gravity;
		int NewCurId = 100;
		float Ext;
		float B_Ex;
		Alg_Type AlgoType;
		bool it = true;
		bool ContainsManifold(Vec_SH<Contact> ColRel, S_P<Contact> NewMan);
		void CullManifolds(Vec_SH<Contact>& Cnt );
	public:
		DynamicCollisions(std::string Name);
		~DynamicCollisions();
		//Body information of Class
		void AddNewBody(S_P<ColShapes> NewShape);
		void AddNewBody(Vec_SH<ColShapes> NewShapes);
		std::string GetName();
		Vec_WP<Bodies> GetAllBodies();
		S_P<Bodies> GetABody(int ID);
		Vec_SH<Bodies> GetAllBods();
		//change and check type of CollisionCheckAlgoritm
		Alg_Type GetType();
		void SetNewType(Alg_Type NewType);
		int IterTook() { return this->Col_Rel->GetTook(); };
		int VelIter() { return this->Col_Rel->GetVelTook(); };
	};
}
