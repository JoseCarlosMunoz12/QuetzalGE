#include "IG_All_Items.h"

IG_All_Items::IG_All_Items(std::string Name)
	:WinName(Name)
{
}

IG_All_Items::~IG_All_Items()
{
}

void IG_All_Items::Update()
{

    if (show)
    {
        if (!Begin(this->WinName.c_str()))
        {
            end();
        }
        else
        {
            ImGui::Text("All Items avaliable in the world");
            end();
        }
    }
}
