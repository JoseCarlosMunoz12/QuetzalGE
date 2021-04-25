#pragma once
#include <vector>
#include "ImGuiWins.h"
#include "../Renderer/Render_Manager.h"
class ImGuiWindowManager
{
public:
    ImGuiWindowManager(GLFWwindow* window, S_P<Render_Manager> InitManager);
    ~ImGuiWindowManager() {};
    void Update();
    void Render();
    void AddWindow(std::shared_ptr<ImGuiWinPar> newWin);
private:
    std::vector<std::shared_ptr<ImGuiWinPar>> windows;
    S_P<Render_Manager> Ren_Manager;
    void ShowDockSpace(bool* p_open);
    void SetStyle();
    void UpdateWindows();
    void DeleteWindows();

};

