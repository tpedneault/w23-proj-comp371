#pragma once

#include "ECS/Components/Mesh.h"
#include "ECS/Components/Transform.h"
#include "Core/System.h"

namespace Zoom {

struct Actor {
  Transform transform{};
  Mesh mesh{};
};

class ECS final : public System {
 public:
  void Initialization(void* specs) override;
  void Update() override;
  void Destroy() override;

  std::vector<Actor> actors;
};

};  // namespace Zoom