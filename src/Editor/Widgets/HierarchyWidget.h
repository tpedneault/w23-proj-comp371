#pragma once

#include "Editor/Widget.h"

#include "ECS/ECS.h"

namespace ambr {

class HierarchyWidget : public Widget {
 public:
  explicit HierarchyWidget(const String &id) : Widget(id) {}

  void Render() override {
    auto const actors = SystemLocator<ECS>::Get()->actors;
    auto const selectedIndex = SystemLocator<ECS>::Get()->GetSelectedActorIndex();

    ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    {
      for (U32 i = 0; i < actors.size(); i++) {
        if (!actors[i]->isVisible) {
          ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(151, 151, 151, 255));
        }
        if (ImGui::Selectable(!actors[i]->name.empty() ? actors[i]->name.c_str() : "UNDEFINED",
                              selectedIndex == i)) {
          PublishEvent({EventCode::ChangeSelectedActor, new U32(i)});
        }
        if (!actors[i]->isVisible) {
          ImGui::PopStyleColor();
        }
      }
    }
    ImGui::End();
  }
};

};  // namespace ambr