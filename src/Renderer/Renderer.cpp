#include "Renderer/Renderer.h"

#include "ECS/ECS.h"

namespace Zoom {

void Renderer::Initialization(void* specs) {
  m_Specs = *(static_cast<RendererSystemSpecifications*>(specs));

  auto vertex =
      Shader::Create(ShaderType::Vertex, "assets/shaders/vertex_shader.glsl");
  auto frag =
      Shader::Create(ShaderType::Fragment, "assets/shaders/frag_shader.glsl");
  m_ShaderProgram = ShaderProgram::Create({vertex, frag}, true);

  SetViewportSize(m_Specs.viewportWidth, m_Specs.viewportHeight);
}

void Renderer::Update() {
  // Clear the main window.
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // !! ANYTHING FROM THIS POINT ON IS RENDERED TO THE FRAMEBUFFER !!.
  if (m_Specs.useFramebuffer) {
    m_Framebuffer.Bind();
  }

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  m_ShaderProgram->Use();

  for (const auto& actor : SystemLocator<ECS>::Get()->actors) {
    glBindVertexArray(actor.mesh.GetVAO());
    glDrawArrays(GL_TRIANGLES, 0, actor.mesh.GetSize());
  }

  if (m_Specs.useFramebuffer) {
    m_Framebuffer.Unbind();
  }
}

void Renderer::Destroy() {}

void Renderer::SetViewportSize(const I32 width, const I32 height) {
  glViewport(0, 0, width, height);

  m_Framebuffer.SetSize(width, height);
  m_Framebuffer.Initialize();
}

U32 Renderer::GetFramebufferTextureID() const {
  return m_Framebuffer.GetColorAttachmentID();
}

std::vector<std::shared_ptr<System>> Renderer::GetDependencies() const {
  return {SystemLocator<ECS>::Get()};
}
};  // namespace Zoom