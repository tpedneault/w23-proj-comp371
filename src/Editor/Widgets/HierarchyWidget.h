#pragma once

#include "Editor/Widget.h"

#include "ECS/ECS.h"

namespace ambr {

class HierarchyWidget : public Widget {
 public:
  explicit HierarchyWidget(const String &id) : Widget(id) {}

  void Render() override {
    auto const actors = SystemLocator<ECS>::Get()->GetActors();
    auto const lights = SystemLocator<ECS>::Get()->GetLights();
    auto const cameras = SystemLocator<ECS>::Get()->GetCameras();
    auto const selectedEntity = SystemLocator<ECS>::Get()->GetSelectedActorIndex();

    ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    {
      if(ImGui::Button("New Actor")) {
        PublishEvent({ EventCode::CreateActorEntity });
      }

      ImGui::SameLine();
      if(ImGui::Button("New Light")) {
        PublishEvent({ EventCode::CreateLightEntity });
      }

      ImGui::SameLine();
      if(ImGui::Button("New Camera")) {
        PublishEvent({ EventCode::CreateCameraEntity });
      }

      ImGui::Dummy(ImVec2(0.0f, 2.5f));

      if (ImGui::CollapsingHeader("Entities", ImGuiTreeNodeFlags_None)) {
        for (U32 i = 0; i < actors.size(); i++) {
          if (!actors[i]->isVisible) {
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(151, 151, 151, 255));
          }
          if (ImGui::Selectable(!actors[i]->name.empty() ? actors[i]->name.c_str() : "UNDEFINED",
                                selectedEntity == i, ImGuiSelectableFlags_SelectOnClick)) {
            PublishEvent({EventCode::ChangeSelectedActor, new U32(i)});
          }
          if (!actors[i]->isVisible) {
            ImGui::PopStyleColor();
          }
        }
      }

      ImGui::Dummy(ImVec2(0.0f, 5.0f));

      if (ImGui::CollapsingHeader("Lights", ImGuiTreeNodeFlags_None)) {
        for(U32 i = 0; i < lights.size(); i++) {
          if(ImGui::Selectable(!lights[i]->name.empty() ? lights[i]->name.c_str() : "UNDEFINED")) {

          }
        }
      }

      ImGui::Dummy(ImVec2(0.0f, 5.0f));

      if (ImGui::CollapsingHeader("Cameras", ImGuiTreeNodeFlags_None)) {
        for(U32 i = 0; i < cameras.size(); i++) {
          if(ImGui::Selectable(!cameras[i]->name.empty() ? cameras[i]->name.c_str() : "UNDEFINED")) {

          }
        }
      }
    }
    ImGui::End();
  }
};

};  // namespace ambr