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

  [[nodiscard]] U32 GetFramebufferTextureID() const { return m_Framebuffer.GetTextureID(); }

 private:
  U32 m_VBO, m_VAO, m_ShaderProgram;
  Framebuffer m_Framebuffer;
};

};  // namespace Zoom