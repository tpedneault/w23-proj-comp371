#include "Gui/Widget.h"

#include "ECS/ECS.h"

namespace Zoom {

class SceneWidget : public Widget {
 public:
  void Render() override {
    ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    {
      // Render the scene elements here.
      auto const actors = SystemLocator<ECS>::Get()->actors;
      for (int i = 0; i < actors.size(); i++) {
        if (ImGui::Selectable(actors[i]->name.c_str(), m_SelectedActor == i)) {
          m_SelectedActor = i;
        }
      }
    }
    ImGui::End();
  }

  U32 GetSelectedActor() { return m_SelectedActor; }

 private:
  U32 m_SelectedActor = 0;
};

};  // namespace Zoom