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

  {
    auto vertex = Shader::Create(ShaderType::Vertex, "assets/shaders/skybox.vertex.glsl");
    auto frag = Shader::Create(ShaderType::Fragment, "assets/shaders/skybox.fragment.glsl");
    m_SkyboxProgram = ShaderProgram::Create({vertex, frag});

    delete vertex;
    delete frag;
  }

  {
    auto vertex = Shader::Create(ShaderType::Vertex, "assets/shaders/grid.vertex.glsl");
    auto frag = Shader::Create(ShaderType::Fragment, "assets/shaders/grid.fragment.glsl");
    m_GridProgram = ShaderProgram::Create({vertex, frag});

    delete vertex;
    delete frag;
  }

  m_SceneCamera.position = glm::vec3(4.0f, 4.0f, 4.0f);
  m_SceneCamera.orientation = glm::vec3(-4.0f, -4.0f, -4.0f);
  m_SceneCamera.up = glm::vec3(0.0f, -1.0f, 0.0f);

  LoadDefaultTexture();
  LoadSkyboxCubemap();
  LoadGridData();

  glEnable(GL_DEPTH_TEST);

  SetViewportSize(m_Specs.viewportWidth, m_Specs.viewportHeight);
}

void Renderer::OnUpdate() {
  // Clear the main window.
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  UpdateSceneCamera();

  // !! ANYTHING FROM THIS POINT ON IS RENDERED TO THE FRAMEBUFFER !!.
  if (m_Specs.useFramebuffer) {
    m_Framebuffer.Bind();
  }

  glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  m_ShaderProgram->Use();

  glm::mat4 projection = glm::perspective(
      glm::radians(m_SceneCamera.fov),
      static_cast<float>(m_Framebuffer.GetWidth()) / m_Framebuffer.GetHeight(),
      m_SceneCamera.nearPlane, m_SceneCamera.farPlane);

  auto
      view = glm::lookAt(m_SceneCamera.position, m_SceneCamera.position + m_SceneCamera.orientation, m_SceneCamera.up);

  auto light = SystemLocator<ECS>::Get()->GetLights()[0];

  m_ShaderProgram->Use();
  m_ShaderProgram->SetUniform("projection", projection);
  m_ShaderProgram->SetUniform("view", view);
  m_ShaderProgram->SetUniform("cameraPosition", m_SceneCamera.position);
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

      glm::mat4 modelViewMatrix = view * model;
      glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelViewMatrix)));
      m_ShaderProgram->SetUniform("normalMatrix", normalMatrix);

      glActiveTexture(GL_TEXTURE0);
      if (mesh->texture) {
        glBindTexture(GL_TEXTURE_2D, mesh->textureID);
      } else if (actor->texture) {
        glBindTexture(GL_TEXTURE_2D, actor->texture->textureID);
      } else {
        glBindTexture(GL_TEXTURE_2D, m_DefaultTexture);
      }
      glBindVertexArray(mesh->vertexArray);
      glDrawElements(GL_TRIANGLES, mesh->indexCount * 3, GL_UNSIGNED_INT, nullptr);
      glBindVertexArray(0);
      glBindTexture(GL_TEXTURE_2D, 0);
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

  // Render the grid.
  glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(100.0f, 0.0f, 100.0f));

  m_GridProgram->Use();
  m_GridProgram->SetUniform("model", model);
  m_GridProgram->SetUniform("view", view);
  m_GridProgram->SetUniform("projection", projection);

  m_GridProgram->SetUniform("gridSize", 100.0f);
  m_GridProgram->SetUniform("lineWidth", 0.01f);
  m_GridProgram->SetUniform("lineColor", glm::vec3(0.3f, 0.3f, 0.3f));

  glBindVertexArray(m_GridVAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);

  // Render the skybox.
  glDepthFunc(GL_LEQUAL);

  m_SkyboxProgram->Use();
  glm::mat4 skyboxView = glm::mat4(glm::mat3(glm::lookAt(glm::vec3(0.0f), m_SceneCamera.orientation, m_SceneCamera.up)));
  m_SkyboxProgram->SetUniform("view", skyboxView);
  m_SkyboxProgram->SetUniform("projection", projection);

  glDepthFunc(GL_LEQUAL);
  glBindVertexArray(m_SkyboxVAO);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, m_SkyboxTexture);
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glDepthFunc(GL_LESS);

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
    default:
      break;
  }
}

void Renderer::UpdateSceneCamera() {
  float dt = SystemLocator<Window>::Get()->GetDeltaTime();
  GLFWwindow *window = SystemLocator<Window>::Get()->GetWindow();

  // Calculate the camera's front, right, and up vectors
  glm::vec3 front = glm::normalize(m_SceneCamera.orientation);
  glm::vec3 right = glm::normalize(glm::cross(front, m_SceneCamera.up));
  glm::vec3 up = glm::normalize(glm::cross(right, front));

  glm::vec3 displacement(0.0f);

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    displacement -= right * SCENE_CAMERA_MOVE_SPEED * dt;
  }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    displacement += front * SCENE_CAMERA_MOVE_SPEED * dt;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    displacement += right * SCENE_CAMERA_MOVE_SPEED * dt;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    displacement -= front * SCENE_CAMERA_MOVE_SPEED * dt;
  }

  // Update both the camera position and target
  m_SceneCamera.position += displacement;
}

void Renderer::LoadSkyboxCubemap() {
  static std::vector<String> faces = {
      "assets/skybox/right.bmp",
      "assets/skybox/left.bmp",
      "assets/skybox/top.bmp",
      "assets/skybox/bottom.bmp",
      "assets/skybox/front.bmp",
      "assets/skybox/back.bmp"
  };

  glGenTextures(1, &m_SkyboxTexture);
  glBindTexture(GL_TEXTURE_CUBE_MAP, m_SkyboxTexture);

  stbi_set_flip_vertically_on_load(false);
  I32 width, height, numChannels;
  for (U32 i = 0; i < faces.size(); i++) {
    U8 *data = stbi_load(faces[i].c_str(), &width, &height, &numChannels, 0);
    if (data) {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    } else {
      AMBR_LOG_ERROR(fmt::format("Failed to load cubemap texture: {}.", faces[i].c_str()));
    }
    stbi_image_free(data);
  }
  stbi_set_flip_vertically_on_load(true);

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  std::vector<float> skyboxVertices = {
      //   Coordinates
      -1.0f, -1.0f, 1.0f,//        7--------6
      1.0f, -1.0f, 1.0f,//       /|       /|
      1.0f, -1.0f, -1.0f,//      4--------5 |
      -1.0f, -1.0f, -1.0f,//      | |      | |
      -1.0f, 1.0f, 1.0f,//      | 3------|-2
      1.0f, 1.0f, 1.0f,//      |/       |/
      1.0f, 1.0f, -1.0f,//      0--------1
      -1.0f, 1.0f, -1.0f
  };

  std::vector<U32> skyboxIndices = {
      // Right
      1, 2, 6,
      6, 5, 1,
      // Left
      0, 4, 7,
      7, 3, 0,
      // Top
      4, 5, 6,
      6, 7, 4,
      // Bottom
      0, 3, 2,
      2, 1, 0,
      // Back
      0, 1, 5,
      5, 4, 0,
      // Front
      3, 7, 6,
      6, 2, 3
  };

  m_SkyboxNumberIndices = skyboxIndices.size();

  GLuint cubeVBO, cubeEBO;
  glGenVertexArrays(1, &m_SkyboxVAO);
  glGenBuffers(1, &cubeVBO);
  glGenBuffers(1, &cubeEBO);

  glBindVertexArray(m_SkyboxVAO);

  glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
  glBufferData(GL_ARRAY_BUFFER, skyboxVertices.size() * sizeof(float), skyboxVertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, skyboxIndices.size() * sizeof(U32), skyboxIndices.data(), GL_STATIC_DRAW);

  // Vertex positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);

  glBindVertexArray(0);
}

void Renderer::LoadDefaultTexture() {
  glGenTextures(1, &m_DefaultTexture);
  glBindTexture(GL_TEXTURE_2D, m_DefaultTexture);

  GLubyte whitePixel[] = {255, 255, 255, 255}; // RGBA
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, whitePixel);

  // Set texture parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::OnViewportClicked(ImGuiIO &io, ImVec2 topLeft, ImVec2 viewportSize) {
  ImVec2 mousePos = io.MousePos;
  ImVec2 imageBottomRight = ImVec2(topLeft.x + viewportSize.x, topLeft.y + viewportSize.y);

  if (io.MouseDown[0] && mousePos.x >= topLeft.x && mousePos.y >= topLeft.y && mousePos.x <= imageBottomRight.x
      && mousePos.y <= imageBottomRight.y) {
    ImVec2 delta = io.MouseDelta;

    static float sensitivity = -0.015f;

    // Normalize the orientation vector
    glm::vec3 camDir = glm::normalize(m_SceneCamera.orientation);

    // Calculate the camera's right and up vectors
    glm::vec3 camRight = glm::normalize(glm::cross(camDir, m_SceneCamera.up));
    glm::vec3 camUp = glm::normalize(glm::cross(camRight, camDir));

    // Update the camera's orientation based on the mouse movement
    glm::vec3 deltaOrientation = (camRight * -delta.x * sensitivity) + (camUp * delta.y * (sensitivity * -1));
    m_SceneCamera.orientation += deltaOrientation;

    // Re-normalize the orientation vector after the update
    m_SceneCamera.orientation = glm::normalize(m_SceneCamera.orientation);
  }
}

void Renderer::LoadGridData() {
  static float gridQuadVertices[] = {
      -0.5f, 0.0f, -0.5f,
      0.5f, 0.0f, -0.5f,
      0.5f, 0.0f, 0.5f,
      -0.5f, 0.0f, 0.5f
  };

  static U32 gridQuadIndices[] = {
      0, 1, 2,
      0, 2, 3
  };

  U32 vbo, ebo;
  glGenVertexArrays(1, &m_GridVAO);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(m_GridVAO);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(gridQuadVertices), gridQuadVertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(gridQuadIndices), gridQuadIndices, GL_STATIC_DRAW);

  // Position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}

};  // namespace ambr