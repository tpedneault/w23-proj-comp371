#include "Gui/Widget.h"

namespace Zoom {

class PropertiesWidget : public Widget {
 public:
  void Render() override {
    ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    {
      // Render the scene elements here.
    }
    ImGui::End();
  }
};

};  // namespace Zoom