#pragma once
#include <string>

class ImGuiWindow
{
public:
	ImGuiWindow()
		:show(true)
	{};
	~ImGuiWindow() {};
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