#pragma once

#include "Core/System.h"
#include "Gui/Widgets/AssetsWidget.h"
#include "Gui/Widgets/MenuBar.h"
#include "Gui/Widgets/PropertiesWidget.h"
#include "Gui/Widgets/SceneWidget.h"
#include "Gui/Widgets/ViewportWidget.h"
#include "Gui/Widgets/ShaderEditorWidget.h"
#include "Window/Window.h"

namespace ambr {

enum class Widgets : U8 { Assets, MenuBar, Properties, Scene, Viewport, ShaderEditor };

class Gui final : public System {
 public:
  void OnInitialization(void* specs) override;
  void OnUpdate() override;
  void OnDestroy() override;

  [[nodiscard]] std::vector<std::shared_ptr<System>> GetDependencies()
      const override;

  ImGuiIO& GetIO();

  /**
   * \brief Processes the received event.
   * \param e event to handle
   */
  void ProcessEvent(const Event& e) override;

 private:
  std::map<Widgets, Widget*> m_Widgets;

  static void ConfigureIO();
  static void ConfigureStyle();
};

};  // namespace ambr