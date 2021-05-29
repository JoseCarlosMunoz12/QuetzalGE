#pragma once
#include "Anim_Items/AnimationData.h"
class AnimHandler
{
private:
	Vec_SH<AnimationData> AllAnims;
public:
	AnimHandler();
	~AnimHandler();
	void AddAnims(M_S_M Offsets, M_S_M TransMats, M_S_I BoneLocs);
	void Update(float dt);
	S_P<AnimationData> GetAnim(int Id) { return this->AllAnims[Id]; };
};