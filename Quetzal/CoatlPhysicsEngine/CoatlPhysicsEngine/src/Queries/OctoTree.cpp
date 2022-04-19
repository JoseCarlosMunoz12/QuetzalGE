#include "OctoTree.h"
using namespace CoatlPhysicsEngine;

void OctoTree::InitChilds()
{

	Vec3D Pos = Center;
	//Top Layer
	this->Box0 = std::make_unique<OctoTree>(Vec3D(Pos[0] - Ext / 2, Pos[1] + Ext / 2, Pos[2] + Ext / 2), Ext / 2);
	this->Box1 = std::make_unique<OctoTree>(Vec3D(Pos[0] + Ext / 2, Pos[1] + Ext / 2, Pos[2] + Ext / 2), Ext / 2);
	this->Box2 = std::make_unique<OctoTree>(Vec3D(Pos[0] - Ext / 2, Pos[1] - Ext / 2, Pos[2] + Ext / 2), Ext / 2);
	this->Box3 = std::make_unique<OctoTree>(Vec3D(Pos[0] + Ext / 2, Pos[1] - Ext / 2, Pos[2] + Ext / 2), Ext / 2);
	//Bottom Layer							
	this->Box4 = std::make_unique<OctoTree>(Vec3D(Pos[0] - Ext / 2, Pos[1] + Ext / 2, Pos[2] - Ext / 2), Ext / 2);
	this->Box5 = std::make_unique<OctoTree>(Vec3D(Pos[0] + Ext / 2, Pos[1] + Ext / 2, Pos[2] - Ext / 2), Ext / 2);
	this->Box6 = std::make_unique<OctoTree>(Vec3D(Pos[0] - Ext / 2, Pos[1] - Ext / 2, Pos[2] - Ext / 2), Ext / 2);
	this->Box7 = std::make_unique<OctoTree>(Vec3D(Pos[0] + Ext / 2, Pos[1] - Ext / 2, Pos[2] - Ext / 2), Ext / 2);
}

void OctoTree::SeperateBods()
{
	for (auto& jj : this->Bodies)
		this->Insert(jj);
	this->Bodies.clear();
}

bool OctoTree::InsidePar(Vec3D Pos)
{

	if (Pos[0] > (Center[0] + Ext) || Pos[0] < (Center[0] - Ext))
		return false;
	if (Pos[1] > (Center[1] + Ext) || Pos[1] < (Center[1] - Ext))
		return false;
	if (Pos[2] > (Center[2] + Ext) || Pos[2] < (Center[2] - Ext))
		return false;
	return true;
}

bool OctoTree::InsidePar(Vec3D Pos, double Ex)
{
	if (MATH::abs(Pos[0] - Center[0]) >= (Ext + Ex))
		return false;
	if (glm::abs(Pos.y - Center.y) >= (Ext + Ex))
		return false;
	if (glm::abs(Pos.z - Center.z) >= (Ext + Ex))
		return false;
	return true;
}

OctoTree::OctoTree(Vec3D initPos, double initEx)
	:Queries(),Center(initPos),Ext(initEx)
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
