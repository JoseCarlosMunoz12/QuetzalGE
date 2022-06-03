#include "CollisionManager.h"
using namespace CoatlPhysicsEngine;

CollisionManager::CollisionManager()
	:SphereColSphere(),AABBColAABB(),CapsuleColCapsule(),
        SphereColAABB(), CapsuleColSphere(), CapsuleColAABB(),TriangleColSphere(),
    TriangleColCapsule(),TriangleColAABB(),TriangleColTriangle(),
    OBBColOBB(),ABBColOBB(),TriangleColOBB(),SphereColOBB(),CapsuleColOBB()
{}
CollisionManager::~CollisionManager()
{}
///Base Collisions
template<typename _T, typename _N>
 bool CollisionManager::CheckCollide(_T R, _N N,  glm::vec3 Pos0, glm::quat Rot, glm::vec3 Pos1, glm::quat Rot1)
{
	return false;
}
template<>
bool CollisionManager::CheckCollide(S_P<ColShapes> Sph0, S_P<ColShapes> SPh1,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
{
	return true;
}
 ///Same Object Collisions
template<>
bool CollisionManager::CheckCollide( S_P<Sphere> Sph0, S_P<Sphere> SPh1,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
{
	return SphereSphere(Sph0,SPh1, Pos0, Rot0, Pos1, Rot1);
}
 template<>
 bool CollisionManager::CheckCollide(AABB_Obj Obj0, AABB_Obj Obj1,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return AABBAABB(Obj0, Obj1,  Pos0, Rot0, Pos1, Rot1);
 }
 template<>
 bool CollisionManager::CheckCollide(Capsule Cap0,Capsule Cap1,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return CapsuleCols(Cap0, Cap1,  Pos0,  Rot0,  Pos1, Rot1);
 }
 template<>
 bool CollisionManager::CheckCollide(Triangles Tr0, Triangles Tr1,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return TrColTr(Tr0, Tr1,  Pos0,  Rot0,  Pos1, Rot1);
 }
 template<>
 bool CollisionManager::CheckCollide(OBB Ob0, OBB Ob1,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return OBBCol(Ob0, Ob1,  Pos0,  Rot0,  Pos1, Rot1);
 }
///Different Combinations
// S_P<Sphere> X AABB
 template<>
 bool CollisionManager::CheckCollide(S_P<Sphere> Sph0, AABB_Obj Obj,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return SphereColsAABB(Sph0, Obj,  Pos0,  Rot0,  Pos1, Rot1);
 }
 template<>
 bool CollisionManager::CheckCollide(AABB_Obj obj,  S_P<Sphere> Sph0,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return SphereColsAABB(Sph0, obj,  Pos0,  Rot0,  Pos1, Rot1);
 }
 // S_P<Sphere> X Capsule
 template<>
 bool CollisionManager::CheckCollide(Capsule Cap,  S_P<Sphere> Sph,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return Collision(Cap,Sph,  Pos0,  Rot0,  Pos1, Rot1);
 }
 template<>
 bool CollisionManager::CheckCollide( S_P<Sphere> Sph,Capsule Cap,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return Collision(Cap, Sph,  Pos0,  Rot0,  Pos1, Rot1);
 }
 //Capsule X AABB
 template<>
 bool CollisionManager::CheckCollide(Capsule Cap, AABB_Obj Obj,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return CapColAABB(Cap,Obj,  Pos0,  Rot0,  Pos1, Rot1);
 }
 template<>
 bool CollisionManager::CheckCollide(AABB_Obj Obj, Capsule Cap,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return CapColAABB(Cap, Obj,  Pos0,  Rot0,  Pos1, Rot1);
 }
 // S_P<Sphere> X Triangles
 template<>
 bool CollisionManager::CheckCollide(Triangles Tr,  S_P<Sphere> Sph,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return TrColSphere(Tr, Sph,  Pos0,  Rot0,  Pos1, Rot1);
 }
 template<>
 bool CollisionManager::CheckCollide( S_P<Sphere> Sph, Triangles Tr,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return TrColSphere(Tr, Sph,  Pos0,  Rot0,  Pos1, Rot1);
 }
 //Triangles X Capsule
 template<>
 bool CollisionManager::CheckCollide(Triangles Tr, Capsule Cap,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return TrColCap(Tr, Cap,  Pos0,  Rot0,  Pos1, Rot1);
 }
 template<>
 bool CollisionManager::CheckCollide(Capsule Cap, Triangles Tr,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return TrColCap(Tr, Cap,  Pos0,  Rot0,  Pos1, Rot1);
 }
 //Triangles X AABB
 template<>
 bool CollisionManager::CheckCollide(AABB_Obj Obj,Triangles Tr,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return TrColAABB(Tr, Obj,  Pos0,  Rot0,  Pos1, Rot1);
 }
 template<>
 bool CollisionManager::CheckCollide(Triangles Tr,AABB_Obj Obj,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return TrColAABB(Tr, Obj,  Pos0,  Rot0,  Pos1, Rot1);
 }
 //AABB X OBB
 template<>
 bool CollisionManager::CheckCollide(AABB_Obj AABB, OBB Obj,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return ABBColsOBB(AABB, Obj,  Pos0,  Rot0,  Pos1, Rot1);
 }
 template<>
 bool CollisionManager::CheckCollide( OBB Obj,AABB_Obj AABB,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return ABBColsOBB(AABB, Obj,  Pos0,  Rot0,  Pos1, Rot1);
 }
 //Triangles X OBB
 template<>
 bool CollisionManager::CheckCollide(Triangles Tr, OBB Obj,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return TriColOBB(Tr, Obj,  Pos0,  Rot0,  Pos1, Rot1);
 }
 template<>
 bool CollisionManager::CheckCollide( OBB Obj,Triangles Tr,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return TriColOBB(Tr, Obj,  Pos0,  Rot0,  Pos1, Rot1);
 }
 // S_P<Sphere> X OBB
 template<>
 bool CollisionManager::CheckCollide( S_P<Sphere> SPh, OBB Obj,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return SphColOBB(SPh,Obj,  Pos0,  Rot0,  Pos1, Rot1);
 }
 template<>
 bool CollisionManager::CheckCollide(OBB Obj,  S_P<Sphere> SPh,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return SphColOBB(SPh, Obj,  Pos0,  Rot0,  Pos1, Rot1);
 }
 //Capsule X OBB
 template<>
 bool CollisionManager::CheckCollide(Capsule Cap, OBB Obj,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return CapColOBB(Cap, Obj,  Pos0,  Rot0,  Pos1, Rot1);
 }
 template<>
 bool CollisionManager::CheckCollide(OBB Obj, Capsule Cap,  glm::vec3 Pos0, glm::quat Rot0, glm::vec3 Pos1, glm::quat Rot1)
 {
     return CapColOBB(Cap, Obj,  Pos0,  Rot0,  Pos1, Rot1);
 }