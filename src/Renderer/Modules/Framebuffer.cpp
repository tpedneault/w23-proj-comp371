#include "Renderer/Modules/Framebuffer.h"

namespace ambr {

Framebuffer::Framebuffer() {}

Framebuffer::~Framebuffer() {
}

void Framebuffer::Initialize() {
  glGenFramebuffers(1, &m_FBO);
  glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

  // Generate multi sampled color attachment texture
  glGenTextures(1, &m_ColorAttachment);
  glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_ColorAttachment);
  glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 16, GL_RGB, m_Width, m_Height, GL_TRUE);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_ColorAttachment, 0);

  // Generate multi sampled depth attachment texture
  glGenTextures(1, &m_DepthAttachment);
  glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_DepthAttachment);
  glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 16, GL_DEPTH24_STENCIL8, m_Width, m_Height, GL_TRUE);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, m_DepthAttachment, 0);

  // Create blit framebuffer
  glGenFramebuffers(1, &m_BlitFBO);
  glBindFramebuffer(GL_FRAMEBUFFER, m_BlitFBO);

  // Create color attachment texture
  glGenTextures(1, &m_BlitColorAttachment);
  glBindTexture(GL_TEXTURE_2D, m_BlitColorAttachment);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_BlitColorAttachment, 0);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if(result != GL_FRAMEBUFFER_COMPLETE) {
    AMBR_LOG_ERROR(fmt::format("Framebuffer error: {}", result));
  }
}

void Framebuffer::Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, m_FBO); }

void Framebuffer::Unbind() const {
  glBindFramebuffer(GL_READ_FRAMEBUFFER, m_FBO);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_BlitFBO);
  glBlitFramebuffer(0, 0, m_Width, m_Height, 0, 0, m_Width, m_Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::SetSize(U32 width, U32 height) {
  m_Width = width;
  m_Height = height;
}

U32 Framebuffer::GetColorAttachmentID() const { return m_BlitColorAttachment; }

U32 Framebuffer::GetWidth() const { return m_Width; }

U32 Framebuffer::GetHeight() const { return m_Height; }

};  // namespace ambr