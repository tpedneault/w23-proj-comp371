#include "Renderer/Modules/Shader.h"

namespace ambr {

Shader* Shader::Create(ShaderType type, const String& path) {
  const auto shader = new Shader(type);

  const std::ifstream fin(path);
  std::stringstream buffer;
  buffer << fin.rdbuf();

  const String sourceData = buffer.str();
  const char* source = sourceData.c_str();
  shader->m_Id = glCreateShader(static_cast<GLenum>(type));
  glShaderSource(shader->m_Id, 1, &source, nullptr);
  glCompileShader(shader->m_Id);

  GLint isCompiled = 0;
  glGetShaderiv(shader->m_Id, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(shader->m_Id, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> errorLog(maxLength);
    glGetShaderInfoLog(shader->m_Id, maxLength, &maxLength, errorLog.data());

    glDeleteShader(shader->m_Id);

    return nullptr;
  }

  return shader;
}

U32 Shader::GetID() const { return m_Id; }

Shader::Shader(ShaderType type) : m_Type(type) {}

Shader::~Shader() { glDeleteShader(m_Id); }

std::shared_ptr<ShaderProgram> ShaderProgram::Create(
    std::vector<Shader*> shaders) {
  auto program = std::make_shared<ShaderProgram>();
  program->m_Id = glCreateProgram();
  for (const auto shader : shaders) {
    glAttachShader(program->m_Id, shader->GetID());
  }
  glLinkProgram(program->m_Id);

  for (const auto shader : shaders) {
    glDetachShader(program->m_Id, shader->GetID());
  }

  GLint isLinked = 0;
  glGetProgramiv(program->m_Id, GL_LINK_STATUS, &isLinked);
  if (isLinked == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(program->m_Id, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(program->m_Id, maxLength, &maxLength, infoLog.data());

    glDeleteProgram(program->m_Id);

    std::string output(infoLog.begin(), infoLog.end());
    ZOOM_LOG_ERROR(output);

    return nullptr;
  }

  return program;
}

void ShaderProgram::Use() const { glUseProgram(m_Id); }

U32 ShaderProgram::GetID() const { return m_Id; }

}  // namespace ambr