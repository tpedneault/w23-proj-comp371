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
    AMBR_LOG_ERROR(fmt::format("Failed to load shader {}, err={}", path, std::string(errorLog.begin(), errorLog.end())));

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
    AMBR_LOG_ERROR(output);

    return nullptr;
  }

  return program;
}

void ShaderProgram::Use() const { glUseProgram(m_Id); }

U32 ShaderProgram::GetID() const { return m_Id; }

I32 ShaderProgram::SetUniform(const String& name, const glm::mat4& value) const {
  I32 location = glGetUniformLocation(m_Id, name.c_str());
  if(location >= 0) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
  } else {
    AMBR_LOG_WARN(fmt::format("Failed to load uniform {}.", name));
  }
  return location;
}

I32 ShaderProgram::SetUniform(const String& name, const glm::vec3& value) const {
  I32 location = glGetUniformLocation(m_Id, name.c_str());
  if(location >= 0) {
    glUniform3f(location, value.x, value.y, value.z);
  } else {
    AMBR_LOG_WARN(fmt::format("Failed to load uniform {}.", name));
  }
  return location;
}

I32 ShaderProgram::SetUniform(const String& name, float value) const {
  I32 location = glGetUniformLocation(m_Id, name.c_str());
  if(location >= 0) {
    glUniform1f(location, value);
  } else {
    AMBR_LOG_WARN(fmt::format("Failed to load uniform {}.", name));
  }
  return location;
}

I32 ShaderProgram::SetUniform(const String& name, U32 value) const {
  I32 location = glGetUniformLocation(m_Id, name.c_str());
  if(location >= 0) {
    glUniform1i(location, value);
  } else {
    AMBR_LOG_WARN(fmt::format("Failed to load uniform {}.", name));
  }
  return location;
}

}  // namespace ambr