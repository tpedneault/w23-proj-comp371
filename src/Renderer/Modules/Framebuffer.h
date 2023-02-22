#pragma once

#include <GL/glew.h>

#include "Core/Base.h"

namespace ambr {
/**
 * \brief Implementation of the OpenGL framebuffer. Once the framebuffer is
 * bound, any rendering performed is stored as a Texture.
 */
class Framebuffer {
 public:
  Framebuffer();
  virtual ~Framebuffer();

  /**
   * \brief Initializes the framebuffer using the OpenGL pipeline.
   */
  void Initialize();

  /**
   * \brief Binds the framebuffer, any rendering operations performed after this
   * will result in the scene being rendered to the framebuffer.
   */
  void Bind() const;

  /**
   * \brief Unbinds the framebuffer, any rendering operations performed after
   * this will result in the scene being rendered to the window.
   */
  void Unbind() const;

  /**
   * \brief Sets the size of the framebuffer.
   * \param width of the framebuffer.
   * \param height of the framebuffer.
   */
  void SetSize(U32 width, U32 height);

  /**
   * \brief Gets the Texture ID for the color attachment. This can then be used
   * to render the texture in an ImGui widgets as an example. \return ID of the
   * color attachment.
   */
  [[nodiscard]] U32 GetColorAttachmentID() const;

  [[nodiscard]] U32 GetWidth() const;

  [[nodiscard]] U32 GetHeight() const;

 private:
  U32 m_FBO{}, m_DepthAttachment{}, m_ColorAttachment{};
  U32 m_Width{}, m_Height{};
};

};  // namespace ambr