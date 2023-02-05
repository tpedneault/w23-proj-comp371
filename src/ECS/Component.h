#pragma once

namespace ambr {

enum class ComponentType {
  Transform,
  Mesh,
  Color,
};

struct Component
{
  ComponentType type;
};

};  // namespace ambr