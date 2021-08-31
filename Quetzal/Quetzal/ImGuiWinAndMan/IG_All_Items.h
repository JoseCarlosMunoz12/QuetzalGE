#pragma once
#include "ImGuiPar.h"

class IG_All_Items : public ImGuiWinPar
{
private:
	std::string WinName;
	void DisplayChildren(S_P<Node> Nd,Vec_SH<Mesh>VecMesh,Vec_SH<Texture>VecTex,Vec_SH<Material> VecMat);
	void DisplayChildren(S_P<Node> Nd, Vec_SH<Anim_Mesh>VecMesh, Vec_SH<Texture>VecTex, Vec_SH<Material> VecMat);
	//Displays Static Data
	void DisplayData(S_P<Model> Mdl);
	//Displays Animated Data
	void DisplayData(S_P<Anim_Model> Mdl);
public:
	IG_All_Items(std::string Name = "All Items");
	~IG_All_Items();
	void Update(float dt) override;
};

