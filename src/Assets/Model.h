#pragma once

#include "Core/System.h"

namespace Zoom {

struct Model {
  U32 VAO;
  U32 VBO;
};

class ModelManager final : public System {
 public:
  static Model* FromOBJ(const String& name, const String& path);
  static Model* FromVertices(const String& name, const std::vector<float> vertices);
};

};  // namespace Zoom