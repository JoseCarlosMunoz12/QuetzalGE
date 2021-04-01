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
                //do something
            }
            end();
        }
    }
}
