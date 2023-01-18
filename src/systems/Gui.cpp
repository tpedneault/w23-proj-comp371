#include "Gui.h"

namespace sc {

GuiManager::GuiManager() = default;
GuiManager::~GuiManager() = default;

void GuiManager::Start(GLFWwindow *window) {
  std::cout << "started GUI manager" << std::endl;
  m_Context = ImGui::CreateContext();
  m_Window = window;
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 400");
}

void GuiManager::Update() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // Draw items here.
  CreateViewportWindow();

  ImGui::End();
  ImGui::Render();

  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  ImGui::SetCurrentContext(m_Context);
}

void GuiManager::Close() {
}

void GuiManager::CreateViewportWindow() {
  ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_None);

  // Generate samples and plot them
  float samples[100];
  for (int n = 0; n < 100; n++)
    samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
  ImGui::PlotLines("Samples", samples, 100);

  // Display contents in a scrolling region
  ImGui::TextColored(ImVec4(1,1,0,1), "Important Stuff");
  ImGui::BeginChild("Scrolling");
  for (int n = 0; n < 50; n++)
    ImGui::Text("%04d: Some text", n);
  ImGui::EndChild();
  ImGui::End();
}

};