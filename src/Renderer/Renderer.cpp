#include "Renderer/Renderer.h"

#include "ECS/ECS.h"

namespace Zoom {

const char* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

void Renderer::Initialization(void* specs) {
  m_Specs = *(static_cast<RendererSystemSpecifications*>(specs));

  const U32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  const U32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);

  const U32 shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

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

  glUseProgram(m_ShaderProgram);

  for (const auto& actor : SystemLocator<ECS>::Get().actors) {
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
};  // namespace Zoom