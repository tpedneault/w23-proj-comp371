#pragma once

#include "Core/Base.h"

namespace ambr {

enum class EventCode : U16 {
  ExitApplication,

  Editor_ChangeSelectedEntity,
  Editor_ChangeSelectedActorModel,
  Editor_ChangeSelectedActorTexture,
  Editor_OpenLoadModelWindow,
  Editor_CloseLoadModelWindow,
  Editor_ImportModel,
  Editor_CreateActorEntity,
  Editor_CreateLightEntity,
  Editor_CreateCameraEntity,

  ShaderGraph_PushNode,
  ShaderGraph_PopNode,
  ShaderGraph_RegisterTexture,
  ShaderGraph_UnregisterTexture,
};

struct Event {
  EventCode code;
  void* data;
  U32 dataSize;
};

////////////////////////////
/// EVENT SPECIFICATIONS ///
////////////////////////////

struct Editor_LoadModelEventSpecifications {
  String name;
  String path;
};

struct ShaderGraph_PushNodeEventSpecifications {
  String nodeType;
  String templateTypeName;
};

struct ShaderGraph_RegisterTexture {
  I32 nodeID;
  String textureName;
  U32 textureID;
};

struct ShaderGraph_UnregisterTexture {
  I32 nodeID;
};

};  // namespace ambr