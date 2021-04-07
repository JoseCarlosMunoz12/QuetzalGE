#pragma once
#include "ImGuiPar.h"
class ImGuiTestButton : public ImGuiWinPar
{
public:
    ImGuiTestButton(std::string Name);
    void Update() override;
private:
    std::string WinName;
    int Counter = 0;
};

