#pragma once
#include "BaseCols.h"
#include "../Maths/Maths.h"
#include "../Physics/Phys_Libs.h"
namespace CoatlPhysicsEngine {
	class KinematicsCollisions : public BaseCols
	{
	private:
		std::unique_ptr<Queries> AlgoCheck;
		float Ext;
		float B_Ex;
		Alg_Type AlgoType;
		int NewCurId = 0;
	public:
		KinematicsCollisions(std::string Name);
		~KinematicsCollisions();
		std::vector<std::shared_ptr<Bodies>> GetBods(std::shared_ptr<Bodies> Bod);
		void AddNewBody(std::shared_ptr<ColShapes> NewShape);
		void AddNewBody(std::vector<std::shared_ptr<ColShapes>> NewShapes);
		Alg_Type GetType();
		void SetNewType(Alg_Type NewType);
	};
}

