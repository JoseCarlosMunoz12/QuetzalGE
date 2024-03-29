#include "StaticCollisions.h"
using namespace CoatlPhysicsEngine;

StaticCollisions::StaticCollisions(std::string Name)
	:BaseCols(Name), Ext(100.f), AlgoType(Alg_Type::O_T), B_Ex(4.f)
{
}

StaticCollisions::~StaticCollisions()
{	
}

void StaticCollisions::UpdateCollisionCheck()
{
}

void StaticCollisions::CheckCol(std::shared_ptr<Bodies> Bod)
{
	//make approriate Algorithm
	switch (AlgoType)
	{
	case Alg_Type::B_F:
		this->AlgoCheck = std::make_unique<B_Force_Self>();
		break;
	case Alg_Type::Q_T:
		this->AlgoCheck = std::make_unique<QuadTree>(glm::vec3(0.f), Ext);
		break;
	case Alg_Type::O_T:
		this->AlgoCheck = std::make_unique<OctoTree>(glm::vec3(0.f), Ext);
		break;
	default:
		break;
	}
	//Add bodies into Algorithm
	for (auto& jj : AllBods)
	{
		this->AlgoCheck->Insert(jj);
	}
	//get queries and test them
	std::vector<std::shared_ptr<Bodies>> Quer = this->AlgoCheck->GetQueries(Bod, Ext);
	for (auto& kk : Quer)
	{
	}
}

void StaticCollisions::AddNewBody( std::shared_ptr<ColShapes> NewShape)
{
	this->AllBods.push_back(std::make_shared<Bodies>(NewShape,this->NewCurId));
	this->NewCurId++;
}

void StaticCollisions::AddNewBody(std::vector<std::shared_ptr<ColShapes>> NewShapes)
{
	for (auto& ii : NewShapes)
	{
		this->AllBods.push_back(std::make_shared<Bodies>(ii, this->NewCurId));
		this->NewCurId++;
	}
}

std::string StaticCollisions::GetName()
{
	return this->Name;
}

std::vector<std::weak_ptr<Bodies>> StaticCollisions::GetAllBodies()
{
	std::vector<std::weak_ptr<Bodies>> Temp;
	for (auto& jj : this->AllBods)
	{
		Temp.push_back(jj);
	}
	return Temp;
}

std::vector<std::shared_ptr<Bodies>> StaticCollisions::GetBods(std::shared_ptr<Bodies> Bod)
{
	//make approriate Algorithm
	switch (AlgoType)
	{
	case Alg_Type::B_F:
		this->AlgoCheck = std::make_unique<B_Force_Self>();
		break;
	case Alg_Type::Q_T:
		break;
		this->AlgoCheck = std::make_unique<QuadTree>(glm::vec3(0.f), Ext);
	case Alg_Type::O_T:
		this->AlgoCheck = std::make_unique<OctoTree>(glm::vec3(0.f), Ext);
		break;
	default:
		break;
	}
	//Add bodies into Algorithm
	for (auto& jj : AllBods)
		this->AlgoCheck->Insert(jj);
	//get queries and test them

	return this->AlgoCheck->GetQueries(Bod, Ext);
}

std::shared_ptr<Bodies> StaticCollisions::GetABody(int ID)
{
	std::shared_ptr<Bodies> Temp;
	for (auto& ii : this->AllBods)
	{
		if (ii->GetID() == ID)
		{
			Temp = ii;
			break;
		}
	}
	return Temp;
}

Alg_Type StaticCollisions::GetType()
{
	return this->AlgoType;
}

void StaticCollisions::SetNewType(Alg_Type NewType)
{
	this->AlgoType = NewType;
}
