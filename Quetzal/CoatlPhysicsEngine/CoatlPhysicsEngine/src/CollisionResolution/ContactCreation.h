#pragma once
#include "../Bodies/Bodies.h"
#include "../GJK/GJK.h"
#include "../SAT/SAT.h"
#include "Col_Resolution.h"
#include "ShapesResolution/ShapeResolution.h"
namespace CoatlPhysicsEngine
{
	class ContactCreation
	{
		//Contact creation
		static std::vector<S_P<Contact>> ContactCreate(S_P<Sphere> Sph0, S_P<Bodies> Bod0, S_P<Bodies> Bod1);
		static std::vector<S_P<Contact>> ContactCreate(S_P<Bodies> Bod0, S_P<Bodies> Bod1);
		static std::vector<S_P<Contact>> ContactCreate(S_P<Capsule> Cap, S_P<Bodies> Bod0, S_P<Bodies> Bod1);
		static std::vector<S_P<Contact>> MakeContacts(S_P<Bodies> Bod0, S_P<Bodies> Bod1);
		static float GetLowestFric(S_P<Bodies> Bod0, S_P<Bodies> Bod1);
		static float GetLowestRest(S_P<Bodies> Bod0, S_P<Bodies> Bod1);
	public:
		ContactCreation();
		~ContactCreation();
		//Create Manifolds
		static std::vector<S_P<Contact>> MakeManifold(S_P<Bodies> Bod0, S_P<Bodies> Bod1, float dt0, float dt1);
		static void MakeJointManifold(std::vector<S_P<Contact>>& R, std::vector<S_P<ColJoints>> BodJoints);
	};

}
