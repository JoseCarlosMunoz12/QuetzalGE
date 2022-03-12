#include "CollisionManager.h"
using namespace CoatlPhysicsEngine;
//Same Body Collisions
bool CollisionManager::CheckCollideSS(Sphere R, Sphere N)
{
	double radSum = R.GetRadius() + N.GetRadius();
	Vec3D Dis = R.GetPosition() - N.GetPosition();
	double dis = Dis.length();
	return radSum > dis;
}
bool CollisionManager::CheckCollideBC(BB R, Capsule N)
{

	std::vector<int> Ind = { 0,1,1,2,2,3,3,0,
		4,5,5,6,6,7,7,4,
		0,4,1,5,2,6,3,7 };
	std::vector<Vec3D> Points = R.GetVertices();
	double rad = N.GetRadius();
	for (int ii = 0; ii < 12; ii++)
	{
		int JJ = ii * 2;
		int KK = JJ + 1;
		double Dis = MATH::Distance_Seg(N.GetVertices(), { Points[Ind[JJ]] ,Points[Ind[KK]] });
		if (rad > Dis)
		{
			return true;
		}
	}
	return false;
}
bool CollisionManager::CheckCollideBS(BB R, Sphere N)
{
	Vec3D clsPnt = R.GetClosestPoint(N.GetPosition());
	double rad = N.GetRadius();
	Vec3D dif = clsPnt - N.GetPosition();
	double dis = dif.length();
	return dis <= rad;
}
bool CollisionManager::CheckCollideCS(Capsule R, Sphere N)
{
	double cpRad = R.GetRadius();
	double spRad = N.GetRadius();
	Vec3D T = MATH::ClosestPoint_Seg(R.GetVertices(), N.GetPosition());
	double dis = T.length();
	double radSum = cpRad + spRad;
	return radSum > dis;
}
bool CollisionManager::CheckCollideCC(Capsule R, Capsule N)
{
	double cap0R = R.GetRadius();
	double cap1R = N.GetRadius();
	double rDis = cap0R + cap1R;
	double dis = MATH::Distance_Seg(R.GetVertices(), N.GetVertices());
	return rDis > dis;
}
bool CollisionManager::CheckCollideBB(BB R, BB N)
{
	std::vector<Vec3D> Ob0_Segs = R.GetVertices();
	std::vector<Vec3D> Ob1_Segs = N.GetVertices();
	std::vector<Vec3D> norms0 = R.GetNormals();
	std::vector<Vec3D> norms1 = N.GetNormals();
	return MATH::SATColCheck(Ob0_Segs, norms0, Ob1_Segs, norms1);
}