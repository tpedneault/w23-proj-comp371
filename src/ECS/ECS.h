#pragma once

#include "Core/System.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/Color.h"

#include "Assets/Model.h"

namespace ambr {

enum class EntityType { Actor, Light, Camera };

struct EntityIndexInfo {
  EntityType entityType;
  U32 index;
};

struct Actor {
  String name{};
  Transform transform{};
  std::shared_ptr<Model> model;
  bool isVisible = true;
};

struct Camera {
  String name{};
  glm::vec3 position{};
  bool isVisible = true;
};

struct Light {
  String name{};
  glm::vec3 position{};
  glm::vec3 color{};
  float ambientStrength;
  bool isVisible = true;
};

class ECS final : public System {
 public:
  String GetName() override { return "ECS"; }

  void OnInitialization(void *specs) override;
  void OnUpdate() override;
  void OnDestroy() override;

  [[nodiscard]] std::vector<std::shared_ptr<System>> GetDependencies() const override;

  /**
   * \brief Processes the received event.
   * \param e event to handle
   */
  void ProcessEvent(const Event &e) override;

  [[nodiscard]] bool IsEntitySelected() const;
  [[nodiscard]] EntityIndexInfo GetSelectedEntityInfo() const;
  [[nodiscard]] std::vector<std::shared_ptr<Actor>> GetActors() const;
  [[nodiscard]] std::vector<std::shared_ptr<Light>> GetLights() const;
  [[nodiscard]] std::vector<std::shared_ptr<Camera>> GetCameras() const;

 private:
  void OnChangeSelectedEntity(EntityIndexInfo entityInfo);
  void OnChangeSelectedActorModel(const String& modelId);

  std::vector<std::shared_ptr<Actor>> m_Actors;
  std::vector<std::shared_ptr<Light>> m_Lights;
  std::vector<std::shared_ptr<Camera>> m_Cameras;

  bool m_HasSelectedEntity;
  EntityIndexInfo m_SelectedEntity;
};

};  // namespace ambr