#include "Systems/Gui/Widget.h"
#include "Systems/Renderer/Renderer.h"

namespace Zoom {

class ViewportWidget : public Widget
{
public:
  inline void Render() override
  {
    ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    {
      // Display the rendered viewport in this window.
      U32 textureID = SystemLocator<Renderer>::Get().GetFramebufferTextureID();
      ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{800, 600});
    }
    ImGui::End();
  }
};

};