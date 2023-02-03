#pragma once

#include "Core/Base.h"

namespace Zoom {

enum class EventCode : U16 {
  ExitApplication = 0,
};

struct Event {
  EventCode code;
  void* data;
  U32 dataSize;
};

};  // namespace Zoom