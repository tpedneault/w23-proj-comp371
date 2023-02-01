#pragma once

#include <GL/glew.h>

#include "Core/Base.h"

namespace Zoom {

enum class ShaderType : GLenum {
  Vertex = GL_VERTEX_SHADER,
  Fragment = GL_FRAGMENT_SHADER
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
  static std::shared_ptr<ShaderProgram> Create(std::vector<Shader*> shaders,
                                               bool deleteShaders);
  void Use();

  ShaderProgram() = default;
  virtual ~ShaderProgram() = default;

 protected:
  U32 m_Id;
};

};  // namespace Zoom