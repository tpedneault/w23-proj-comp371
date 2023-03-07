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
      if(!SystemLocator<ECS>::Get()->IsEntitySelected()) {
        ImGui::End();
        return;
      }

      auto entity = SystemLocator<ECS>::Get()->GetSelectedEntityInfo();
      switch(entity.entityType) {
        case EntityType::Actor:
          RenderActorProperties(SystemLocator<ECS>::Get()->GetActors()[entity.index]);
          break;
        case EntityType::Light:
          RenderLightProperties(SystemLocator<ECS>::Get()->GetLights()[entity.index]);
          break;
        case EntityType::Camera:
          RenderCameraProperties(SystemLocator<ECS>::Get()->GetCameras()[entity.index]);
          break;
      }
    }

    ImGui::End();
  }

  inline void RenderActorProperties(std::shared_ptr<Actor> actor) {
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
                      1.0f, 0.0f, 360.0f, "%.2fº");
    ImGui::Text("Scaling");
    ImGui::DragFloat3("##Scale",
                      reinterpret_cast<float*>(&actor->transform.scale),
                      0.1f, 0.0f, 1000000.0f, "%.2f");
    ImGui::DragFloat("##ScaleMultiplier", reinterpret_cast<float*>(&actor->transform.scaleMultiplier),
                     0.05f, 0.0f, 1000000.0f, "%.2f");
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

  inline void RenderLightProperties(std::shared_ptr<Light> light) {
    ImGui::Dummy(ImVec2(0.0f, 5.0f));
    ImGui::Text("Light Name");
    ImGui::InputText("##Name", &light->name);
    ImGui::Dummy(ImVec2(0.0f, 1.0f));
    ImGui::Checkbox("Is Visible", &light->isVisible);
    ImGui::Dummy(ImVec2(0.0f, 5.0f));

    ImGui::Text("Position");
    ImGui::DragFloat3(
        "##Position",
        reinterpret_cast<float*>(&light->position),
        0.1f, 0.0f, 0.0f, "%.2f");
  }

  inline void RenderCameraProperties(std::shared_ptr<Camera> camera) {
    ImGui::Dummy(ImVec2(0.0f, 5.0f));
    ImGui::Text("Camera Name");
    ImGui::InputText("##Name", &camera->name);
    ImGui::Dummy(ImVec2(0.0f, 1.0f));
    ImGui::Checkbox("Is Visible", &camera->isVisible);
    ImGui::Dummy(ImVec2(0.0f, 5.0f));

    ImGui::Text("Position");
    ImGui::DragFloat3(
        "##Position",
        reinterpret_cast<float*>(&camera->position),
        0.1f, 0.0f, 0.0f, "%.2f");
  }
};

};  // namespace ambr