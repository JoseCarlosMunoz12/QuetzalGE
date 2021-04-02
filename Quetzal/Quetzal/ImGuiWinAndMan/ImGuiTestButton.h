#pragma once
#include "ImGuiPar.h"
class ImGuiTestButton : public ImGuiWinPar
{
public:
    void Update() override;
private:
    int Counter = 0;
};

