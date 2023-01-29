#include "Systems/Gui/Widget.h"
#include "Systems/Renderer/Renderer.h"

namespace Zoom {

class ViewportWidget : public Widget
{
public:
  void Render() override
  {
    ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    {
      // Display the rendered viewport in this window.
      ImVec2 availableRegion = ImGui::GetContentRegionAvail();
      U32 textureID = SystemLocator<Renderer>::Get().GetFramebufferTextureID();
      SystemLocator<Renderer>::Get().SetViewportSize(availableRegion.x,
                                                     availableRegion.y);
      ImGui::Image(reinterpret_cast<void*>(textureID), availableRegion);
    }
    ImGui::End();
  }
};

};