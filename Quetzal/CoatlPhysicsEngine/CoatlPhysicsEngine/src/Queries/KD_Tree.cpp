#include "KD_Tree.h"
using namespace CoatlPhysicsEngine;

KD_Tree::KD_Tree()
{
}

KD_Tree::KD_Tree(S_P<Body> newBody)
{
}

KD_Tree::KD_Tree(Vec_SH<Body> newBodies)
{
}

KD_Tree::~KD_Tree()
{
}

void KD_Tree::InsertBodies(S_P<Body> newBody)
{
}

bool KD_Tree::Insert(S_P<Body> newBody)
{
	return false;
}

Vec_SH<Body> KD_Tree::GetQueries(S_P<Body> Bod, double Ext)
{
	return Vec_SH<Body>();
}

Vec_SH<Body> KD_Tree::GetQueries(Vec3D Pos, double Ext)
{
	return Vec_SH<Body>();
}

std::string KD_Tree::GetAlgorType()
{
	return std::string();
}
