#pragma once
#include "ImGuiPar.h"

class IG_All_Items : public ImGuiWinPar
{
private:
	std::string WinName;
	void DisplayChildren(S_P<Node> Nd,Vec_SH<Mesh>VecMesh,Vec_SH<Texture>VecTex,Vec_SH<Material> VecMat);
public:
	IG_All_Items(std::string Name = "All Items");
	~IG_All_Items();
	void Update() override;
};

