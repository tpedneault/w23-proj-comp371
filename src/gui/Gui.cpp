#include "Gui.h"

namespace sc {

GuiManager::GuiManager(GLFWwindow *window) : m_Window(window) {}

GuiManager::~GuiManager() = default;

void GuiManager::Start() {
  std::cout << "Started GUI manager" << std::endl;

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ConfigureIO();
  ConfigureStyle();

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
  ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
  {
    ImGui::Text("Hello, world!");
  }
  ImGui::End();
}

void GuiManager::CreateSceneWindow() {
  ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
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
  ImGui::Begin("Console", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
  {

  }
  ImGui::End();
}

void GuiManager::CreatePropertiesWindow() {
  ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
  {

  }
  ImGui::End();
}

void GuiManager::ConfigureIO() {
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

  io.Fonts->AddFontFromFileTTF("assets/fonts/Source_Sans_Pro/SourceSansPro-Regular.ttf", 18.0f);
  io.Fonts->AddFontFromFileTTF("assets/fonts/Source_Sans_Pro/SourceSansPro-Bold.ttf", 18.0f);
}

/**
 * Style copied from this comment:
 * https://github.com/ocornut/imgui/issues/707#issuecomment-670976818
 */
void GuiManager::ConfigureStyle() {
  constexpr auto ColorFromBytes = [](uint8_t r, uint8_t g, uint8_t b) {
    return ImVec4((float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, 1.0f);
  };

  auto &style = ImGui::GetStyle();
  ImVec4 *colors = style.Colors;

  const ImVec4 bgColor = ColorFromBytes(37, 37, 38);
  const ImVec4 lightBgColor = ColorFromBytes(82, 82, 85);
  const ImVec4 veryLightBgColor = ColorFromBytes(90, 90, 95);

  const ImVec4 panelColor = ColorFromBytes(51, 51, 55);
  const ImVec4 panelHoverColor = ColorFromBytes(29, 151, 236);
  const ImVec4 panelActiveColor = ColorFromBytes(0, 119, 200);

  const ImVec4 textColor = ColorFromBytes(255, 255, 255);
  const ImVec4 textDisabledColor = ColorFromBytes(151, 151, 151);
  const ImVec4 borderColor = ColorFromBytes(78, 78, 78);

  colors[ImGuiCol_Text] = textColor;
  colors[ImGuiCol_TextDisabled] = textDisabledColor;
  colors[ImGuiCol_TextSelectedBg] = panelActiveColor;
  colors[ImGuiCol_WindowBg] = bgColor;
  colors[ImGuiCol_ChildBg] = bgColor;
  colors[ImGuiCol_PopupBg] = bgColor;
  colors[ImGuiCol_Border] = borderColor;
  colors[ImGuiCol_BorderShadow] = borderColor;
  colors[ImGuiCol_FrameBg] = panelColor;
  colors[ImGuiCol_FrameBgHovered] = panelHoverColor;
  colors[ImGuiCol_FrameBgActive] = panelActiveColor;
  colors[ImGuiCol_TitleBg] = bgColor;
  colors[ImGuiCol_TitleBgActive] = bgColor;
  colors[ImGuiCol_TitleBgCollapsed] = bgColor;
  colors[ImGuiCol_MenuBarBg] = panelColor;
  colors[ImGuiCol_ScrollbarBg] = panelColor;
  colors[ImGuiCol_ScrollbarGrab] = lightBgColor;
  colors[ImGuiCol_ScrollbarGrabHovered] = veryLightBgColor;
  colors[ImGuiCol_ScrollbarGrabActive] = veryLightBgColor;
  colors[ImGuiCol_CheckMark] = panelActiveColor;
  colors[ImGuiCol_SliderGrab] = panelHoverColor;
  colors[ImGuiCol_SliderGrabActive] = panelActiveColor;
  colors[ImGuiCol_Button] = panelColor;
  colors[ImGuiCol_ButtonHovered] = panelHoverColor;
  colors[ImGuiCol_ButtonActive] = panelHoverColor;
  colors[ImGuiCol_Header] = panelColor;
  colors[ImGuiCol_HeaderHovered] = panelHoverColor;
  colors[ImGuiCol_HeaderActive] = panelActiveColor;
  colors[ImGuiCol_Separator] = borderColor;
  colors[ImGuiCol_SeparatorHovered] = borderColor;
  colors[ImGuiCol_SeparatorActive] = borderColor;
  colors[ImGuiCol_ResizeGrip] = bgColor;
  colors[ImGuiCol_ResizeGripHovered] = panelColor;
  colors[ImGuiCol_ResizeGripActive] = lightBgColor;
  colors[ImGuiCol_PlotLines] = panelActiveColor;
  colors[ImGuiCol_PlotLinesHovered] = panelHoverColor;
  colors[ImGuiCol_PlotHistogram] = panelActiveColor;
  colors[ImGuiCol_PlotHistogramHovered] = panelHoverColor;
  colors[ImGuiCol_DragDropTarget] = bgColor;
  colors[ImGuiCol_NavHighlight] = bgColor;
  colors[ImGuiCol_DockingPreview] = panelActiveColor;
  colors[ImGuiCol_Tab] = bgColor;
  colors[ImGuiCol_TabActive] = panelActiveColor;
  colors[ImGuiCol_TabUnfocused] = bgColor;
  colors[ImGuiCol_TabUnfocusedActive] = panelActiveColor;
  colors[ImGuiCol_TabHovered] = panelHoverColor;

  style.WindowRounding = 0.0f;
  style.ChildRounding = 0.0f;
  style.FrameRounding = 0.0f;
  style.GrabRounding = 0.0f;
  style.PopupRounding = 0.0f;
  style.ScrollbarRounding = 0.0f;
  style.TabRounding = 0.0f;
}

};