#include "Core/Application.h"
#include "Core/Base.h"
#include "ECS/ECS.h"
#include "Gui/Gui.h"
#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "Assets/Font.h"

int main(int argc, char** argv) {
  Zoom::Application app;

  Zoom::WindowSystemSpecifications windowSpecs {1920, 1080, "Zoom Engine" };
  Zoom::RendererSystemSpecifications rendererSpecs {
      Zoom::RendererImplementation::OpenGL, true, 1920, 1080 };

  /** Systems need to be registered in the right order.
   *  ex: Window needs to be registered before Renderer, since it depends on it. **/
  app.Register(Zoom::SystemLocator<Zoom::Window>::Get(), &windowSpecs);
  app.Register(Zoom::SystemLocator<Zoom::ECS>::Get(), nullptr);
  app.Register(Zoom::SystemLocator<Zoom::Renderer>::Get(), &rendererSpecs);
  app.Register(Zoom::SystemLocator<Zoom::Gui>::Get(), nullptr);
  app.Register(Zoom::SystemLocator<Zoom::FontManager>::Get(), nullptr);

  app.Start();

  return 0;
};