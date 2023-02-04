#pragma once

namespace Zoom {

enum class ComponentType {
  Transform,
  Mesh,
};

struct Component
{
  ComponentType type;
};

};  // namespace Zoom