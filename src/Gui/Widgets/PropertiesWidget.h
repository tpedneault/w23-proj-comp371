#include "ECS/ECS.h"
#include "Gui/Widget.h"

namespace Zoom {

class PropertiesWidget : public Widget {
 public:
  void Render() override {
    ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    {
      // Render the scene elements here.
      auto actor = SystemLocator<ECS>::Get()->actors[m_SelectedActor];
      RenderTransformWidget(actor);
    }
    ImGui::End();
  }

  void SetSelectedActor(U32 id) { m_SelectedActor = id; }

 private:
  void RenderTransformWidget(std::shared_ptr<Actor> actor) {
    ImGui::Text("Translation");
    ImGui::DragFloat3(
        "Translation",
        reinterpret_cast<float*>(&actor->transform.translation), 0.05f, -10.0f,
        10.0f);
    ImGui::Text("Rotation");
    ImGui::DragFloat3("Rotation",
                      reinterpret_cast<float*>(&actor->transform.rotation),
                      1.0f, 0.0f, 360.0f);
    ImGui::Text("Scale");
    ImGui::DragFloat3("Scale",
                      reinterpret_cast<float*>(&actor->transform.scale), 0.05f,
                      0.0f, 5.0f);
  }

  U32 m_SelectedActor = 0;
};

};  // namespace Zoom