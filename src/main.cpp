#include "Zoom.h"

int main() {
  auto& window = Zoom::SystemLocator<Zoom::Window>::Get();
  auto& renderer = Zoom::SystemLocator<Zoom::Renderer>::Get();
  auto& gui = Zoom::SystemLocator<Zoom::Gui>::Get();
  auto& ecs = Zoom::SystemLocator<Zoom::ECS>::Get();

  Zoom::WindowSystemSpecifications windowSpecs{800, 600, "Zoom Engine"};

  /** Initialize all systems in the proper order. **/
  window.Initialize(&windowSpecs);
  renderer.Initialize(nullptr);
  gui.Initialize(nullptr);
  ecs.Initialize(nullptr);

  /** Load assets. **/
  Zoom::SystemLocator<Zoom::FontManager>::Get().Initialize(nullptr);

  /** Begin the game loop. **/
  while (window.IsOpen()) {
    ecs.Update();
    renderer.Update();
    gui.Update();
    window.Update();
  }

  /** Destroy all systems. **/
  ecs.Destroy();
  gui.Destroy();
  renderer.Destroy();
  window.Destroy();

  return 0;
}
