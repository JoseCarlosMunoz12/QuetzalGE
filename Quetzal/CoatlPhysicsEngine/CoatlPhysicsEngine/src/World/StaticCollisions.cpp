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
}

Vec_SH<Body> StaticCollisions::GetBodies()
{
    return this->Bodies;
}

Alg_Type StaticCollisions::GetAlgType()
{
    return this->AlgoType;
}

void StaticCollisions::SetNewType(Alg_Type NewType)
{
    this->AlgoType = NewType;

}
