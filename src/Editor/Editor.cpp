#include "Editor/Editor.h"

namespace ambr {

void Editor::OnInitialization(void *specs) {
  // Initialization the ImGui library here.
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  m_Widgets.push_back(new AssetsWidget("assets"));
  m_Widgets.push_back(new MenuBar("menu"));
  m_Widgets.push_back(new PropertiesWidget("properties"));
  m_Widgets.push_back(new SceneWidget("scene"));
  m_Widgets.push_back(new ViewportWidget("scene_viewport"));
  m_Widgets.push_back(new ShaderEditorWidget("shader_editor",
                                             new ShaderEditorSpecifications{"assets/shaders/fragment_shader.glsl ",
                                                                            "Fragment Shader"}));

  ConfigureIO();
  ConfigureStyle();

  // Initializes the ImGui backends for GLFW and OpenGL 3.3
  const auto &window = SystemLocator<Window>::Get();
  ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
  ImGui_ImplOpenGL3_Init("#version 330");

  // Initialize the widgets.
  for (const auto &widget : m_Widgets) {
    widget->OnInitialization();
  }
}

void Editor::OnUpdate() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(),
                               ImGuiDockNodeFlags_PassthruCentralNode);

  // Render all registered widgets and retrieve their events.
  for (const auto &widget : m_Widgets) {
    widget->Render();
    auto events = widget->ForwardEvents();
    for (const auto &event : events) {
      m_EventQueue.push_back(event);
    }
  }

  // Logic goes here.
  const auto scene = GetWidget<SceneWidget>("scene");
  const U32 selectedActor = scene->GetSelectedActor();

  const auto properties = GetWidget<PropertiesWidget>("properties");
  properties->SetSelectedActor(selectedActor);

  ImGui::EndFrame();
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  // Get events from the widgets and publish them.
}

void Editor::OnDestroy() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

std::vector<std::shared_ptr<System>> Editor::GetDependencies() const {
  return {SystemLocator<Window>::Get(), SystemLocator<Renderer>::Get()};
}

ImGuiIO &Editor::GetIO() { return ImGui::GetIO(); }

template<typename T>
T *Editor::GetWidget(const String &id) {
  for (const auto widget : m_Widgets) {
    if (widget->GetID() == id) {
      return reinterpret_cast<T *>(widget);
    }
  }
  return nullptr;
}

void Editor::ProcessEvent(const Event &e) {}

void Editor::ConfigureIO() {
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void Editor::ConfigureStyle() {
  constexpr auto ColorFromBytes = [](uint8_t r, uint8_t g, uint8_t b) {
    return ImVec4((float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f,
                  1.0f);
  };

  auto &style = ImGui::GetStyle();
  ImVec4 *colors = style.Colors;

  const ImVec4 bgColor = ColorFromBytes(30, 30, 30);
  const ImVec4 lightBgColor = ColorFromBytes(53, 53, 53);
  const ImVec4 veryLightBgColor = ColorFromBytes(90, 90, 90);

  const ImVec4 panelColor = ColorFromBytes(53, 54, 52);
  const ImVec4 panelHoverColor = ColorFromBytes(207, 45, 68);
  const ImVec4 panelActiveColor = ColorFromBytes(230, 50, 75);

  const ImVec4 textColor = ColorFromBytes(255, 255, 255);
  const ImVec4 textDisabledColor = ColorFromBytes(151, 151, 151);
  const ImVec4 borderColor = ColorFromBytes(65, 65, 65);

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
  colors[ImGuiCol_MenuBarBg] = bgColor;
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
  style.TabRounding = 0.5f;
}

}  // namespace ambr