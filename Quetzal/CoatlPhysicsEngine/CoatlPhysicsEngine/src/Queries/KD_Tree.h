#pragma once
#include "Queries.h"

namespace CoatlPhysicsEngine {
	class KD_Tree : public Queries
	{
		S_P<Body> m_Body;
		S_P<KD_Tree> Left;
		S_P<KD_Tree> Right;
	public:
		KD_Tree();
		KD_Tree(S_P<Body> newBody);
		KD_Tree(Vec_SH<Body> newBodies);
		~KD_Tree();

		void InsertBodies(S_P<Body> newBody);
		bool Insert(S_P<Body> newBody) override;
		Vec_SH<Body> GetQueries(S_P<Body> Bod, double Ext) override;
		Vec_SH<Body> GetQueries(Vec3D Pos, double Ext) override;
		std::string GetAlgorType() override;
	};
}