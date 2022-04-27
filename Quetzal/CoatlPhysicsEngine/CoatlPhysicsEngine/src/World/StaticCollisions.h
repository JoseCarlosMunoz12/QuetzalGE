#pragma once
#include "../define.h"
#include "../Queries/B_Force.h"
#include "../Queries/QuadTree.h"
#include "../Queries/OctoTree.h"
#include "../Body/Body.h"
#include "../CollisionManager/CollisionManager.h"

namespace CoatlPhysicsEngine {
	enum class Alg_Type
	{
		B_F,
		Q_T,
		O_T
	};
	class COATL_API StaticCollisions
	{
	protected:
		U_P<Queries> Algo;
		Vec_SH<Body> Bodies;
		S_P<CollisionManager> ColMan;
		int NewCurID = 0;
		double Ext;
		double B_Ex;
		Alg_Type AlgoType;
		void SetupAlgo();
	public:
		StaticCollisions();
		~StaticCollisions();
		void AddBody(S_P<Body> initBody);
		void AddBodies(Vec_SH<Body> NewShapes);
		Vec_SH<Body> GetAllBodies();
		Vec_SH<Body> GetBodies(S_P<Body> body);
		Alg_Type GetAlgType();
		void SetNewType(Alg_Type NewType);

	};
}