#pragma once

#include "Gui/Widget.h"

namespace ambr {

class MenuBar : public Widget {
 public:
  void Render() override {
    if (ImGui::BeginMainMenuBar()) {
      /* File Menu */
      if (ImGui::BeginMenu("File"))
      {
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

      /* Entity Menu */
      if (ImGui::BeginMenu("Entity")) {
        if (ImGui::MenuItem("Create Triangle")) {
        }
        if (ImGui::MenuItem("Create Square")) {
        }
        ImGui::EndMenu();
      }

      ImGui::EndMainMenuBar();
    }
  }
};

};  // namespace ambr