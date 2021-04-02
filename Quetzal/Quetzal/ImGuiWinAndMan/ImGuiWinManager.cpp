#include "ImGuiWinManager.h"

ImGuiWinManager::ImGuiWinManager(GLFWwindow* window)
{

	ImGui_ImplGlfw_InitForOpenGL(window, true);
}
