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
      auto actor = SystemLocator<ECS>::Get()->GetSelectedActor();
      if(!actor) {
        ImGui::End();
        return;
      }

      ImGui::Dummy(ImVec2(0.0f, 5.0f));
      ImGui::Text("Actor Name");
      ImGui::InputText("##Name", &actor->name);
      ImGui::Dummy(ImVec2(0.0f, 1.0f));
      ImGui::Checkbox("Is Visible", &actor->isVisible);
      ImGui::Dummy(ImVec2(0.0f, 5.0f));

      ImGui::BeginGroup();
      ImGui::Text("Transform");
      ImGui::Dummy(ImVec2(0.0f, 1.0f));
      ImGui::Text("Position");
      ImGui::DragFloat3(
          "##Position",
                        reinterpret_cast<float*>(&actor->transform.translation),
                        0.1f, 0.0f, 0.0f, "%.2f");
      ImGui::Text("Rotation");
      ImGui::DragFloat3("##Rotation",
                        reinterpret_cast<float*>(&actor->transform.rotation),
                        1.0f, 0.0f, 0.0f, "%.2f");
      ImGui::Text("Rotation");
      ImGui::DragFloat3("##Scale",
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
      const char* currentSelection = actor->model->name.c_str();
      if(ImGui::BeginCombo("##Model", currentSelection)) {
        auto models = SystemLocator<ModelManager>::Get()->GetModels();
        for(auto & model : models) {
          bool isSelected = currentSelection == model->name.c_str();
          if(ImGui::Selectable(model->name.c_str(), isSelected)) {
            PublishEvent({ EventCode::ChangeSelectedActorModel, &model->name });
          }
          if(isSelected) {
            ImGui::SetItemDefaultFocus();
          }
        }
        ImGui::EndCombo();
      }
      ImGui::EndGroup();

      ImGui::Dummy(ImVec2(0.0f, 5.0f));
      ImGui::Separator();
      ImGui::Dummy(ImVec2(0.0f, 5.0f));

    }
    ImGui::End();
  }
};

};  // namespace ambr