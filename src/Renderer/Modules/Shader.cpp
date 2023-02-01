#include "Renderer/Modules/Shader.h"

namespace Zoom {

Shader* Shader::Create(ShaderType type, const String& path) {
  auto* shader = new Shader(type);

  std::ifstream fin(path);
  std::stringstream buffer;
  buffer << fin.rdbuf();

  const char* source = buffer.str().c_str();
  shader->m_Id = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(shader->m_Id, 1, &source, nullptr);
  glCompileShader(shader->m_Id);

  return shader;
}

U32 Shader::GetID() const { return m_Id; }

Shader::Shader(ShaderType type) : m_Type(type) {}

Shader::~Shader() { glDeleteShader(m_Id); }

std::shared_ptr<ShaderProgram> ShaderProgram::Create(
    std::vector<Shader*> shaders, bool deleteShaders = false) {
  auto program = std::make_shared<ShaderProgram>();
  program->m_Id = glCreateProgram();
  for (const auto shader : shaders) {
    glAttachShader(program->m_Id, shader->GetID());
  }
  glLinkProgram(program->m_Id);

  if (deleteShaders) {
    for (Shader* shader : shaders) {
      delete shader;
    }
  }

  return program;
}

void ShaderProgram::Use() { glUseProgram(m_Id); }
}  // namespace Zoom