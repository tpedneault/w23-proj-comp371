#pragma once

#include <Gl/glew.h>
#include <GLFW/glfw3.h>

#include "Systems/System.h"

namespace Zoom {

class Renderer final : public System {
 public:
  void Initialize(void* specs) override;
  void Update() override;
  void Destroy() override;

 private:
  U32 m_VBO, m_VAO, m_ShaderProgram;
};

};  // namespace Zoom