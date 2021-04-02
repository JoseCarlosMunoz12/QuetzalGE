#pragma once
#include <vector>
#include "ImGuiWins.h"
class ImGuiWinManager
{
public:
    ImGuiWinManager(GLFWwindow* window);
    ~ImGuiWinManager();
    void Update();
    void Render();
    void AddWindow(ImGuiWindow newWin);
private:
    std::vector<ImGuiWindow> windows;
    void ShowDockSpace(bool* p_open);
    void Setstyle();
    void UpdateWindows();
    void DeleteWindows();

};

