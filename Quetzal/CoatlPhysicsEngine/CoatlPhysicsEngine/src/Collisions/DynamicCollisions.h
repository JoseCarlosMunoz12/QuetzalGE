#pragma once
#include "BaseCols.h"
#include "StaticCollisions.h"
#include "KinematicsCollisions.h"
#include "../Maths/Maths.h"
#include "../Physics/Phys_Libs.h"
#include <algorithm>

namespace CoatlPhysicsEngine {
	class COATL_API DynamicCollisions : public BaseCols

	{
	private:
		U_P<Phy_Base> F_Manager;
		U_P<Phy_Base> Grav_F_Manager;
		U_P<Queries> AlgoCheck;
		U_P<Col_Resolution> Col_Rel;
		glm::vec3 Gravity;
		int NewCurId = 100;
		float Ext;
		float B_Ex;
		Alg_Type AlgoType;
		const float EPSILON = 0.00015f;
		bool it = true;
		bool BinColDetection(S_P<Bodies> Bod0, S_P<Bodies> Bod1,
			glm::vec3 Vel0, glm::vec3 Vel1,
			float t0, float t1,
			float& NewDt);
		bool ContainsManifold(Vec_SH<Contact> ColRel, S_P<Contact> NewMan);
		void CullManifolds(Vec_SH<Contact>& Cnt );
	public:
		DynamicCollisions(std::string Name);
		~DynamicCollisions();
		void CheckCollision(S_P<StaticCollisions> Statics,S_P<KinematicsCollisions> Kin,Vec_SH<Contact>& Conts ,float dt);
		//Body information of Class
		void AddNewBody(S_P<ColShapes> NewShape);
		void AddNewBody(Vec_SH<ColShapes> NewShapes);
		std::string GetName();
		Vec_WP<Bodies> GetAllBodies();
		S_P<Bodies> GetABody(int ID);
		//change and check type of CollisionCheckAlgoritm
		Alg_Type GetType();
		void SetNewType(Alg_Type NewType);
		int IterTook() { return this->Col_Rel->GetTook(); };
		int VelIter() { return this->Col_Rel->GetVelTook(); };
	};
}
