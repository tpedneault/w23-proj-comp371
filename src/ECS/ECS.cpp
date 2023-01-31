#include "ECS/ECS.h"

namespace Zoom {

void ECS::Initialization(void* specs) {
  // This is for testing purposes only.
  const std::vector vertices1 = {
      glm::vec3(-1.0f, -1.0f, 0.0f),  // left
      glm::vec3(0.0f, -1.0f, 0.0f),   // right
      glm::vec3(0.0f, 0.5f, 0.0f),    // top
  };

  Actor actor;
  actor.transform = {glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                     glm::vec3(1.0f, 1.0f, 1.0f)};
  actor.mesh = Mesh::FromVertices(vertices1);
  actors.push_back(actor);

  const std::vector vertices2 = {
      glm::vec3(0.0f, 1.0f, 0.0f),  // left
      glm::vec3(1.0f, 1.0f, 0.0f),  // right
      glm::vec3(0.0f, 0.5f, 0.0f),  // top
  };

  Actor right;
  right.transform = {glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                     glm::vec3(1.0f, 1.0f, 1.0f)};
  right.mesh = Mesh::FromVertices(vertices2);
  actors.push_back(right);
}

void ECS::Update() {}

void ECS::Destroy() {
  /**
   * TODO: Save the current state to a binary file. Load previous state
   */
}

};  // namespace Zoom