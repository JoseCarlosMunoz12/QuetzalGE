#pragma once
#include "ImGuiPar.h"
class ImGuiTestButton : public ImGuiWinPar
{
public:
    ImGuiTestButton(std::string Name);
    void Update(float) override;
private:
    std::string WinName;
    int Counter = 0;
};

