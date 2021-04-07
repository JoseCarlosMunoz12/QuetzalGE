#include "ImGuiTextureWindow.h"

void ImGuiTextureWindow::Update()
{
    if (show)
    {
        if (!Begin("MainViewPort"))
        {
            end();
        }
        else
        {
            GLuint T;
            ImVec2 Te = ImGui::GetWindowSize();
            ImGui::Image((void*)0, Te);
            end();
        }
    }
}
