#pragma once

#include <gl/glew.h>

#include "Core/Base.h"

namespace Zoom {

class Framebuffer {
 public:
  void Initialize();
  void Bind() const;
  void Unbind() const;
  void Destroy();

  [[nodiscard]] U32 GetTextureID() const { return m_Texture; }

 private:
  U32 m_FBO{}, m_RBO{}, m_Texture{};
};

};  // namespace Zoom