#pragma once
#include "../Body/Body.h"
namespace CoatlPhysicsEngine {
	class Queries {
	protected:
		Vec_SH<Body> Bodies;
	public:
		Queries() { Bodies = std::vector <S_P<Body>>(); }
		~Queries() {}
		virtual bool Insert(S_P<Body> Bod) = 0;
		virtual Vec_SH<Body> GetQueries(S_P<Body> Bod, double Ext) = 0;
		virtual std::string GetAlgorType(){return "None";}
		void Erase() { Bodies.clear(); };
	};
}