#include "Renderer/Renderer.h"

namespace ambr {

void Renderer::OnInitialization(void *specs) {
  m_Specs = *(static_cast<RendererSystemSpecifications *>(specs));

  {
    auto vertex =
        Shader::Create(ShaderType::Vertex, "assets/shaders/actor.vertex.glsl");
    auto frag =
        Shader::Create(ShaderType::Fragment, "assets/shaders/actor.fragment.glsl");
    m_ShaderProgram = ShaderProgram::Create({vertex, frag});

    delete vertex;
    delete frag;
  }

  {
    auto vertex = Shader::Create(ShaderType::Vertex, "assets/shaders/light.vertex.glsl");
    auto frag = Shader::Create(ShaderType::Fragment, "assets/shaders/light.fragment.glsl");
    m_LightShaderProgram = ShaderProgram::Create({vertex, frag});

    delete vertex;
    delete frag;
  }

  m_SceneCamera.position = glm::vec3(4.0f, 4.0f, 4.0f);
  m_SceneCamera.target = glm::vec3(-4.0f, -4.0f, -4.0f);
  m_SceneCamera.up = glm::vec3(0.0f, -1.0f, 0.0f);

  glEnable(GL_DEPTH_TEST);

  SetViewportSize(m_Specs.viewportWidth, m_Specs.viewportHeight);
}

void Renderer::OnUpdate() {
  // Clear the main window.
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // !! ANYTHING FROM THIS POINT ON IS RENDERED TO THE FRAMEBUFFER !!.
  if (m_Specs.useFramebuffer) {
    m_Framebuffer.Bind();
  }

  glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_ShaderProgram->Use();

  const glm::mat4 projection = glm::perspective(
      glm::radians(m_SceneCamera.fov),
      static_cast<float>(m_Framebuffer.GetWidth()) / m_Framebuffer.GetHeight(),
      m_SceneCamera.nearPlane, m_SceneCamera.farPlane);

  const auto view = glm::lookAt(m_SceneCamera.position, m_SceneCamera.position + m_SceneCamera.target, m_SceneCamera.up);

  auto light = SystemLocator<ECS>::Get()->GetLights()[0];

  m_ShaderProgram->Use();
  m_ShaderProgram->SetUniform("projection", projection);
  m_ShaderProgram->SetUniform("view", view);
  m_ShaderProgram->SetUniform("light.position", light->position);
  m_ShaderProgram->SetUniform("light.color", light->color);
  m_ShaderProgram->SetUniform("light.ambientStrength", light->ambientStrength);

  // TODO: Move to the ActorRenderer class.
  for (const auto &actor : SystemLocator<ECS>::Get()->GetActors()) {
    // If the actor is currently hidden, skip to the next.
    if (!actor->isVisible) {
      continue;
    }

    glm::mat4 model = Transform::GetTransformationMatrix(actor->transform);

    for (const auto &mesh : actor->model->meshes) {
      glm::mat4 meshTransform = model * mesh->transform;
      m_ShaderProgram->SetUniform("model", meshTransform);
      glBindVertexArray(mesh->vertexArray);
      glDrawElements(GL_TRIANGLES, mesh->indexCount * 3, GL_UNSIGNED_INT, nullptr);
      glBindVertexArray(0);
    }
  }

  m_LightShaderProgram->Use();
  m_LightShaderProgram->SetUniform("projection", projection);
  m_LightShaderProgram->SetUniform("view", view);

  for (const auto &light : SystemLocator<ECS>::Get()->GetLights()) {
    if (!light->isVisible) {
      continue;
    }

    glm::mat4 modelTransform(1.0f);
    modelTransform = glm::translate(modelTransform, light->position);
    modelTransform = glm::scale(modelTransform, glm::vec3(0.1f, 0.1f, 0.1f));

    auto model = SystemLocator<ModelManager>::Get()->GetDefaultModel();
    m_LightShaderProgram->SetUniform("model", modelTransform);
    glBindVertexArray(model->meshes[0]->vertexArray);
    glDrawElements(GL_TRIANGLES, model->meshes[0]->indexCount * 3, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
  }

  if (m_Specs.useFramebuffer) {
    m_Framebuffer.Unbind();
  }
}

void Renderer::OnDestroy() {}

void Renderer::SetViewportSize(const I32 width, const I32 height) {
  glViewport(0, 0, width, height);

  m_Framebuffer.SetSize(width, height);
  m_Framebuffer.Initialize();
}

U32 Renderer::GetFramebufferTextureID() const {
  return m_Framebuffer.GetColorAttachmentID();
}

std::vector<std::shared_ptr<System>> Renderer::GetDependencies() const {
  return {SystemLocator<Window>::Get()};
}

void Renderer::ProcessEvent(const Event &e) {
  switch (e.code) {
    case EventCode::KeyPressed: {
      I32 keyCode = *(static_cast<I32 *>(e.data));
      OnKeyPressed(keyCode);
      delete static_cast<I32 *>(e.data);
      break;
    }
    default:
      break;
  }
}

void Renderer::OnKeyPressed(I32 keyCode) {
  float dt = SystemLocator<Window>::Get()->GetDeltaTime();
  switch (keyCode) {
    case GLFW_KEY_A:
      m_SceneCamera.position.x -= SCENE_CAMERA_MOVE_SPEED * dt;
      break;
    case GLFW_KEY_W:
      m_SceneCamera.position.z -= SCENE_CAMERA_MOVE_SPEED * dt;
      break;
    case GLFW_KEY_D:
      m_SceneCamera.position.x += SCENE_CAMERA_MOVE_SPEED * dt;
      break;
    case GLFW_KEY_S:
      m_SceneCamera.position.z += SCENE_CAMERA_MOVE_SPEED * dt;
      break;
    default:
      break;
  }
}

};  // namespace ambr