#include "ImGuiTestButton.h"

void ImGuiTestButton::Update()
{
    if (show)
    {
        if (!Begin("Startup"))
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
