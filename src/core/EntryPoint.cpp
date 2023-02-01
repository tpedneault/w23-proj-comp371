#include "Core/Base.h"

#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "Gui/Gui.h"
#include "ECS/ECS.h"
#include "Assets/Font.h"

int main(int argc, char** argv){
  const auto window = Zoom::SystemLocator<Zoom::Window>::Get();
  const auto renderer = Zoom::SystemLocator<Zoom::Renderer>::Get();
  const auto gui = Zoom::SystemLocator<Zoom::Gui>::Get();
  const auto ecs = Zoom::SystemLocator<Zoom::ECS>::Get();

  Zoom::WindowSystemSpecifications windowSpecs{1920, 1080, "Zoom Engine"};
  Zoom::RendererSystemSpecifications rendererSpecs{Zoom::RendererImplementation::OpenGL, true, 800, 600};

  /** Initialization all systems in the proper order. **/
  window->Initialize(&windowSpecs);
  ecs->Initialize(nullptr);
  renderer->Initialize(&rendererSpecs);
  gui->Initialize(nullptr);

  /** Load assets. **/
  Zoom::SystemLocator<Zoom::FontManager>::Get()->Initialize(nullptr);

  /** Begin the game loop. **/
  while (window->IsOpen()) {
    ecs->Update();
    renderer->Update();
    gui->Update();
    window->Update();
  }

  /** Destroy all systems. **/
  ecs->Destroy();
  gui->Destroy();
  renderer->Destroy();
  window->Destroy();

  return 0;
};