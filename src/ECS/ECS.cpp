#include "ECS/ECS.h"

namespace ambr {

void ECS::OnInitialization(void *specs) {
  auto light = std::make_shared<Light>();
  light->name = "Default Light";
  light->position = glm::vec3(-5.0f, 5.0f, 0.0f);
  light->color = glm::vec3(1.0f, 1.0f, 1.0f);
  light->ambientStrength = 0.1f;
  m_Lights.push_back(light);
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
    case EventCode::CreateActorEntity: {
      auto actor = std::make_shared<Actor>();
      actor->name = "New Actor";
      actor->transform = {
          {0.0f, 0.0f, 0.0f},
          {0.0f, 0.0f, 0.0f},
          {1.0f, 1.0f, 1.0f}
      };
      actor->model = SystemLocator<ModelManager>::Get()->GetDefaultModel();
      m_Actors.push_back(actor);
      break;
    }
    case EventCode::CreateLightEntity: {
      auto light = std::make_shared<Light>();
      light->name = "New Light";
      light->position = {0.0f, 0.0f, 0.0f};
      light->color = {1.0f, 1.0f, 1.0f};
      light->ambientStrength = 0.1f;
      m_Lights.push_back(light);
      break;
    }
    case EventCode::CreateCameraEntity: {
      auto camera = std::make_shared<Camera>();
      camera->name = "New Camera";
      camera->position = {0.0f, 0.0f, 0.0f};
      m_Cameras.push_back(camera);
      break;
    }
    default:
      break;
  }
}

std::shared_ptr<Actor> ECS::GetSelectedActor() const {
  if(m_Actors.empty()) {
    return nullptr;
  }
  return m_Actors[m_SelectedActor];
}

U32 ECS::GetSelectedActorIndex() const {
  return m_SelectedActor;
}

void ECS::OnChangeSelectedActor(U32 id) {
  m_SelectedActor = id;
}

void ECS::OnChangeSelectedActorModel(String modelId) {
  m_Actors[m_SelectedActor]->model = SystemLocator<ModelManager>::Get()->GetModel(modelId);
}

std::vector<std::shared_ptr<Actor>> ECS::GetActors() const {
  return m_Actors;
}

std::vector<std::shared_ptr<Light>> ECS::GetLights() const {
  return m_Lights;
}

std::vector<std::shared_ptr<Camera>> ECS::GetCameras() const {
  return m_Cameras;
}
EntityIndexInfo ECS::GetSelectedEntityInfo() const {
  return m_SelectedEntity;
}

};  // namespace ambr