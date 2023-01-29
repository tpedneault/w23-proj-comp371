#include "Systems/ECS/ECS.h"

namespace Zoom {

void ECS::Initialize(void* specs) {
  // This is for testing purposes only.
  const std::vector vertices = {
      glm::vec3(-1.0f, -1.0f, 0.0f),  // left
      glm::vec3(1.0f, -1.0f, 0.0f),   // right
      glm::vec3(0.0f, 1.0f, 0.0f),    // top
  };

  Actor actor;

  actor.transform = { glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                      glm::vec3(1.0f, 1.0f, 1.0f) };

  actor.mesh = Mesh::FromVertices(vertices);

  actors.push_back(actor);
}

void ECS::Update() {}

void ECS::Destroy() {
  /**
   * TODO: Save the current state to a binary file. Load previous state
   */
}

};  // namespace Zoom