#pragma once

#include "Core/System.h"
#include "Editor/Widgets/AssetsWidget.h"
#include "Editor/Widgets/MenuBar.h"
#include "Editor/Widgets/PropertiesWidget.h"
#include "Editor/Widgets/SceneWidget.h"
#include "Editor/Widgets/ViewportWidget.h"
#include "Editor/Widgets/ShaderEditorWidget.h"
#include "Window/Window.h"

namespace ambr {

class Editor final : public System {
 public:
  void OnInitialization(void* specs) override;
  void OnUpdate() override;
  void OnDestroy() override;

  [[nodiscard]] std::vector<std::shared_ptr<System>> GetDependencies()
      const override;

  ImGuiIO& GetIO();

  template <typename T>
  T* GetWidget(const String& id);
  void DeleteShader(const String& id);

  /**
   * \brief Processes the received event.
   * \param e event to handle
   */
  void ProcessEvent(const Event& e) override;

 private:
  std::vector<Widget*> m_Widgets;

  static void ConfigureIO();
  static void ConfigureStyle();
};

};  // namespace ambr