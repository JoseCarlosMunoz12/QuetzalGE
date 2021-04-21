#pragma once
#include "ImGuiPar.h"
class ImGuiTextureWindow : public ImGuiWinPar
{
public:
	void Update() override;
	ImGuiTextureWindow(GLuint TextId);
private:
	std::vector<GLuint> Textures;
	int CurId;
};

