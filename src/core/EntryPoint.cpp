#include "Core/Application.h"
#include "Core/Base.h"
#include "ECS/ECS.h"
#include "Gui/Gui.h"
#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "Assets/Font.h"
#include "Assets/Model.h"

int main(int argc, char** argv) {
  ambr::Application app;

  ambr::WindowSystemSpecifications windowSpecs {1920, 1080, "Ambrosia Editor" };
  ambr::RendererSystemSpecifications rendererSpecs {
      ambr::RendererImplementation::OpenGL, true, 1920, 1080 };

  /** Systems need to be registered in the right order.
   *  ex: Window needs to be registered before Renderer, since it depends on it. **/
  app.Register(ambr::SystemLocator<ambr::Window>::Get(), &windowSpecs);
  app.Register(ambr::SystemLocator<ambr::ModelManager>::Get(), nullptr);
  app.Register(ambr::SystemLocator<ambr::ECS>::Get(), nullptr);
  app.Register(ambr::SystemLocator<ambr::Renderer>::Get(), &rendererSpecs);
  app.Register(ambr::SystemLocator<ambr::Gui>::Get(), nullptr);
  app.Register(ambr::SystemLocator<ambr::FontManager>::Get(), nullptr);

  app.Start();

  return 0;
};