#include "Col_Resolution.h"
using namespace CoatlPhysicsEngine;

Col_Resolution::Col_Resolution(int InitVel, int InitPos)
	:VelIt(InitVel), Posit(InitPos)
{
}

Col_Resolution::~Col_Resolution()
{
}

void Col_Resolution::ResolveContacts(std::vector<std::shared_ptr<Contact>> Cnt,float dt)
{
	for (auto& jj : Cnt)
	{
		if (jj->BodA->GetParticle()->GetAwakeStatus())
		{
		}
	}
}

/////////////////////////////////////////////////////////////////////////
//----------------------------Contact class----------------------------//
/////////////////////////////////////////////////////////////////////////