#pragma once
#include <string>
#include "ImGuiCallh.h"
#include "../Renderer/Render_Manager.h"
class ImGuiWinPar
{
public:
	ImGuiWinPar()
		:show(true)
	{};
	~ImGuiWinPar() {};
	virtual void Update() {};
	void Show() {};
	void AddManager(S_P<Render_Manager> Init_Base) { this->Base_Render = Init_Base; };
protected:
	S_P<Render_Manager> Base_Render;
	virtual bool Begin(std::string name) 
	{
		return ImGui::Begin(name.c_str(), &show);
	};
	void end() 
	{
		ImGui::End();
	};
	bool show;
};