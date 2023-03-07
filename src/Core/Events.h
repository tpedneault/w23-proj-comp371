#pragma once

#include "Core/Base.h"

namespace ambr {

enum class EventCode : U16 {
  ExitApplication,
  ChangeSelectedActor,
  ChangeSelectedEntity,
  ChangeSelectedActorModel,
  OpenLoadModelWindow,
  CloseLoadModelWindow,
  ImportModel,
  CreateActorEntity,
  CreateLightEntity,
  CreateCameraEntity,
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