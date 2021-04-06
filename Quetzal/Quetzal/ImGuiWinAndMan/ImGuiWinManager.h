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
    void AddWindow(ImGuiWinPar newWin);
private:
    std::vector<ImGuiWinPar> windows;
    void ShowDockSpace(bool* p_open);
    void SetStyle();
    void UpdateWindows();
    void DeleteWindows();

};

