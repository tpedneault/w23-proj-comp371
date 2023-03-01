#include "ECS/ECS.h"

namespace ambr {

void ECS::OnInitialization(void *specs) {
  {
    auto actor = std::make_shared<Actor>();
    actor->name = "Cow";
    actor->transform = {glm::vec3(-1.0f, 0.0f, -6.0f),
                        glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, -0.8f, 1.0f)};
    actor->model = SystemLocator<ModelManager>::Get()->GetModel("car");
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

void ECS::ProcessEvent(const Event &e) {
  switch (e.code) {
    case EventCode::ChangeSelectedActor: {
      OnChangeSelectedActor(*(static_cast<U32 *>(e.data)));
      delete (U32 *) e.data;
      break;
    }
    case EventCode::ChangeSelectedActorModel:
      OnChangeSelectedActorModel(*(static_cast<String *>(e.data)));
      break;
    default:
      break;
  }
}

std::shared_ptr<Actor> ECS::GetSelectedActor() const {
  return actors[m_SelectedActor];
}

U32 ECS::GetSelectedActorIndex() const {
  return m_SelectedActor;
}

void ECS::OnChangeSelectedActor(U32 id) {
  m_SelectedActor = id;
}

void ECS::OnChangeSelectedActorModel(String modelId) {
  actors[m_SelectedActor]->model = SystemLocator<ModelManager>::Get()->GetModel(modelId);
}

};  // namespace ambr