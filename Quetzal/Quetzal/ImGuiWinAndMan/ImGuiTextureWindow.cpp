#include "ImGuiTextureWindow.h"

void ImGuiTextureWindow::Update(float dt)
{
    if (show)
    {
        if (!Begin("MainViewPort"))
        {
            end();
        }
        else
        {
            if(ImGui::Button("Run Game"))
                this->Base_Render->ChangeRenderTarget(true);
            ImGui::SameLine();
            float fps = 1.f / dt;
            ImGui::Text("FPS: %6.3f",fps);
            ImVec2 Te = ImGui::GetWindowSize();
            Te.y -= 60;
            if (Te.y <= 0)
                Te.y = 1;
            ImGui::Image((void*)this->Textures[CurId], Te, ImVec2(0, 1), ImVec2(1, 0));
            end();
        }
    }
}

ImGuiTextureWindow::ImGuiTextureWindow(GLuint TextId)
    :ImGuiWinPar(), CurId(0)
{
    this->Textures.push_back(TextId);

}