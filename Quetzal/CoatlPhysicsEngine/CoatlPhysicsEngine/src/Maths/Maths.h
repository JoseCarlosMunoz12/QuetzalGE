#pragma once
#include "../define.h"
#include "Vectors.h"
#include "Matrix.h"

#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace CoatlPhysicsEngine;

namespace MATH {
	//Closest points for Shapes and Segments
	COATL_API Vec3D ClosestPoint_Seg(std::vector<Vec3D> trianlge, Vec3D Pos, Vec3D Point);
	COATL_API Vec3D ClosestPoint_Seg(std::vector<Vec3D> Seg, Vec3D Point);
	COATL_API Vec3D ClosestPoint_Pnt(std::vector<Vec3D> Seg, Vec3D Pos, Vec3D Point);
	COATL_API void ClosestSeg_Seg(std::vector<Vec3D> Seg0, std::vector<Vec3D> Seg1,Vec3D& Pos0, Vec3D& Pos1);
	//DistanceValue
	COATL_API double Distance_Pnt(std::vector<Vec3D> Seg, Vec3D Pos, Vec3D Point);
	COATL_API double Distance_Seg(std::vector<Vec3D> Seg0, Vec3D Pos, std::vector<Vec3D> Seg1);
	COATL_API double Distance_Seg(std::vector<Vec3D> Seg0, std::vector<Vec3D> Seg1);
	COATL_API double Distance_Tr_Pnt(std::vector<Vec3D> Tr, Vec3D Pos, Vec3D Pnt);
	// Bool SegmentTest
	COATL_API bool ProjColl(std::vector<Vec3D> Seg, std::vector<Vec3D> Sh_Vert0, std::vector<Vec3D> Sh_Vert1);
	COATL_API bool ProjColl(Vec3D Normal, std::vector<Vec3D> Sh_Vert0, std::vector<Vec3D> Sh_Vert1);
	COATL_API bool SATColCheck(std::vector<Vec3D> Norm0, std::vector<Vec3D> Norm1, std::vector<Vec3D> Pnts0, std::vector<Vec3D> Pnts1);
	//Return Changes
	COATL_API void SetMaxMins(Vec3D& Max, Vec3D& Min, Vec3D NewVal);
	COATL_API Vec3D SetMax(Vec3D Max, Vec3D NewVal);
	COATL_API Vec3D SetMin(Vec3D Min, Vec3D NewVal);
	//Vector Maths
	COATL_API Vec3D CreateNormal(std::vector<Vec3D> Seg);
	COATL_API Vec3D Normalize(Vec3D Vec);
	//Vector Check
	COATL_API Vec3D ClampLowest(Vec3D Vec, float Limit);
	COATL_API bool IsSame(Vec3D Vec0, Vec3D Vec1);
}