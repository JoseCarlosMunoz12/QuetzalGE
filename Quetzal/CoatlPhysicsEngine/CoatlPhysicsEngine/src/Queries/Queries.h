#pragma once
#include "../Body/Body.h"
namespace CoatlPhysicsEngine {
	class Queries {
	public:
		Queries() {}
		~Queries() {}
		virtual bool Insert(S_P<Body> Bod) = 0;
		virtual Vec_SH<Body> GetQueries(S_P<Body> Bod, float Ext) = 0;
		virtual std::string GetAlgorType()
		{
			return "None";
		}
		virtual void Erase() {};
	};
}