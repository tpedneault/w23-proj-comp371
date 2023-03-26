#pragma once

#include "Core/Base.h"

namespace ambr {

enum class EventCode : U16 {
  ExitApplication,
  KeyPressed,

  Editor_ChangeSelectedEntity,
  Editor_ChangeSelectedActorModel,
  Editor_OpenLoadModelWindow,
  Editor_CloseLoadModelWindow,
  Editor_ImportModel,
  Editor_CreateActorEntity,
  Editor_CreateLightEntity,
  Editor_CreateCameraEntity,

  ShaderGraph_PushNode,
  ShaderGraph_PopNode,
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