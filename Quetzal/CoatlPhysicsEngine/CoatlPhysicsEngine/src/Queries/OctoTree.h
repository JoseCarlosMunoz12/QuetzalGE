#pragma once
#include "Queries.h"
namespace CoatlPhysicsEngine
{
	class OctoTree: public Queries
	{
	private:
		///OctoTree Parameters
		Vec3D Center;
		double Ext;
		//Top Boxes
		std::unique_ptr<OctoTree> Box0;
		std::unique_ptr<OctoTree> Box1;
		std::unique_ptr<OctoTree> Box2;
		std::unique_ptr<OctoTree> Box3;
		//Bottome Boxes
		std::unique_ptr<OctoTree> Box4;
		std::unique_ptr<OctoTree> Box5;
		std::unique_ptr<OctoTree> Box6;
		std::unique_ptr<OctoTree> Box7;
		///Functions in OctoTree
		void InitChilds();
		void SeperateBods();
		bool InsidePar(Vec3D Pos);
		bool InsidePar(Vec3D Pos, double Ex);
	public:
		OctoTree(Vec3D InitCent, double Ex);
		~OctoTree();
		bool Insert(S_P<Body> body) override;
		Vec_SH<Body> GetQueries(S_P<Body> Bod, double Ext) override;
		Vec_SH<Body> GetQueries(Vec3D Pos, double Ext) override;
		std::string GetAlgorType() override;
	};
}