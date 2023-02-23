#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/Base.h"
#include "ECS/Component.h"

namespace ambr {

struct Transform {
  glm::vec3 translation;
  glm::vec3 rotation; // Exposes the rotation as Euler angles.
  glm::vec3 scale;

  [[nodiscard]] static glm::mat4 GetTransformationMatrix(
      const Transform& transform) {

    auto matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, transform.translation);
    matrix = glm::scale(matrix, transform.scale);

    // TODO: Implement rotation by converting the rotation Euler angles to Quaternions.
    return matrix;
  }
};

};  // namespace ambr