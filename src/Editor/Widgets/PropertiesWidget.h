#pragma once 

#include "ECS/ECS.h"
#include "Editor/Widget.h"

namespace ambr {

class PropertiesWidget : public Widget {
 public:
  PropertiesWidget(const String& id) : Widget(id) {}

  void Render() override {
    ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    {
      // Render the scene elements here.
      auto actor = SystemLocator<ECS>::Get()->actors[m_SelectedActor];

    	ImGui::BeginGroup();
      ImGui::Text("Transform");
      ImGui::DragFloat3(
          "Position",
                        reinterpret_cast<float*>(&actor->transform.translation),
                        0.1f, 0.0f, 0.0f, "%.2f");
      ImGui::DragFloat3("Rotation",
                        reinterpret_cast<float*>(&actor->transform.rotation),
                        1.0f, 0.0f, 0.0f, "%.2f");
      ImGui::DragFloat3("Scale",
                        reinterpret_cast<float*>(&actor->transform.scale),
                        0.1f, 0.0f, 0.0f, "%.2f");
      ImGui::EndGroup();

      ImGui::Dummy(ImVec2(0.0f, 5.0f));
    	ImGui::Separator();
      ImGui::Dummy(ImVec2(0.0f, 5.0f));

      ImGui::BeginGroup();
      ImGui::Text("Shader");
      ImGui::EndGroup();

      ImGui::Dummy(ImVec2(0.0f, 5.0f));
      ImGui::Separator();
      ImGui::Dummy(ImVec2(0.0f, 5.0f));

      ImGui::BeginGroup();
      ImGui::Text("Model");
      ImGui::EndGroup();

      const char* currentSelection = actor->model->name.c_str();
      if(ImGui::BeginCombo("Model", currentSelection)) {
        auto models = SystemLocator<ModelManager>::Get()->GetModels();
        for(U32 i = 0; i < models.size(); i++) {
          bool isSelected = currentSelection == models[i]->name.c_str();
          if(ImGui::Selectable(models[i]->name.c_str(), isSelected)) {
            actor->model = models[i];
          }
          if(isSelected) {
            ImGui::SetItemDefaultFocus();
          }
        }
        ImGui::EndCombo();
      }

      ImGui::Dummy(ImVec2(0.0f, 5.0f));
      ImGui::Separator();
      ImGui::Dummy(ImVec2(0.0f, 5.0f));

    }
    ImGui::End();
  }

  void SetSelectedActor(U32 id) { m_SelectedActor = id; }

 private:
  U32 m_SelectedActor = 0;
};

};  // namespace ambr