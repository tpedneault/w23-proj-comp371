#pragma once

#include <gl/glew.h>

#include "Core/Base.h"

namespace Zoom {
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
  void SetSize(U16 width, U16 height);

  /**
   * \brief Gets the Texture ID for the color attachment. This can then be used to render the texture in an ImGui widgets as an example.
   * \return ID of the color attachment.
   */
  [[nodiscard]] U32 GetColorAttachmentID() const;

 private:
  U32 m_FBO{}, m_DepthAttachment{}, m_ColorAttachment{};
  U16 m_Width{}, m_Height{};
};

};  // namespace Zoom