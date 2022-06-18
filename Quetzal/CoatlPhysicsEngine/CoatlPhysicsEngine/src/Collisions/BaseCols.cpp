#include "BaseCols.h"
using namespace CoatlPhysicsEngine;

BaseCols::BaseCols(std::string Name)
{
	this->Name = Name;
}

BaseCols::~BaseCols()
{
}

void BaseCols::UpdateBodies(float dt)
{
	for (auto& ii : this->AllBods)
		ii->UpdatePos(dt);
}
