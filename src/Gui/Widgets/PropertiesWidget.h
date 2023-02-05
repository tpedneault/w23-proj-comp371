#include "ECS/ECS.h"
#include "Gui/Widget.h"

namespace ambr {

class PropertiesWidget : public Widget {
 public:
  void Render() override {
    ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    {
      // Render the scene elements here.
      auto actor = SystemLocator<ECS>::Get()->actors[m_SelectedActor];
    }
    ImGui::End();
  }

  void SetSelectedActor(U32 id) { m_SelectedActor = id; }

 private:
  U32 m_SelectedActor = 0;
};

};  // namespace ambr