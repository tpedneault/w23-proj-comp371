#pragma once

#include "Core/Base.h"

namespace ambr {

enum class EventCode : U16 {
  ExitApplication,
  ChangeSelectedActor,
  ChangeSelectedActorModel,
};

struct Event {
  EventCode code;
  void* data;
  U32 dataSize;
};

};  // namespace ambr