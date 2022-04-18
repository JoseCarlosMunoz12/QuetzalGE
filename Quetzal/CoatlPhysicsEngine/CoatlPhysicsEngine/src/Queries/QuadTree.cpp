#include "QuadTree.h"
using namespace CoatlPhysicsEngine;

 QuadTree::QuadTree()
{
}

 QuadTree::~QuadTree()
{
}

bool QuadTree::Insert(S_P<Body> body)
{
	return false;
}

Vec_SH<Body> QuadTree::GetQueries(S_P<Body> Bod, double Ext)
{
	return Vec_SH<Body>();
}

std::string QuadTree::GetAlgorType()
{
	return std::string();
}
