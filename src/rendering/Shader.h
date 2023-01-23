#pragma once

#include <GL/glew.h>
#include <memory>
#include <vector>

namespace sc {

enum class ShaderType {
  VERTEX   = GL_VERTEX_SHADER,
  FRAGMENT = GL_FRAGMENT_SHADER,
  GEOMETRY = GL_GEOMETRY_SHADER,
  COMPUTE  = GL_COMPUTE_SHADER,
};

class Shader {
 public:
  static std::shared_ptr<Shader> FromFile(ShaderType type, const std::string& path);

  explicit Shader(ShaderType type);
  virtual ~Shader();

  [[nodiscard]] GLuint GetID() const;
 private:
  GLuint m_Id;
  ShaderType m_ShaderType;

  void Init(const std::string& source);
};

class ShaderProgram {
 public:
  static std::shared_ptr<ShaderProgram> FromShaders(const std::vector<std::shared_ptr<Shader>>& shaders);

  ShaderProgram();
  virtual ~ShaderProgram();

  void Init();
  void Use();
  [[nodiscard]] GLuint GetID() const;

 private:
  GLuint m_Id{};
};

};