#pragma once
#include "ImGuiPar.h"
class ImGuiTestButton : public ImGuiWindow
{
public:
    void Update() override;
private:
    int counter = 0;
};

