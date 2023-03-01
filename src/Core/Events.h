#pragma once

#include "Core/Base.h"

namespace ambr {

enum class EventCode : U16 {
  ExitApplication,
  ChangeSelectedActor,
  ChangeSelectedActorModel,
  OpenLoadModelWindow,
  CloseLoadModelWindow,
  LoadModel,
};

struct Event {
  EventCode code;
  void* data;
  U32 dataSize;
};

////////////////////////////
/// EVENT SPECIFICATIONS ///
////////////////////////////

struct LoadModelEventSpecs {
  String name;
  String path;
};

};  // namespace ambr