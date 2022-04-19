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
	if (std::abs(Pos[0] - Center[0]) >= (Ext + Ex))
		return false;
	if (std::abs(Pos[1] - Center[1]) >= (Ext + Ex))
		return false;
	if (std::abs(Pos[2] - Center[2]) >= (Ext + Ex))
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
	Vec3D Pos = body->GetShape()->GetPosition();
	//check if points can be inside
	if (!InsidePar(Pos))
	{
		return false;
	}
	int Size = Bodies.size();
	//See if there is room in QuadTree
	if (Size < 8 && Box0 == NULL)
	{
		Bodies.push_back(body);
		return true;
	}
	//Determine to
	if (Box0 == NULL)
	{
		this->InitChilds();
		this->SeperateBods();
	}
	//Check which to insert
	if (Box0->Insert(body)) return true;
	if (Box1->Insert(body)) return true;
	if (Box2->Insert(body)) return true;
	if (Box3->Insert(body)) return true;
	if (Box4->Insert(body)) return true;
	if (Box5->Insert(body)) return true;
	if (Box6->Insert(body)) return true;
	if (Box7->Insert(body)) return true;
	//this happens if it fails.
	return false;
}

Vec_SH<Body> OctoTree::GetQueries(S_P<Body> Bod, double Ext)
{
	Vec_SH<Body> Temp = std::vector<S_P<Body>>();
	//check if the locatin is in the OctoTre
	Vec3D Loc = Bod->GetShape()->GetPosition();
	if (!InsidePar(Loc, Ext))
		return Temp;
	//Append all Bods in the Octo and not include current Body
	for (auto& jj : Bodies)
	{
		if (jj->GetID() != Bod->GetID())
			Temp.push_back(jj);
	}
	if (Box0 == NULL)
		return Temp;
	//Get rest of Bodies
	Vec_SH<Body> Bods0 = Box0->GetQueries(Bod, Ext);
	Temp.insert(Temp.end(), Bods0.begin(), Bods0.end());

	Vec_SH<Body> Bods1 = Box1->GetQueries(Bod, Ext);
	Temp.insert(Temp.end(), Bods1.begin(), Bods1.end());

	Vec_SH<Body>Bods2 = Box2->GetQueries(Bod, Ext);
	Temp.insert(Temp.end(), Bods2.begin(), Bods2.end());

	Vec_SH<Body>Bods3 = Box3->GetQueries(Bod, Ext);
	Temp.insert(Temp.end(), Bods3.begin(), Bods3.end());

	Vec_SH<Body>Bods4 = Box4->GetQueries(Bod, Ext);
	Temp.insert(Temp.end(), Bods4.begin(), Bods4.end());

	Vec_SH<Body>Bods5 = Box5->GetQueries(Bod, Ext);
	Temp.insert(Temp.end(), Bods5.begin(), Bods5.end());

	Vec_SH<Body>Bods6 = Box6->GetQueries(Bod, Ext);
	Temp.insert(Temp.end(), Bods6.begin(), Bods6.end());

	Vec_SH<Body>Bods7 = Box7->GetQueries(Bod, Ext);
	Temp.insert(Temp.end(), Bods7.begin(), Bods7.end());

	return Temp;
}

std::string OctoTree::GetAlgorType()
{
	return "OctoTree";
}
