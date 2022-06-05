#pragma once
#include "../Contact.h"
#include "../../Shapes/Capsule.h"
#include "../../GJK/GJK.h"
namespace CoatlPhysicsEngine {
	class CapsuleRelCapsule
	{
	private:

	public:
		static std::vector<std::shared_ptr<Contact>> CapRel(Capsule Cap0, Capsule Cap1);
		CapsuleRelCapsule();
		~CapsuleRelCapsule();
	};	
}
