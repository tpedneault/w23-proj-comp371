#pragma once

#include "Core/System.h"

#include "Gui/Widgets/MenuBar.h"
#include "Gui/Widgets/PropertiesWidget.h"
#include "Gui/Widgets/SceneWidget.h"
#include "Gui/Widgets/ViewportWidget.h"

#include "Window/Window.h"

namespace Zoom {

class Gui final : public System {
 public:
  void OnInitialization(void* specs) override;
  void OnUpdate() override;
  void OnDestroy() override;

  [[nodiscard]] std::vector<std::shared_ptr<System>> GetDependencies() const override;

  ImGuiIO& GetIO();

  /**
   * \brief Processes the received event.
   * \param e event to handle
   */
  void ProcessEvent(const Event& e) override;

 private:
  MenuBar m_MenuBar;
  PropertiesWidget m_PropertiesWidget;
  SceneWidget m_SceneWidget;
  ViewportWidget m_ViewportWidget;

  static void ConfigureIO();
  static void ConfigureStyle();
};

};  // namespace Zoom