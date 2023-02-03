#include "Renderer/Modules/Framebuffer.h"

namespace Zoom {

Framebuffer::Framebuffer() {}

Framebuffer::~Framebuffer() {
}

void Framebuffer::Initialize() {
  glGenFramebuffers(1, &m_FBO);
  glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

  glGenTextures(1, &m_ColorAttachment);
  glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, nullptr);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         m_ColorAttachment, 0);

  glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
  glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Width, m_Height, 0,
               GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                         GL_TEXTURE_2D, m_DepthAttachment, 0);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  GLenum result = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
}

void Framebuffer::Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, m_FBO); }

void Framebuffer::Unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

void Framebuffer::SetSize(U32 width, U32 height) {
  m_Width = width;
  m_Height = height;
}

U32 Framebuffer::GetColorAttachmentID() const { return m_ColorAttachment; }

U32 Framebuffer::GetWidth() const { return m_Width; }

U32 Framebuffer::GetHeight() const { return m_Height; }

};  // namespace Zoom