#include "OctoTree.h"
using namespace CoatlPhysicsEngine;

OctoTree::OctoTree()
{
}

OctoTree::~OctoTree()
{
}

bool OctoTree::Insert(S_P<Body> body)
{
	return false;
}

Vec_SH<Body> OctoTree::GetQueries(S_P<Body> Bod, double Ext)
{
	return Vec_SH<Body>();
}

std::string OctoTree::GetAlgorType()
{
	return std::string();
}
