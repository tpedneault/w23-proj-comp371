#include "Gui.h"

namespace sc {

GuiManager::GuiManager(GLFWwindow *window) : m_Window(window) {}

GuiManager::~GuiManager() = default;

void GuiManager::Start() {
  std::cout << "started GUI manager" << std::endl;

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  /** Configure ImGui **/
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.Fonts->AddFontFromFileTTF("resources/fonts/space-mono.ttf", 18.0f);

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
  ImGui_ImplOpenGL3_Init("#version 330");
}

void GuiManager::Update() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

  CreateViewportWindow();
  CreateConsoleWindow();
  CreateSceneWindow();
  CreatePropertiesWindow();

  ImGui::EndFrame();
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiManager::Close() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void GuiManager::CreateViewportWindow() {
  ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize);
  {
    ImGui::Text("Hello, world!");
  }
  ImGui::End();
}

void GuiManager::CreateSceneWindow() {
  ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize);
  {
    // Generate samples and plot them
    float samples[100];
    for (int n = 0; n < 100; n++)
      samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
    ImGui::PlotLines("Samples", samples, 100);

    // Display contents in a scrolling region
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
    ImGui::BeginChild("Scrolling");
    for (int n = 0; n < 50; n++)
      ImGui::Text("%04d: Some text", n);
    ImGui::EndChild();
  }
  ImGui::End();
}

void GuiManager::CreateConsoleWindow() {
  ImGui::Begin("Console", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize);
  {
    ImGui::Text("Hello, world!");
  }
  ImGui::End();
}

void GuiManager::CreatePropertiesWindow() {
  ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize);
  {

  }
  ImGui::End();
}

};