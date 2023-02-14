#pragma once

#include <Gl/glew.h>

#include "Core/System.h"

#include "Renderer/Modules/Framebuffer.h"
#include "Renderer/Modules/Shader.h"

#include "Window/Window.h"

namespace ambr {

enum class RendererImplementation : U8 { OpenGL, Raytracer };

/**
 * \brief Contains any specifications to be passed to the Renderer during
 * initialization.
 */
struct RendererSystemSpecifications {
  RendererImplementation implementation;
  bool useFramebuffer;
  I32 viewportWidth, viewportHeight;
};

/**
 * \brief Implementation of the Renderer subsystem. Handles everything related
 * to rendering the 3D using OpenGL.
 */
class Renderer : public System {
 public:
  /**
   * \brief Initializes the Renderer subsystem with the given specifications.
   * \param specs Any specifications to be passed to the Renderer, nullptr if
   * none.
   */
  void OnInitialization(void* specs) override;

  /**
   * \brief Renders the current frame.
   */
  void OnUpdate() override;

  /**
   * \brief Frees the memory allocated to the renderer subsystem.
   */
  void OnDestroy() override;

  /**
   * \brief Updates the current viewport dimensions.
   * \param width of the viewport
   * \param height of the viewport
   */
  void SetViewportSize(I32 width, I32 height);

  /**
   * \brief Gets the texture ID of the rendered scene from the framebuffer. To
   * be rendered in an ImGui widget. View Editor system for usage.
   * \return ID of the texture containing the rendered scene.
   */
  [[nodiscard]] U32 GetFramebufferTextureID() const;

  [[nodiscard]] std::vector<std::shared_ptr<System>> GetDependencies()
      const override;

  /**
   * \brief Processes the received event.
   * \param e event to handle
   */
  void ProcessEvent(const Event& e) override;

 private:
  U32 m_VBO{}, m_VAO{};
  std::shared_ptr<ShaderProgram> m_ShaderProgram;
  Framebuffer m_Framebuffer;
  RendererSystemSpecifications m_Specs{};
};

};  // namespace ambr