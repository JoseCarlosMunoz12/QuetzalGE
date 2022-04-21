#include "StaticCollisions.h"

StaticCollisions::StaticCollisions()
{
    this->Bodies = std::vector<S_P<Body>>();
}

StaticCollisions::~StaticCollisions()
{

}

void StaticCollisions::AddBody(S_P<Body> initBody)
{
    initBody->SetID(NewCurID);
    this->Bodies.push_back(initBody);
    NewCurID++;
}

void StaticCollisions::AddBodies(Vec_SH<Body> NewShapes)
{
	for (auto& jj : NewShapes)
	{
		jj->SetID(NewCurID);
		this->Bodies.push_back(jj);
		NewCurID++;
	}
}

Vec_SH<Body> StaticCollisions::GetAllBodies()
{
    return this->Bodies;
}

Vec_SH<Body> StaticCollisions::GetBodies(S_P<Body> body)
{

	switch (AlgoType)
	{
	case Alg_Type::B_F:
		this->Algo = std::make_unique<B_Force>();
		break;
	case Alg_Type::Q_T:
		this->Algo = std::make_unique<QuadTree>(Vec3D(), Ext);
		break;
	case Alg_Type::O_T:
		this->Algo = std::make_unique<OctoTree>(Vec3D(), Ext);
		break;
	default:
		break;
	}
	//Add bodies into Algorithm
	for (auto& jj : this->Bodies)
	{
		this->Algo->Insert(jj);
	}
	//get queries and test them
	return this->Algo->GetQueries(body, Ext);
}

Alg_Type StaticCollisions::GetAlgType()
{
    return this->AlgoType;
}

void StaticCollisions::SetNewType(Alg_Type NewType)
{
    this->AlgoType = NewType;
}
