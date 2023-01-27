#include "Zoom.h"

int
main()
{
  auto& window   = Zoom::SystemLoader<Zoom::Window>::Get();
  auto& renderer = Zoom::SystemLoader<Zoom::Renderer>::Get();
  auto& gui      = Zoom::SystemLoader<Zoom::Gui>::Get();

  Zoom::WindowSystemSpecifications windowSpecs{ 800, 600, "Zoom Engine" };

  /** Initialize all systems in the proper order. **/
  window.Initialize(&windowSpecs);
	renderer.Initialize(nullptr);
  gui.Initialize(nullptr);

  /** Begin the game loop. **/
  while (window.IsOpen()) {
    renderer.Update();
    gui.Update();
    window.Update();
  }

  /** Destroy all systems. **/
  gui.Destroy();
  renderer.Destroy();
  window.Destroy();
}