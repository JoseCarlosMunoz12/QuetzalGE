#include "DynamicCollisions.h"
using namespace CoatlPhysicsEngine;

bool DynamicCollisions::ContainsManifold(Vec_SH<Contact> ColRel, S_P<Contact> NewMan)
{
	for (auto& jj : ColRel)
	{
		bool F_Same = false;
		bool S_Same = false;
		if (jj->Bods[0]->GetID() == NewMan->Bods[0]->GetID() || jj->Bods[1]->GetID() == NewMan->Bods[0]->GetID())
			F_Same = true;
		if (jj->Bods[0]->GetID() == NewMan->Bods[1]->GetID() || jj->Bods[1]->GetID() == NewMan->Bods[1]->GetID())
			S_Same = true;
		if (S_Same && F_Same)
			return true;
	}
	return false;
}

void DynamicCollisions::CullManifolds(Vec_SH<Contact>& Cnt )
{
	//Verifies that there is no repeats of later collisions.
	//Ignores the terrain coordinates
	//erased any repeats that are above the threshold
	std::sort(Cnt.begin(), Cnt.end());
	for (auto jj = Cnt.begin(); jj != Cnt.end();++jj)
		for (auto ii = jj + 1; ii != Cnt.end();)
		{
			int ID0 = (*jj)->Bods[0]->GetID();
			int ID1 = (*ii)->Bods[0]->GetID();
			if (ID0 == ID1)
			{
				float s = glm::abs((*jj)->dt0 - (*ii)->dt0);
				if (s > 0.00003)
					ii = Cnt.erase(ii);
				else
					++ii;
			}
			else
				break;
		}
}

DynamicCollisions::DynamicCollisions(std::string Name)
	:BaseCols(Name),
	Ext(100.f), AlgoType(Alg_Type::O_T), B_Ex(4.f)
{
	this->Gravity = glm::vec3(0.f, 0.f, -9.81f);
}

DynamicCollisions::~DynamicCollisions()
{

}

void DynamicCollisions::AddNewBody(S_P<ColShapes> NewShape)
{
	this->AllBods.push_back(std::make_shared<Bodies>(NewShape, this->NewCurId));
	this->NewCurId++;
}

void DynamicCollisions::AddNewBody(Vec_SH<ColShapes> NewShapes)
{
	for (auto& jj : NewShapes)
		AddNewBody(jj);
}

std::string DynamicCollisions::GetName()
{
	return this->Name;
}

Vec_WP<Bodies> DynamicCollisions::GetAllBodies()
{
	std::vector<std::weak_ptr<Bodies>> Temp;
	for (auto& jj : this->AllBods)
		Temp.push_back(jj);
	return Temp;
}

S_P<Bodies> DynamicCollisions::GetABody(int ID)
{
	S_P<Bodies> Temp;
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

Vec_SH<Bodies> DynamicCollisions::GetAllBods()
{
	return this->AllBods;
}

Alg_Type DynamicCollisions::GetType()
{
	return this->AlgoType;
}

void DynamicCollisions::SetNewType(Alg_Type NewType)
{
	this->AlgoType = NewType;
}
