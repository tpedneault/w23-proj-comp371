#pragma once

#include <gl/glew.h>

#include "Core/Base.h"

namespace Zoom {

class Framebuffer {
 public:
  Framebuffer() = default;
  virtual ~Framebuffer();
  void Invalidate();
  void Bind() const;
  void Unbind() const;

  void SetSize(U16 width, U16 height);
  [[nodiscard]] U32 GetColorAttachmentID() const;

private:
  U32 m_FBO{}, m_DepthAttachment{}, m_ColorAttachment{};
  U16 m_Width{}, m_Height{};
  bool m_Initialized = false;
};

};  // namespace Zoom