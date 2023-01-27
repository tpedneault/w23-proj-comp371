#include "Systems/Gui/Widget.h"

namespace Zoom {

class ViewportWidget : public Widget
{
public:
  inline void Render() override
  {
    ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    {
      // Display the rendered viewport in this window.
    }
    ImGui::End();
  }
};

};