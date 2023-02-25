#pragma once

#include "Core/System.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/Color.h"

#include "Assets/Model.h"

namespace ambr {

struct Actor {
  String name{};
  Transform transform{};
  std::shared_ptr<Model> model;
};

struct Camera {
  String name{};
  glm::vec3 position{};
};

struct Light {
  String name{};
  glm::vec3 position{};
  glm::vec3 color{};
  float ambientStrength;
};

class ECS final : public System {
 public:
  virtual String GetName() override { return "ECS"; }

  void OnInitialization(void *specs) override;
  void OnUpdate() override;
  void OnDestroy() override;

  [[nodiscard]] std::vector<std::shared_ptr<System>> GetDependencies() const override;

  /**
   * \brief Processes the received event.
   * \param e event to handle
   */
  void ProcessEvent(const Event &e) override;

  std::vector<std::shared_ptr<Actor>> actors;
  std::vector<std::shared_ptr<Light>> lights;
  Camera camera;
};

};  // namespace ambr