#pragma once

#include "Core/System.h"
#include "Window/Window.h"

#include "Editor/Widgets/AssetsWidget.h"
#include "Editor/Widgets/MenuBar.h"
#include "Editor/Widgets/PropertiesWidget.h"
#include "Editor/Widgets/HierarchyWidget.h"
#include "Editor/Widgets/ViewportWidget.h"
#include "Editor/Widgets/ShaderEditorWidget.h"
#include "Editor/Widgets/CreateEntityWidget.h"
#include "Editor/Widgets/LoadModelWidget.h"
#include "Editor/Widgets/ShaderGraph/ShaderGraphWidget.h"

namespace ambr {

class Editor final : public System {
 public:
  void OnInitialization(void *specs) override;
  void OnUpdate() override;
  void OnDestroy() override;

  [[nodiscard]] String GetName() override { return "Editor"; }
  [[nodiscard]] std::vector<std::shared_ptr<System>> GetDependencies()
  const override;

  ImGuiIO &GetIO();

  template<typename T>
  T *GetWidget(const String &id);
  void DeleteShader(const String &id);

  /**
   * \brief Processes the received event.
   * \param e event to handle
   */
  void ProcessEvent(const Event &e) override;

 private:
  std::vector<Widget *> m_Widgets;

  void DeleteWidget(const String& id);
  static void ConfigureIO();
  static void ConfigureStyle();
};

};  // namespace ambr