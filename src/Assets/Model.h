#pragma once

#include "Core/System.h"

namespace ambr {

struct Model {
  U32 VAO;
  U32 VBO;
};

class ModelManager final : public System {
 public:
  static Model* FromOBJ(const String& name, const String& path);
  static Model* FromVertices(const String& name, const std::vector<float> vertices);
};

};  // namespace ambr