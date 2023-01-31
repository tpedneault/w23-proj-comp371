#include "Gui/Widget.h"

namespace Zoom {

class SceneWidget : public Widget {
 public:
  void Render() override {
    ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    {
	    // Render the scene elements here.
    }
    ImGui::End();
  }
};

};  // namespace Zoom