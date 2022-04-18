#pragma once
#include "Queries.h"
namespace CoatlPhysicsEngine {
	class QuadTree : public Queries
	{
	public:
		QuadTree();
		~QuadTree();
		bool Insert(S_P<Body> body) override;
		Vec_SH<Body> GetQueries(S_P<Body> Bod, double Ext) override;
		std::string GetAlgorType() override;
	};
}