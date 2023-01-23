#include "Renderer.h"

namespace sc {

void RenderingManager::Start() {
  glGenFramebuffers(1, &sceneFBO);
  glGenFramebuffers(1, &cameraFBO);
}
void RenderingManager::Update() {

}
void RenderingManager::Close() {

}

};

