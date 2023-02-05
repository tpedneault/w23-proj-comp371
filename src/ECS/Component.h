#pragma once

namespace Zoom {

enum class ComponentType {
  Transform,
  Mesh,
  Color,
};

struct Component
{
  ComponentType type;
};

};  // namespace Zoom