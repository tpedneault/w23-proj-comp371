#include "ECS/ECS.h"

namespace ambr {

void ECS::OnInitialization(void *specs) {
  {
    auto actor = std::make_shared<Actor>();
    actor->name = "Cow";
    actor->transform = {glm::vec3(-1.0f, 0.0f, -6.0f),
                        glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, -0.8f, 1.0f)};
    actor->model = SystemLocator<ModelManager>::Get()->GetModel("mini_tank");
    actors.push_back(actor);
  }

  {
    auto light = std::make_shared<Light>();
    light->name = "Light";
    light->position = glm::vec3(-5.0f, 5.0f, 0.0f);
    light->color = glm::vec3(1.0f, 1.0f, 1.0f);
    light->ambientStrength = 0.6f;
    lights.push_back(light);
  }
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

void ECS::ProcessEvent(const Event &e) {}

};  // namespace ambr