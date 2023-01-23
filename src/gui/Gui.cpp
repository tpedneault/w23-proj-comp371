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

  CreateSceneWindow();
  CreateSceneViewWindow();
  CreateCameraViewWindow();
  CreateConsoleWindow();
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

void GuiManager::CreateSceneWindow() {
  ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
  {
    // Display elements in the scene.
  }
  ImGui::End();
}

void GuiManager::CreatePropertiesWindow() {
  ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
  {
    // Display components in the scene and their properties.
  }
  ImGui::End();
}

void GuiManager::CreateSceneViewWindow() {
  ImGui::Begin("Scene View", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
  {
    // Render the Scene FBO to the window.
  }
  ImGui::End();
}

void GuiManager::CreateCameraViewWindow() {
  ImGui::Begin("Camera View", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
  {
    // Render the Camera FBO to the window.
  }
  ImGui::End();
}

void GuiManager::CreateConsoleWindow() {
  ImGui::Begin("Console", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
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

void GuiManager::AssignSceneFBO(GLuint fbo) {
  sceneFBO = fbo;
}

void GuiManager::AssignCameraFBO(GLuint fbo) {
  cameraFBO = fbo;
}

};