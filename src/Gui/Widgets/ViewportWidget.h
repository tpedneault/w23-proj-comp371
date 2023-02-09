#pragma once

#include "Gui/Widget.h"
#include "Renderer/Renderer.h"

namespace ambr {
/**
 * \brief Renders the OpenGL viewport in a widget. Needs access to the Renderer
 * subsystem to access the framebuffer.
 */
class ViewportWidget final : public Widget {
 public:
  void Render() override {
    ImGui::Begin("Scene Viewport", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    {
      // Display the rendered viewport in this window.
      const ImVec2 availableRegion = ImGui::GetContentRegionAvail();
      const U64 textureID = SystemLocator<Renderer>::Get()->GetFramebufferTextureID();
      ImGui::Image(reinterpret_cast<void*>(textureID), availableRegion);
    }
    ImGui::End();
  }
};

};  // namespace ambr