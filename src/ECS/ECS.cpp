#include "ECS/ECS.h"

namespace ambr {

void ECS::OnInitialization(void* specs) {
  // This is for testing purposes only.
  const std::vector vertices = {
      glm::vec3(-1.0f, -1.0f, 10.0f),  // left
      glm::vec3(1.0f, -1.0f, 10.0f),   // right
      glm::vec3(0.0f, 0.5f, 7.5f),     // top
  };

  {
    auto actor = std::make_shared<Actor>();
    actor->name = "Triangle 1";
    actor->transform = {glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(1.0f, 1.0f, 1.0f)};
    actor->mesh = Mesh::FromVertices(vertices);
    actors.push_back(actor);
  }

  {
    auto actor = std::make_shared<Actor>();
    actor->name = "Triangle 2";
    actor->transform = {glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(1.0f, 1.0f, 1.0f)};
    actor->mesh = Mesh::FromVertices(vertices);
    actors.push_back(actor);
  }

  {
    auto actor = std::make_shared<Actor>();
    actor->name = "Triangle 3";
    actor->transform = {glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(1.0f, 1.0f, 1.0f)};
    actor->mesh = Mesh::FromVertices(vertices);
    actors.push_back(actor);
  }

  { auto actor = std::make_shared<Actor>();
    actor->name = "Cursed Cow";
    actor->transform = {glm::vec3(-1.0f, 0.0f, -6.0f),
                        glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(1.0f, 1.0f, 1.0f)};
    actor->mesh = Mesh::FromModel("cow");
    actors.push_back(actor);
  }
}

void ECS::OnUpdate() {}

void ECS::OnDestroy() {
  /**
   * TODO: Save the current state to a binary file. Load previous state
   */
}

std::vector<std::shared_ptr<System>> ECS::GetDependencies() const { return { SystemLocator<ModelManager>::Get() }; }

void ECS::ProcessEvent(const Event& e) {}

};  // namespace ambr