#pragma once

#include <Gl/glew.h>

#include "Systems/Renderer/Framebuffer.h"
#include "Systems/System.h"

namespace Zoom {

class Renderer final : public System {
 public:
  void Initialize(void* specs) override;
  void Update() override;
  void Destroy() override;

  void SetViewportSize(U16 width, U16 height);

  [[nodiscard]] U32 GetFramebufferTextureID() const;

private:
  U32 m_VBO, m_VAO, m_ShaderProgram;
  U16 m_ViewportWidth, m_ViewportHeight;
  Framebuffer m_Framebuffer;
};

};  // namespace Zoom