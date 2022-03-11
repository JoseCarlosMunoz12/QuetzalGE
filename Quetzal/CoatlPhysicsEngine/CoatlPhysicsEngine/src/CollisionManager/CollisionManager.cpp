#include "CollisionManager.h"
using namespace CoatlPhysicsEngine;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

template<typename _T, typename _N>
bool CollisionManager::CheckCollide(_T R, _T N)
{
	return true;
}
template<>
bool CollisionManager::CheckCollide<Body, Body>(Body Bod0, Body Bod1)
{
	return true;
}
//Same Body Collisions
template<>
bool CollisionManager::CheckCollide<Sphere, Sphere>(Sphere Sph0, Sphere Sph1)
{
	double radSum = Sph0.GetRadius() + Sph1.GetRadius();
	Vec3D Dis = Sph0.GetPosition() - Sph1.GetPosition();
	double dis = Dis.length();
	return radSum > dis;
}
template<>
bool CollisionManager::CheckCollide<Capsule, Capsule>(Capsule Cap0, Capsule Cap1)
{
	double cap0R = Cap0.GetRadius();
	double cap1R = Cap1.GetRadius();
	double rDis = cap0R + cap1R;
	double dis = MATH::Distance_Seg(Cap0.GetVertices(), Cap1.GetVertices());
	return rDis > dis;
}
template<>
bool CollisionManager::CheckCollide<BB, BB>(BB _BB0, BB _BB1)
{
	std::vector<Vec3D> Ob0_Segs = _BB0.GetVertices();
	std::vector<Vec3D> Ob1_Segs = _BB1.GetVertices();
	std::vector<Vec3D> norms0 = _BB0.GetNormals();
	std::vector<Vec3D> norms1 = _BB1.GetNormals();
	return MATH::SATColCheck(Ob0_Segs, norms0, Ob1_Segs, norms1);
}