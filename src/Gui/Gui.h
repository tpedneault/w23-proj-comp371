#pragma once

#include "Gui/Widgets/AssetsWidget.h"
#include "Gui/Widgets/PropertiesWidget.h"
#include "Gui/Widgets/SceneWidget.h"
#include "Gui/Widgets/ViewportWidget.h"

#include "Core/System.h"
#include "Window/Window.h"

namespace Zoom {

class Gui final : public System {
 public:
  void Initialization(void* specs) override;
  void Update() override;
  void Destroy() override;

  ImGuiIO& GetIO();

 private:
  std::vector<Widget*> m_Widgets;

  static void ConfigureIO();
  static void ConfigureStyle();
};

};  // namespace Zoom