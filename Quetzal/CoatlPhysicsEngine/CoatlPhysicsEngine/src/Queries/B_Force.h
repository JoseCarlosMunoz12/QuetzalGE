#pragma once
#include "Queries.h"
namespace CoatlPhysicsEngine {
	class B_Force :public Queries
	{
	public:
		B_Force();
		~B_Force();
		bool Insert(S_P<Body> body) override;
		Vec_SH<Body> GetQueries(S_P<Body> Bod, double Ext) override;
		std::string GetAlgorType() override;
	};
}