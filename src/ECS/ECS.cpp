#include "ECS/ECS.h"

namespace Zoom {

void ECS::OnInitialization(void* specs) {
  // This is for testing purposes only.
  const std::vector vertices = {
      glm::vec3(-1.0f, -1.0f, 10.0f),  // left
      glm::vec3(1.0f, -1.0f, 10.0f),   // right
      glm::vec3(0.0f, 0.5f, 10.0f),    // top
  };

  Actor actor;
  actor.transform = {glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
                     glm::vec3(5.0f, 1.0f, 1.0f)};
  actor.mesh = Mesh::FromVertices(vertices);
  m_Actors.push_back(actor);
}

void ECS::OnUpdate() {}

void ECS::OnDestroy() {
  /**
   * TODO: Save the current state to a binary file. Load previous state
   */
}

std::vector<std::shared_ptr<System>> ECS::GetDependencies() const { return {}; }

void ECS::ProcessEvent(const Event& e) {}

};  // namespace Zoom