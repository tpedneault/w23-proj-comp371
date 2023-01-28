#pragma once

#include "Systems/ECS/Components/Mesh.h"
#include "Systems/ECS/Components/Transform.h"
#include "Systems/System.h"

namespace Zoom {

struct Actor {
  Transform transform{};
  Mesh mesh{};
};

class ECS final : public System {
 public:
  void Initialize(void* specs) override;
  void Update() override;
  void Destroy() override;

  std::vector<Actor> actors;
};

};  // namespace Zoom