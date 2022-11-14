#pragma once
#include "../Bodies/Bodies.h"
#define EPA_TOLERANCE 0.0001
#define EPA_MAX_NUM_FACES 64
#define EPA_MAX_NUM_LOOSE_EDGES 32
#define EPA_MAX_NUM_ITERATIONS 64
namespace CoatlPhysicsEngine {
	class GJK_Alg
	{
	private:
		//Other Vectors functions
		static float F3Box(glm::vec3 A, glm::vec3 B, glm::vec3 C);
		static glm::vec3 TripleCross(glm::vec3 A, glm::vec3 B);
		static int Tr_Farthest_Point(std::vector<glm::vec3> Vec);
		//regular Support Function	
		static glm::vec3 Support(S_P<Bodies>Shape0, S_P<Bodies>Shape1, glm::vec3 Dir);
		//sweep test function
		static glm::vec3 Support(S_P<Bodies>Shape0, S_P<Bodies>Shape1,
			std::vector<glm::vec3> Seg0, std::vector<glm::vec3> Seg1 ,glm::vec3 Dir);
		static glm::vec3 Support(std::vector<glm::vec3> Seg, glm::vec3 Dir);
		static bool Simplex_Maker(S_P<Bodies>Shape0, S_P<Bodies>Shape1, glm::vec3 Pos0, glm::vec3 Pos1,
			std::vector<glm::vec3>& Verts, glm::vec3& Dir);
		//EPA GJK functions
		static glm::vec3 EPA_Support(S_P<Bodies>Shape0, S_P<Bodies>Shape1, glm::vec3 Dir);
		static glm::vec3 EPA(std::vector<glm::vec3> Verts,
			S_P<Bodies>Shape0, S_P<Bodies>Shape1, float& Pen);
		static glm::vec3 ClosestPoint(std::vector<glm::vec3> Verts);
		static std::vector<glm::vec3> NewSimplex(std::vector<glm::vec3> Verts, glm::vec3 NewPoint);
		static float Cl_Dist(std::vector<glm::vec3> Verts);
		static glm::vec3 C_F_E(S_P<Bodies>Shape0, S_P<Bodies>Shape1);
		//Simplex for GJK
		static bool Simplex_Maker(S_P<Bodies>Shape0, S_P<Bodies>Shape1,
			std::vector<glm::vec3>& Verts, glm::vec3& Dir);
		static std::vector<int> C_F_S(std::vector<glm::vec3>& Verts);
	public:
		GJK_Alg();
		~GJK_Alg();
		static bool GJK(S_P<Bodies>Shape0, S_P<Bodies>Shape1);
		static bool GJK(S_P<Bodies>Shape0, S_P<Bodies>Shape1,
			std::vector<glm::vec3> Seg0, std::vector<glm::vec3> Seg1);
		static bool EPA_GJK(S_P<Bodies>Shape0, S_P<Bodies>Shape1,glm::vec3& DistVect,float& Pen);

	};
}