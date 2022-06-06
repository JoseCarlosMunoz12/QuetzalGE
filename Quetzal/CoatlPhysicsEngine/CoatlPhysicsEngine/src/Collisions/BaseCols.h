#pragma once
#include <string>
#include <iostream>
#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\type_ptr.hpp>
#include <vector>

#include "../Shapes/ColShapes.h"
#include "../Bodies/Bodies.h"
#include "../Bodies/Bod_Collection.h"
#include "../Bodies/Joints/Joints.h"
#include "../CollisionManager/CollisionManager.h"
#include "../CollisionResolution/Col_Resolution.h"
#include "../OptimizaAlgorithm/QuadTree.h"
#include "../OptimizaAlgorithm/OctoTree.h"
#include "../OptimizaAlgorithm/B_Force.h"
#include "../OptimizaAlgorithm/B_Force_Self.h"
#include "../GJK/GJK.h"
#include "../CollisionResolution/ContactCreation.h"

namespace CoatlPhysicsEngine {
	COATL_API enum class Alg_Type
	{
		B_F,
		Q_T,
		O_T
	};
	class COATL_API BaseCols
	{
	private:
		bool UpdateBodies(S_P<Sphere> Sph0, S_P<Bodies> Bod0, S_P<Bodies> Bod1);
		bool UpdateBodies(S_P<Capsule> Cap0, S_P<Bodies> Bod0, S_P<Bodies> Bod1);
	protected:
		//name
		std::string Name;
		// bodies in the collision world and Collections in this world
		Vec_SH<Bodies> AllBods;
		//Algoirthm to check collision
		U_P<Queries> AlgoCheck;
		int NewCurID;
		//collision manifolds
		Vec_SH<Contact> ColRel;
		// other functions
		bool ColBods(S_P<Bodies> Bod0, S_P<Bodies> Bod1);
		bool ColBods(S_P<Bodies> Bod0, S_P<Bodies> Bod1, Vec<glm::vec3> Seg0, Vec<glm::vec3> S);
	public:
		BaseCols(std::string Name);
		~BaseCols();
		Vec_SH<Contact> GetColRel();
		Vec_SH<Collection> GetCollections();
	};
}
