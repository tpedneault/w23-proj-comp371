#include "ECS/ECS.h"

namespace ambr {

void ECS::OnInitialization(void* specs) {
  auto actor = std::make_shared<Actor>();
  actor->name = "Cow";
  actor->transform = {glm::vec3(-1.0f, 0.0f, -6.0f),
                      glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)};
  actor->model = SystemLocator<ModelManager>::Get()->GetModel("couch");
  actors.push_back(actor);
}

void ECS::OnUpdate() {}

void ECS::OnDestroy() {
  /**
   * TODO: Save the current state to a binary file. Load previous state
   */
}

std::vector<std::shared_ptr<System>> ECS::GetDependencies() const {
  return {SystemLocator<ModelManager>::Get()};
}

void ECS::ProcessEvent(const Event& e) {}

};  // namespace ambr