#include "CollisionManager.h"
using namespace CoatlPhysicsEngine;
CollisionManager::CollisionManager()
	:GJK()
{
}
CollisionManager::~CollisionManager()
{
}
//GJK Collision
bool CollisionManager::CheckCollide(S_P<Shape> L, S_P<Shape> R)
{
	return GJK_Col(L, R);
}
bool CollisionManager::CheckCollide(S_P<Shape> L, S_P<Shape> R, std::vector<Vec3D> Seg0, std::vector<Vec3D> Seg1)
{
	return GJK_Col(L, R, Seg0, Seg1);
}
//Same Body Collisions
bool CollisionManager::CheckCollideSS(S_P<Sphere> L, S_P<Sphere> R)
{
	double radSum = L->GetRadius() + R->GetRadius();
	Vec3D Dis = L->GetPosition() - R->GetPosition();
	double dis = Dis.length();
	return radSum > dis;
}
bool CollisionManager::CheckCollideCC(S_P<Capsule> L, S_P<Capsule> R)
{
	double cap0R = L->GetRadius();
	double cap1R = R->GetRadius();
	double rDis = cap0R + cap1R;
	double dis = MATH::Distance_Seg(L->GetVertices(), R->GetVertices());
	return rDis > dis;
}
bool CollisionManager::CheckCollideBB(S_P<BB> L, S_P<BB> R)
{
	std::vector<Vec3D> Ob0_Segs = R->GetVertices();
	std::vector<Vec3D> Ob1_Segs = R->GetVertices();
	std::vector<Vec3D> norms0 = L->GetNormals();
	std::vector<Vec3D> norms1 = R->GetNormals();
	return MATH::SATColCheck(Ob0_Segs, norms0, Ob1_Segs, norms1);
}
//
//Shape Combinations
//
bool CollisionManager::CheckCollideBC(S_P<BB> L, S_P<Capsule> R)
{

	std::vector<int> Ind = { 0,1,1,2,2,3,3,0,
		4,5,5,6,6,7,7,4,
		0,4,1,5,2,6,3,7 };
	std::vector<Vec3D> Points = L->GetVertices();
	double rad = R->GetRadius();
	for (int ii = 0; ii < 12; ii++)
	{
		int JJ = ii * 2;
		int KK = JJ + 1;
		double Dis = MATH::Distance_Seg(R->GetVertices(), { Points[Ind[JJ]] ,Points[Ind[KK]] });
		if (rad > Dis)
		{
			return true;
		}
	}
	return false;
}
bool CollisionManager::CheckCollideBS(S_P<BB> L, S_P<Sphere> R)
{
	Vec3D clsPnt = L->GetClosestPoint(R->GetPosition());
	double rad = R->GetRadius();
	Vec3D dif = clsPnt - R->GetPosition();
	double dis = dif.length();
	return dis <= rad;
}
bool CollisionManager::CheckCollideCS(S_P<Capsule> L, S_P<Sphere> R)
{
	double cpRad = L->GetRadius();
	double spRad = R->GetRadius();
	Vec3D T = MATH::ClosestPoint_Seg(L->GetVertices(), R->GetPosition());
	double dis = T.length();
	double radSum = cpRad + spRad;
	return radSum > dis;
}
