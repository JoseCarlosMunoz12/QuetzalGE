#include "QuadTree.h"
using namespace CoatlPhysicsEngine;

void QuadTree::InitChilds()
{

	Vec3D Pos = Center;
	this->NorthWest = std::make_unique<QuadTree>(Vec3D(Pos[0] - Ext / 2, Pos[1] + Ext / 2, Pos[2]), Ext / 2);
	this->NorthEast = std::make_unique<QuadTree>(Vec3D(Pos[0] + Ext / 2, Pos[1] + Ext / 2, Pos[2]), Ext / 2);
	this->SouthWest = std::make_unique<QuadTree>(Vec3D(Pos[0] - Ext / 2, Pos[1] - Ext / 2, Pos[2]), Ext / 2);
	this->SouthEast = std::make_unique<QuadTree>(Vec3D(Pos[0] + Ext / 2, Pos[1] - Ext / 2, Pos[2]), Ext / 2);
}

void QuadTree::SeperateBods()
{
	for (auto& jj : this->Bodies)
		this->Insert(jj);
	this->Bodies.clear();
}

bool QuadTree::InsidePar(Vec3D Pos)
{
	if (Pos[0] > (Center[0] + Ext) || Pos[0] < (Center[0] - Ext))
		return false;
	if (Pos[1] > (Center[1] + Ext) || Pos[1] < (Center[1] - Ext))
		return false;
	return true;
}

bool QuadTree::InsidePar(Vec3D Pos, double Ex)
{
	if(std::abs(Pos[0] - Center[0]) >= (Ext + Ex))
		return false;
	if(std::abs(Pos[1] - Center[1]) >= (Ext + Ex))
		return false;
	return true;
}

QuadTree::QuadTree(Vec3D Pos, double Dim)
	:Queries(), Center(Pos), Ext(Dim)
{
}

 QuadTree::~QuadTree()
{
}

bool QuadTree::Insert(S_P<Body> body)
{
	Vec3D Pos = body->GetShape()->GetPosition();

	//check if points can be inside
	if (!InsidePar(Pos))
	{
		return false;
	}
	int Size = this->Bodies.size();
	//See if there is room in QuadTree
	if (Size < 4 && NorthWest == NULL)
	{
		Bodies.push_back(body);
		return true;
	}
	//Determine to
	if (NorthWest == NULL)
	{
		this->InitChilds();
		this->SeperateBods();
	}
	//Check which to insert
	if (NorthWest->Insert(body)) return true;
	if (NorthEast->Insert(body)) return true;
	if (SouthWest->Insert(body)) return true;
	if (SouthEast->Insert(body)) return true;
	//this happens if it fails.
	return false;
}

Vec_SH<Body> QuadTree::GetQueries(S_P<Body> Bod, double Ext)
{
	std::vector<std::shared_ptr<Body>> Temp;
	Vec3D Loc = Bod->GetShape()->GetPosition();
	//Check if the Location and Ext is in the Quadtree
	if (!InsidePar(Loc, Ext))
		return Temp;
	//Append all Bods in the Quad
	for (auto& jj : Bodies)
	{
		if (jj->GetID() != Bod->GetID())
			Temp.push_back(jj);
	}
	//Terminate if there is no Children
	if (NorthWest == NULL)
		return Temp;
	//get rest of Bodies
	std::vector<std::shared_ptr<Body>> NWBods = NorthWest->GetQueries(Bod, Ext);
	Temp.insert(Temp.end(), NWBods.begin(), NWBods.end());

	std::vector<std::shared_ptr<Body>> NEBods = NorthEast->GetQueries(Bod, Ext);
	Temp.insert(Temp.end(), NEBods.begin(), NEBods.end());

	std::vector<std::shared_ptr<Body>> SWBods = SouthWest->GetQueries(Bod, Ext);
	Temp.insert(Temp.end(), SWBods.begin(), SWBods.end());

	std::vector<std::shared_ptr<Body>> SEBods = SouthEast->GetQueries(Bod, Ext);
	Temp.insert(Temp.end(), SEBods.begin(), SEBods.end());
	return Temp;
}

Vec_SH<Body> QuadTree::GetQueries(Vec3D Pos, double Ext)
{
	std::vector<std::shared_ptr<Body>> Temp;
	Vec3D Loc = Pos;
	//Check if the Location and Ext is in the Quadtree
	if (!InsidePar(Loc, Ext))
		return Temp;
	//Append all Bods in the Quad
	for (auto& jj : Bodies)
		Temp.push_back(jj);
	//Terminate if there is no Children
	if (NorthWest == NULL)
		return Temp;
	//get rest of Bodies
	std::vector<std::shared_ptr<Body>> NWBods = NorthWest->GetQueries(Pos, Ext);
	Temp.insert(Temp.end(), NWBods.begin(), NWBods.end());

	std::vector<std::shared_ptr<Body>> NEBods = NorthEast->GetQueries(Pos, Ext);
	Temp.insert(Temp.end(), NEBods.begin(), NEBods.end());

	std::vector<std::shared_ptr<Body>> SWBods = SouthWest->GetQueries(Pos, Ext);
	Temp.insert(Temp.end(), SWBods.begin(), SWBods.end());

	std::vector<std::shared_ptr<Body>> SEBods = SouthEast->GetQueries(Pos, Ext);
	Temp.insert(Temp.end(), SEBods.begin(), SEBods.end());
	return Temp;
}

std::string QuadTree::GetAlgorType()
{
	return "QuadTree";
}
