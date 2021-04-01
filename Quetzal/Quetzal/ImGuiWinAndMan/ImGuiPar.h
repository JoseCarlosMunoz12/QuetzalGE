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
	virtual bool Begin(std::string name) {};
	void end() {};
	bool show;
};