#pragma once

#include "Editor/Widget.h"

namespace ambr {

class AssetsWidget : public Widget {
 public:
  AssetsWidget(const String& id) : Widget(id) {}

  void Render() override {
    ImGui::Begin("Assets", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    {
      // Render the scene elements here.
    }
    ImGui::End();
  }
};

};  // namespace ambr