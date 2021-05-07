#pragma once
#include "ImGuiPar.h"

class IG_All_Items : public ImGuiWinPar
{
private:
	std::string WinName;
	glm::quat QRs;
	glm::vec3 ERs;
	void DisplayChildren(Vec_SH<Node> Chld);
public:
	IG_All_Items(std::string Name = "All Items");
	~IG_All_Items();
	void Update() override;
};

