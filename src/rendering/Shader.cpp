#include <fstream>
#include <sstream>
#include "Shader.h"

namespace sc {

std::shared_ptr<Shader> sc::Shader::FromFile(sc::ShaderType type, const std::string &path) {
  std::ifstream fin(path);
  std::stringstream buffer;
  buffer << fin.rdbuf();

  auto shader = std::make_shared<Shader>(type);
  shader->Init(buffer.str());
  return shader;
}

Shader::Shader(sc::ShaderType type) : m_Id(0), m_ShaderType(type) {}

Shader::~Shader() {
  glDeleteShader(m_Id);
}

GLuint Shader::GetID() const {
  return m_Id;
}

void Shader::Init(const std::string &source) {
  m_Id = glCreateShader(static_cast<GLenum>(m_ShaderType));
  const char* str = source.c_str();
  glShaderSource(m_Id, 1, &str, nullptr);
  glCompileShader(m_Id);
}

std::shared_ptr<ShaderProgram> ShaderProgram::FromShaders(const std::vector<std::shared_ptr<Shader>> &shaders) {
  auto program = std::make_shared<ShaderProgram>();
  program->Init();
  for(const auto& shader : shaders) {
    glAttachShader(program->GetID(), shader->GetID());
  }
  glLinkProgram(program->GetID());
  return program;
}

ShaderProgram::ShaderProgram() = default;

ShaderProgram::~ShaderProgram() = default;

void ShaderProgram::Init() {
  m_Id = glCreateProgram();
}

void ShaderProgram::Use() {
  glUseProgram(m_Id);
}

GLuint ShaderProgram::GetID() const {
  return m_Id;
}

};