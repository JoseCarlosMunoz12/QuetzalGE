#pragma once
#include "Queries.h"
namespace CoatlPhysicsEngine {
	class QuadTree : public Queries
	{
		//Children Quadtree;
		S_P<QuadTree> NorthWest;
		S_P<QuadTree> NorthEast;
		S_P<QuadTree> SouthWest;
		S_P<QuadTree> SouthEast;
		//Quadtree Parameters
		Vec3D Center;
		double Ext;
		void InitChilds();
		void SeperateBods();
		bool InsidePar(Vec3D Pos);
		bool InsidePar(Vec3D Pos, double Ex);
	public:
		QuadTree(Vec3D Pos, double Dim);
		~QuadTree();
		bool Insert(S_P<Body> body) override;
		Vec_SH<Body> GetQueries(S_P<Body> Bod, double Ext) override;
		Vec_SH<Body> GetQueries(Vec3D Pos, double Ext) override;
		std::string GetAlgorType() override;
	};
}