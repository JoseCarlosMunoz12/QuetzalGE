#include "B_Force.h"
using namespace CoatlPhysicsEngine;
B_Force::B_Force()
{
}

B_Force::~B_Force()
{
}

bool B_Force::Insert(S_P<Body> body)
{
	this->Bodies.push_back(body);
	return true;
}

Vec_SH<Body> B_Force::GetQueries(S_P<Body> Bod, double Ext)
{
	return this->Bodies;
}

Vec_SH<Body> CoatlPhysicsEngine::B_Force::GetQueries(Vec3D Pos, double Ext)
{
	return this->Bodies;
}

std::string B_Force::GetAlgorType()
{
	return "Brute Force";
}
