#pragma once

#include <GL/glew.h>

#include "Core/Base.h"

namespace ambr {

enum class ShaderType : GLenum {
  Vertex = GL_VERTEX_SHADER,
  Fragment = GL_FRAGMENT_SHADER,
  Geometry = GL_GEOMETRY_SHADER,
  Compute = GL_COMPUTE_SHADER,
};

class Shader {
 public:
  static Shader* Create(ShaderType type, const String& path);

  Shader(ShaderType type);
  virtual ~Shader();

  [[nodiscard]] U32 GetID() const;

 protected:
  ShaderType m_Type;
  U32 m_Id;
};

class ShaderProgram final {
 public:
  static std::shared_ptr<ShaderProgram> Create(std::vector<Shader*> shaders);
  void Use() const;

  [[nodiscard]] U32 GetID() const;

  ShaderProgram() = default;
  virtual ~ShaderProgram() = default;

 protected:
  U32 m_Id;
};

};  // namespace ambr