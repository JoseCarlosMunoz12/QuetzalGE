#include "KinematicsCollisions.h"
using namespace CoatlPhysicsEngine;

KinematicsCollisions::KinematicsCollisions(std::string Name)
	:BaseCols(Name), Ext(100.f), AlgoType(Alg_Type::O_T), B_Ex(4.f)
{
}

KinematicsCollisions::~KinematicsCollisions()
{
}

std::vector<std::shared_ptr<Bodies>> KinematicsCollisions::GetBods(std::shared_ptr<Bodies> Bod)
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
	return this->AlgoCheck->GetQueries(Bod, Ext);
}

void KinematicsCollisions::AddNewBody(std::shared_ptr<ColShapes> NewShape)
{
	this->AllBods.push_back(std::make_shared<Bodies>(NewShape, this->NewCurId));
	this->NewCurId++;
}

void KinematicsCollisions::AddNewBody(std::vector<std::shared_ptr<ColShapes>> NewShapes)
{
	for (auto& ii : NewShapes)
	{
		this->AllBods.push_back(std::make_shared<Bodies>(ii, this->NewCurId));
		this->NewCurId++;
	}
}

Alg_Type KinematicsCollisions::GetType()
{
	return  this->AlgoType;
}

void KinematicsCollisions::SetNewType(Alg_Type NewType)
{
	this->AlgoType = NewType;
}

