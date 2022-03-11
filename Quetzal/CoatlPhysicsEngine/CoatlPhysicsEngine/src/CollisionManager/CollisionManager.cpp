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