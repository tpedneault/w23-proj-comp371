#include "Renderer.h"

namespace sc {

void RenderingManager::Start() {
  auto vertex = Shader::FromFile(ShaderType::VERTEX, "shaders/base.vert");
  auto fragment = Shader::FromFile(ShaderType::FRAGMENT, "shaders/base.frag");
  m_ShaderProgram = ShaderProgram::FromShaders({ vertex, fragment });
}

void RenderingManager::Update() {
  m_ShaderProgram->Use();
}

void RenderingManager::Close() {
  glDeleteVertexArrays(1, &m_VAO);
  glDeleteBuffers(1, &m_VBO);
}

};

