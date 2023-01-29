#include "Systems/Gui/Widget.h"

namespace Zoom {

class AssetsWidget : public Widget {
 public:
  void Render() override {
    ImGui::Begin("Assets", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    {
      // Render the scene elements here.
    }
    ImGui::End();
  }
};

};  // namespace Zoom