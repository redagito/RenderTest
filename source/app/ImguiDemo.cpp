#include "app/ImguiDemo.h"

#include <imgui.h>

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

bool ImguiDemo::setup() { return true; }

void ImguiDemo::render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

    ImGui::Render();

    // Clear color buffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}