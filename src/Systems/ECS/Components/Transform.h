#pragma once

#include <glm/glm.hpp>

#include "Systems/ECS/ECS.h"

namespace Zoom {

struct Transform {
  glm::vec3 Position;
  glm::vec3 Rotation;
  glm::vec3 Scale;
};

};  // namespace Zoom