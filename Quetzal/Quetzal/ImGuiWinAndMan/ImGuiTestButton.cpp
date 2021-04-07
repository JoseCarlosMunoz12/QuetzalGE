#include "ImGuiTestButton.h"

ImGuiTestButton::ImGuiTestButton(std::string Name = "BaseName")
    :WinName(Name)
{
}

void ImGuiTestButton::Update()
{
    if (show)
    {
        if (!Begin(this->WinName.c_str()))
        {
            end();
        }
        else
        {
            ImGui::Text("Press me:");
            if (ImGui::Button("button"))
            {
                Counter++;
            }
            ImGui::Text(std::to_string(Counter).c_str());
            end();
        }
    }
}
