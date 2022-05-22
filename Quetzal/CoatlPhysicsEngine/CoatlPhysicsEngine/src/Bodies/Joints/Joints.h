#pragma once
#include "../Bodies.h"
namespace CoatlPhysicsEngine
{
	class COATL_API ColJoints
	{
	protected:
		std::weak_ptr<Bodies> BodA;
		std::weak_ptr<Bodies> BodB;
		float Max;
		float Error;
	public:
		ColJoints(float SetError):Max(1.f),Error(SetError) {};
		~ColJoints() {};
		virtual void SetBodies(std::weak_ptr<Bodies> NewBodA, std::weak_ptr<Bodies> NewBodB) { return; };
		//Sets parameters
		virtual void SetMin(float NewMin) { return; };
		virtual void SetMax(float NewMax) { return; };
		virtual void SetAngle(glm::quat NewAngle) { return; };
		void SetError(float NewError) { this->Error = NewError; };
		//Get Parameters
		virtual float GetMax() { return this->Max; };
		virtual float GetMin() { return 0.f; };
		virtual glm::quat GetAngle() { return glm::quat(1.f, 0.f, 0.f, 0.f); };
		virtual std::string GetBodId() { return ""; };
		float GetError() { return this->Error; };
	};
}