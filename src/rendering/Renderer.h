#pragma once

#include "GL/glew.h"
#include "core/SystemManager.h"
#include "Shader.h"

namespace sc {

class RenderingManager : public SystemManager {
 public:
  RenderingManager() {}
  virtual ~RenderingManager() = default;

  void Start() override;
  void Update() override;
  void Close() override;

  [[nodiscard]] GLuint GetSceneFBO() const { return m_FBO; }

 private:
  std::shared_ptr<ShaderProgram> m_ShaderProgram;
  GLuint m_FBO, m_TextureColorBuffer;
  GLuint m_VBO, m_VAO;
  GLuint m_Width, m_Height;
};

};