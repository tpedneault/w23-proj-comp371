#pragma once

#include "Systems/System.h"
#include "Systems/Window/Window.h"
#include "Systems/Gui/Widget.h"
#include "Systems/Gui/Widgets/ViewportWidget.h"

namespace Zoom {

class Gui final : public System
{
public:
  void Initialize(void* specs) override;
  void Update() override;
  void Destroy() override;

  ImGuiIO& GetIO();

private:
  std::vector<Widget*> m_Widgets;

  static void ConfigureIO();
  static void ConfigureStyle();
};

};