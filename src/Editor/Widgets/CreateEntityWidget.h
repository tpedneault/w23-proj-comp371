#pragma once

#include "Editor/Widget.h"

namespace ambr {

class CreateEntityWidget : public Widget {
 public:
  CreateEntityWidget(const String& id) : Widget(id) {}

  void Render() override {
    ImGui::Begin("Create New Entity...", nullptr, ImGuiWindowFlags_Popup);
    {
    }
    ImGui::End();
  }

};

};