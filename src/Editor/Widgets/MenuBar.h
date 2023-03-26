#pragma once

#include "Editor/Widget.h"

namespace ambr {

class MenuBar : public Widget {
 public:
  MenuBar(const String& id) : Widget(id) {}

  void Render() override {
    if (ImGui::BeginMainMenuBar()) {
      /* File Menu */
      if (ImGui::BeginMenu("File"))
      {
        if(ImGui::MenuItem("Import Model")) {
          PublishEvent({ EventCode::Editor_OpenLoadModelWindow });
        }

        if (ImGui::MenuItem("Exit")) {
          PublishEvent({ EventCode::ExitApplication });
        }
        ImGui::EndMenu();
      }

      if(ImGui::BeginMenu("Shader Graph")) {
        if(ImGui::MenuItem("Add Node")) {
          PublishEvent({ EventCode::ShaderGraph_PushNode });
        }

        if(ImGui::MenuItem("Remove Node")) {
          PublishEvent({ EventCode::ShaderGraph_PopNode });
        }

        ImGui::EndMenu();
      }

      /* Edit Menu */
      if (ImGui::BeginMenu("Edit"))
      {
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("View"))
      {
        ImGui::EndMenu();
      }

      ImGui::EndMainMenuBar();
    }
  }
};

};  // namespace ambr