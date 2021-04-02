#pragma once
#include <string>
#include "ImGuiCallh.h"
class ImGuiWinPar
{
public:
	ImGuiWinPar()
		:show(true)
	{};
	~ImGuiWinPar() {};
	virtual void Update() {};
	void Show() {};
protected:
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