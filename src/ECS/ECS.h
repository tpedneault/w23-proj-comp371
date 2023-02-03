#pragma once

#include "Core/System.h"
#include "ECS/Components/Mesh.h"
#include "ECS/Components/Transform.h"

namespace Zoom {

struct Actor {
  Transform transform{};
  Mesh mesh{};
};

class ECS final : public System {
 public:
  void OnInitialization(void* specs) override;
  void OnUpdate() override;
  void OnDestroy() override;

  [[nodiscard]] std::vector<std::shared_ptr<System>> GetDependencies()
      const override;

  /**
   * \brief Processes the received event.
   * \param e event to handle
   */
  void ProcessEvent(const Event& e) override {}

  std::vector<Actor> m_Actors;
};

};  // namespace Zoom