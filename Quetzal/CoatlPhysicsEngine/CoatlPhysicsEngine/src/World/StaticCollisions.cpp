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
    this->Bodies.push_back(initBody);
}

Vec_SH<Body> StaticCollisions::GetBodies()
{
    return this->Bodies;
}
