#include "Renderer/Renderer.h"

#include "ECS/ECS.h"

namespace ambr {

void Renderer::OnInitialization(void* specs) {
  m_Specs = *(static_cast<RendererSystemSpecifications*>(specs));

  auto vertex =
      Shader::Create(ShaderType::Vertex, "assets/shaders/vertex_shader.glsl");
  auto frag =
      Shader::Create(ShaderType::Fragment, "assets/shaders/frag_shader.glsl");

  m_ShaderProgram = ShaderProgram::Create({vertex, frag});

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
  for (const auto& actor : SystemLocator<ECS>::Get()->actors) {
    glm::mat4 transform = Transform::GetTransformationMatrix(actor->transform);

    glm::mat4 mvp = projection * transform;

    const I32 mvpUniform =
        glGetUniformLocation(m_ShaderProgram->GetID(), "mvp");
    glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, glm::value_ptr(mvp));

    for(const auto& mesh : actor->model->meshes) {
      glBindVertexArray(mesh->vertexArray);
      glDrawElements(GL_TRIANGLE_STRIP, mesh->indexCount, GL_UNSIGNED_INT, nullptr);
      glBindVertexArray(0);
    }
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
  return {SystemLocator<Window>::Get()};
}
void Renderer::ProcessEvent(const Event& e) {}

};  // namespace ambr