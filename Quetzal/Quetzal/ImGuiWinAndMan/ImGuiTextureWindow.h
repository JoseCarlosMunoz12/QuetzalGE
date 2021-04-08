#pragma once
#include "ImGuiPar.h"

class ImGuiTextureWindow : public ImGuiWinPar
{
public:
	void Update() override;
private:
	std::vector<std::weak_ptr<GLuint>> Textures;
	int CurId;
};

