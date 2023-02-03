#include "Assets/Font.h"
#include "Core/Application.h"
#include "Core/Base.h"
#include "ECS/ECS.h"
#include "Gui/Gui.h"
#include "Renderer/Renderer.h"
#include "Window/Window.h"

int main(int argc, char** argv) {
  Zoom::Application app;

  Zoom::WindowSystemSpecifications windowSpecs{1920, 1080, "Zoom Engine"};
  Zoom::RendererSystemSpecifications rendererSpecs{
      Zoom::RendererImplementation::OpenGL, true, 1920, 1080};

  app.Register(Zoom::SystemLocator<Zoom::Window>::Get(), &windowSpecs);
  app.Register(Zoom::SystemLocator<Zoom::ECS>::Get(), nullptr);
  app.Register(Zoom::SystemLocator<Zoom::Renderer>::Get(), &rendererSpecs);
  app.Register(Zoom::SystemLocator<Zoom::Gui>::Get(), nullptr);
  app.Register(Zoom::SystemLocator<Zoom::FontManager>::Get(), nullptr);

  app.Start();

  return 0;
};