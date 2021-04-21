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
            ImVec2 Te = ImGui::GetWindowSize();
            ImGui::Image((void*)this->Textures[CurId], Te);
            end();
        }
    }
}

ImGuiTextureWindow::ImGuiTextureWindow(GLuint TextId)
    :ImGuiWinPar(), CurId(0)
{
    this->Textures.push_back(TextId);

}