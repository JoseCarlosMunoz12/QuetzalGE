#pragma once
#include <vector>
#include "ImGuiWins.h"
class ImGuiWindowManager
{
public:
    ImGuiWindowManager(GLFWwindow* window);
    ~ImGuiWindowManager() {};
    void Update();
    void Render();
    void AddWindow(std::shared_ptr<ImGuiWinPar> newWin);
private:
    std::vector<std::shared_ptr<ImGuiWinPar>> windows;
    void ShowDockSpace(bool* p_open);
    void SetStyle();
    void UpdateWindows();
    void DeleteWindows();

};

