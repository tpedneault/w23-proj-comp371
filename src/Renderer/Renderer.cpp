#include "Renderer/Renderer.h"

#include "ECS/ECS.h"

namespace Zoom {

void Renderer::OnInitialization(void* specs) {
  m_Specs = *(static_cast<RendererSystemSpecifications*>(specs));

  auto vertex =
      Shader::Create(ShaderType::Vertex, "assets/shaders/vertex_shader.glsl");
  auto frag =
      Shader::Create(ShaderType::Fragment, "assets/shaders/frag_shader.glsl");

  m_ShaderProgram = ShaderProgram::Create({vertex, frag});

  delete vertex;
  delete frag;

  glEnable(GL_DEPTH_TEST);

  SetViewportSize(m_Specs.viewportWidth, m_Specs.viewportHeight);
}

void Renderer::OnUpdate() {
  // Clear the main window.
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // !! ANYTHING FROM THIS POINT ON IS RENDERED TO THE FRAMEBUFFER !!.
  if (m_Specs.useFramebuffer) {
    m_Framebuffer.Bind();
  }

  glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_ShaderProgram->Use();

  // TODO: Move the perspective matrix to the Camera class.
  const glm::mat4 projection = glm::perspective(
      glm::radians(45.0f),
      static_cast<float>(m_Framebuffer.GetWidth()) / m_Framebuffer.GetHeight(),
      0.1f, 100.0f);

  // TODO: Move to the ActorRenderer class.
  for (auto& actor : SystemLocator<ECS>::Get()->actors) {
    glm::mat4 transform = Transform::GetTransformationMatrix(actor->transform);

    glm::mat4 mvp = projection * transform;
    const I32 uniformID = glGetUniformLocation(m_ShaderProgram->GetID(), "mvp");
    glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(mvp));

    glBindVertexArray(actor->mesh.GetVAO());
    glDrawArrays(GL_TRIANGLES, 0, actor->mesh.GetSize());
  }

  if (m_Specs.useFramebuffer) {
    m_Framebuffer.Unbind();
  }
}

void Renderer::OnDestroy() {}

void Renderer::SetViewportSize(const I32 width, const I32 height) {
  glViewport(0, 0, width, height);

  m_Framebuffer.SetSize(width, height);
  m_Framebuffer.Initialize();
}

U32 Renderer::GetFramebufferTextureID() const {
  return m_Framebuffer.GetColorAttachmentID();
}

std::vector<std::shared_ptr<System>> Renderer::GetDependencies() const {
  return {SystemLocator<Window>::Get(), SystemLocator<ECS>::Get()};
}
void Renderer::ProcessEvent(const Event& e) {}
};  // namespace Zoom