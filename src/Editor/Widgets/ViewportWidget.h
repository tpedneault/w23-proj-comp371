#pragma once

#include "Editor/Widget.h"
#include "Renderer/Renderer.h"

namespace ambr {
/**
 * \brief Renders the OpenGL viewport in a widget. Needs access to the Renderer
 * subsystem to access the framebuffer.
 */
class ViewportWidget final : public Widget {
 public:
  ViewportWidget(const String& id) : Widget(id) {}

  void Render() override {
    ImGui::Begin("Scene Viewport", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    {
      // Display the rendered viewport in this window.
      const ImVec2 availableRegion = ImGui::GetContentRegionAvail();
      const ImVec2 topLeft = ImGui::GetCursorScreenPos();
      const U64 textureID = SystemLocator<Renderer>::Get()->GetFramebufferTextureID();
      ImGui::Image(reinterpret_cast<void*>(textureID), availableRegion);
      SystemLocator<Renderer>::Get()->OnViewportClicked(ImGui::GetIO(), topLeft, availableRegion);
    }
    ImGui::End();
  }
};

};  // namespace ambr