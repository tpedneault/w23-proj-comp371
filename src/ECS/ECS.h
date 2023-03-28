#pragma once

#include "Core/System.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/GraphTexture.h"

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
  std::shared_ptr<GraphTexture> texture = nullptr;
  bool isVisible = true;
};

struct Camera {
  String name{};
  glm::vec3 position{};
  glm::vec3 target{};
  glm::vec3 up{};
  float fov = 90.0f;
  float nearPlane = 0.1f;
  float farPlane = 100.0f;
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
  [[nodiscard]] std::shared_ptr<GraphTexture> GetRegisteredTextureByID(U32 id);
  [[nodiscard]] std::vector<std::shared_ptr<Actor>> GetActors() const;
  [[nodiscard]] std::vector<std::shared_ptr<Light>> GetLights() const;
  [[nodiscard]] std::vector<std::shared_ptr<Camera>> GetCameras() const;
  [[nodiscard]] std::vector<std::shared_ptr<GraphTexture>> GetRegisteredTextures() const;

 private:
  void OnChangeSelectedEntity(EntityIndexInfo entityInfo);
  void OnChangeSelectedActorModel(const String& modelId);
  void OnChangeSelectedActorTexture(U32 nodeID);
  void OnRegisterTexture(const GraphTexture& texture);
  void OnUnregisterTexture(U32 nodeID);

  std::vector<std::shared_ptr<Actor>> m_Actors;
  std::vector<std::shared_ptr<Light>> m_Lights;
  std::vector<std::shared_ptr<Camera>> m_Cameras;
  std::vector<std::shared_ptr<GraphTexture>> m_RegisteredGraphTextures;

  bool m_HasSelectedEntity;
  EntityIndexInfo m_SelectedEntity;
};

};  // namespace ambr