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
        if (ImGui::MenuItem("Exit")) {
          m_EventQueue.push_back({EventCode::ExitApplication});
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