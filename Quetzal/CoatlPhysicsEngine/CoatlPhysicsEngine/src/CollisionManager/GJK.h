#pragma once
#include "../Shape/Shape.h"
#include "../Shape/Capsule.h"
#include "../Shape/BB.h"
#include "../Shape/Sphere.h"
#include "../Shape/Convex.h"

#define EPA_TOLERANCE 0.0001
#define EPA_MAX_NUM_FACES 64
#define EPA_MAX_NUM_LOOSE_EDGES 32
#define EPA_MAX_NUM_ITERATIONS 64
namespace CoatlPhysicsEngine {
	class COATL_API GJK
	{
	protected:
		//Other Vectors functions
		double F3Box(Vec3D A, Vec3D B, Vec3D C);
		Vec3D TripleCross(Vec3D A, Vec3D B);
		int Tr_Farthest_Point(std::vector<Vec3D> Vec);
		//regular Support Function	
		Vec3D Support(S_P<Shape> Shape0, S_P<Shape> Shape1, Vec3D Dir);
		//sweep test function
		Vec3D Support(S_P<Shape> Shape0, S_P<Shape> Shape1,
			std::vector<Vec3D> Seg0, std::vector<Vec3D> Seg1, Vec3D Dir);
		Vec3D Support(std::vector<Vec3D> Seg, Vec3D Dir);
		bool Simplex_Maker(S_P<Shape> Shape0, S_P<Shape> Shape1, Vec3D Pos0, Vec3D Pos1,
			std::vector<Vec3D>& Verts, Vec3D& Dir);
		//EPA GJK functions
		Vec3D EPA_Support(S_P<Shape> Shape0, S_P<Shape> Shape1, Vec3D Dir);
		Vec3D EPA(std::vector<Vec3D> Verts,
			S_P<Shape> Shape0, S_P<Shape> Shape1, double& Pen);
		Vec3D ClosestPoint(std::vector<Vec3D> Verts);
		std::vector<Vec3D> NewSimplex(std::vector<Vec3D> Verts, Vec3D NewPoint);
		double Cl_Dist(std::vector<Vec3D> Verts);
		Vec3D C_F_E(S_P<Shape> Shape0, S_P<Shape> Shape1);
		//Simplex for GJK
		bool Simplex_Maker(S_P<Shape> Shape0, S_P<Shape> Shape1,
			std::vector<Vec3D>& Verts, Vec3D& Dir);
		std::vector<int> C_F_S(std::vector<Vec3D>& Verts);

		bool ColCheck(S_P<Shape> Shape0, S_P<Shape> Shape1);
		bool ColCheck(S_P<Shape> Shape0, S_P<Shape> Shape1,
			std::vector<Vec3D> Seg0, std::vector<Vec3D> Seg1);
		bool EPA_GJK(S_P<Shape> Shape0, S_P<Shape> Shape1, Vec3D& DistVect, double& Pen);

	public:
		GJK();
		~GJK();
	};
}
