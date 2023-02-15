#pragma once

#include "Core/Base.h"
#include "Core/EventData.h"

namespace ambr {

enum class EventCode : U16 {
  ExitApplication,
  ToggleFullscreen,
  OpenCreateEntityWidget,
  CreateEntity,
  CloseCreateEntityWidget,
  IsModelLoaded,
  LoadModelFromFile,
};

struct Event {
  EventCode code;
  void* data;
  U32 dataSize;
};

};  // namespace ambr