#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glfw/glfw3.h>

#include "ECS/ECS.h"

namespace Zoom {

struct Transform {
  glm::vec3 translation;
  glm::vec3 rotation;
  glm::vec3 scale;

  [[nodiscard]] static const glm::mat4& GetTransformationMatrix(const Transform& transform)
  {
  	auto view = glm::mat4(1.0f);
    view = glm::translate(view, transform.translation);
    view = glm::rotate(view, static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));

    return view;
  }
};

};  // namespace Zoom