#pragma once

#include "GL/glew.h"
#include "core/SystemManager.h"

namespace sc {

class RenderingManager : public SystemManager {
 public:
  RenderingManager() {}
  virtual ~RenderingManager() {}

  void Start() override;
  void Update() override;
  void Close() override;

  inline GLuint GetSceneFBO() { return sceneFBO; }
  inline GLuint GetCameraFBO() { return cameraFBO; }

 private:
  GLuint sceneFBO, cameraFBO;
};

};