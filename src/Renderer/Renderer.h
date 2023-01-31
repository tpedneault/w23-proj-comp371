#pragma once

#include <Gl/glew.h>
#include "Core/System.h"
#include "Renderer/Modules/Framebuffer.h"

namespace Zoom {

enum class RendererImplementation : U8 {
  OpenGL,
  Raytracer
};

/**
 * \brief Contains any specifications to be passed to the Renderer during
 * initialization.
 */
struct RendererSystemSpecifications {
  RendererImplementation implementation;
  bool useFramebuffer;
  I32 viewportWidth = 800, viewportHeight = 600;
};

/**
 * \brief Implementation of the Renderer subsystem. Handles everything related
 * to rendering the 3D using OpenGL.
 */
class Renderer : public System {
 public:
  static Renderer& Create(const RendererSystemSpecifications& specs);

  /**
   * \brief Initializes the Renderer subsystem with the given specifications.
   * \param specs Any specifications to be passed to the Renderer, nullptr if
   * none.
   */
  void Initialization(void* specs) override;

  /**
   * \brief Renders the current frame.
   */
  void Update() override;

  /**
   * \brief Frees the memory allocated to the renderer subsystem.
   */
  void Destroy() override;

  /**
   * \brief Updates the current viewport dimensions.
   * \param width of the viewport
   * \param height of the viewport
   */
  void SetViewportSize(I32 width, I32 height);

  /**
   * \brief Gets the texture ID of the rendered scene from the framebuffer. To
   * be rendered in an ImGui widget. View Gui system for usage.
   * \return ID of the texture containing the rendered scene.
   */
  [[nodiscard]] U32 GetFramebufferTextureID() const;

 private:
  U32 m_VBO{}, m_VAO{}, m_ShaderProgram{};
  Framebuffer m_Framebuffer;
  RendererSystemSpecifications m_Specs{};
};

};  // namespace Zoom