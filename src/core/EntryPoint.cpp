#include "Assets/Font.h"
#include "Core/Base.h"
#include "ECS/ECS.h"
#include "Gui/Gui.h"
#include "Renderer/Renderer.h"
#include "Window/Window.h"

int main(int argc, char** argv) {
  const auto window = Zoom::SystemLocator<Zoom::Window>::Get();
  const auto renderer = Zoom::SystemLocator<Zoom::Renderer>::Get();
  const auto gui = Zoom::SystemLocator<Zoom::Gui>::Get();
  const auto ecs = Zoom::SystemLocator<Zoom::ECS>::Get();

  Zoom::WindowSystemSpecifications windowSpecs{1920, 1080, "Zoom Engine"};
  /*Zoom::RendererSystemSpecifications rendererSpecs {
    Zoom::RendererImplementation::OpenGL, false, 1920, 1080
  };*/

  /** Initialization all systems in the proper order. **/
  window->Initialize(&windowSpecs);
  /*ecs->Initialize(nullptr);
  renderer->Initialize(&rendererSpecs);*/
  // gui->Initialize(nullptr);

  /** Load assets. **/
  // Zoom::SystemLocator<Zoom::FontManager>::Get()->Initialize(nullptr);

  auto vertex = Zoom::Shader::Create(Zoom::ShaderType::Vertex,
                                     "assets/shaders/vertex_shader.glsl");
  auto fragment = Zoom::Shader::Create(Zoom::ShaderType::Fragment,
                                       "assets/shaders/frag_shader.glsl");
  auto program = Zoom::ShaderProgram::Create({vertex, fragment});

  float vertices[9] = {
      -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.5f, 0.0f,
  };

  Zoom::U32 VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 3, vertices,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3,
                        static_cast<void*>(nullptr));
  glEnableVertexAttribArray(0);

  /** Begin the game loop. **/
  while (window->IsOpen()) {
    /*ecs->Update();
    renderer->Update();*/
    // gui->Update();
    program->Use();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

  	window->Update();
  }

  /** Destroy all systems. **/
  // ecs->Destroy();
  // gui->Destroy();
  // renderer->Destroy();
  window->Destroy();

  return 0;
};