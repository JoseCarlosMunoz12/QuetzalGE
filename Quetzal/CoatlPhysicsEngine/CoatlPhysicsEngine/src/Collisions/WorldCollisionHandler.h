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
	class WorldCollisionHandler
	{
	private:
		const float EPSILON = 0.00015f;
		bool UpdateBodies(S_P<Sphere> Sph0, S_P<Bodies> Bod0, S_P<Bodies> Bod1);
		bool UpdateBodies(S_P<Capsule> Cap0, S_P<Bodies> Bod0, S_P<Bodies> Bod1);
	protected:
		// other functions
		bool ColBods(S_P<Bodies> Bod0, S_P<Bodies> Bod1);
		bool ColBods(S_P<Bodies> Bod0, S_P<Bodies> Bod1, Vec<glm::vec3> Seg0, Vec<glm::vec3> Seg1);
		bool BinColDetection(S_P<Bodies> Bod0, S_P<Bodies> Bod1, glm::vec3 Vel0, glm::vec3 Vel1,
			float t0, float t1, float& NewDt);

	};
}