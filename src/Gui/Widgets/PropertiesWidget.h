#pragma once 

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
      ImGui::DragFloat3(
          "Translation",
                        reinterpret_cast<float*>(&actor->transform.translation),
                        0.1f, 0.0f, 0.0f, "%.2f");
      ImGui::DragFloat3("Rotation",
                        reinterpret_cast<float*>(&actor->transform.rotation),
                        0.1f, 0.0f, 0.0f, "%.2f");
      ImGui::DragFloat3("Scale",
                        reinterpret_cast<float*>(&actor->transform.scale),
                        0.1f, 0.0f, 0.0f, "%.2f");
    }
    ImGui::End();
  }

  void SetSelectedActor(U32 id) { m_SelectedActor = id; }

 private:
  U32 m_SelectedActor = 0;
};

};  // namespace ambr