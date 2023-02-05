#include "Gui/Widget.h"

namespace ambr {

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

};  // namespace ambr