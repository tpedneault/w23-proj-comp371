#include "Assets/Model.h"

namespace ambr {

std::shared_ptr<Model> ModelManager::FromOBJ(const String& name,
                                             const String& path) {
  std::ifstream fin(path);
  std::string token;

  std::vector<glm::vec3> vertices;
  std::vector<glm::uvec3> indices;

  for (std::string line; std::getline(fin, line);) {
    std::stringstream ss(line);
    std::getline(ss, token, ' ');

    if (token == "v") {
      vertices.push_back(ReadVertexLine(ss));
    } else if (token == "f") {
      indices.push_back(ReadVertexLine(ss));
    }
  }

  auto model = std::make_shared<Model>();

  glGenVertexArrays(1, &model->VAO);
  glBindVertexArray(model->VAO);

  I32 verticesSize = sizeof(glm::vec3) * vertices.size();
  glGenBuffers(1, &model->VBO);
  glBindBuffer(GL_ARRAY_BUFFER, model->VBO);
  glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
                        static_cast<void*>(nullptr));

  // Verify that the vertices were successfully stored.
  I32 size = 0;
  glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
  if (size != verticesSize) {
    AMBR_LOG_ERROR(std::format(
        "Failed to load indices for model {}, actual size: {} s.b {}", name,
        size, verticesSize));
  }

  glEnableVertexAttribArray(0);

  I32 indicesSize = sizeof(glm::uvec3) * indices.size();
  glGenBuffers(1, &model->EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices.data(),
               GL_STATIC_DRAW);

  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
  if (size != indicesSize) {
    AMBR_LOG_ERROR(std::format(
        "Failed to load indices for model {}, actual size: {} s.b {}", name,
        size, indicesSize));
  }

  model->IndexCount = indicesSize / sizeof(glm::uvec3);

  return model;
}

void ModelManager::OnInitialization(void* specs) {
  m_Models["cow"] = FromOBJ("cow",  "assets/models/cow.obj");
  m_Models["cube"] = FromOBJ("cube", "assets/models/cube.obj");
}

void ModelManager::OnUpdate() {}

void ModelManager::OnDestroy() {}

void ModelManager::ProcessEvent(const Event& e) {}

std::vector<std::shared_ptr<System>> ModelManager::GetDependencies() const {
  return {};
}

std::shared_ptr<Model> ModelManager::GetModel(const String& name) {
  return m_Models[name];
}

glm::vec3 ModelManager::ReadVertexLine(std::stringstream& ss) {
  std::string token;
  glm::vec3 vertex{};
  std::getline(ss, token, ' ');
  vertex.x = std::stof(token);
  std::getline(ss, token, ' ');
  vertex.y = std::stof(token);
  std::getline(ss, token, ' ');
  vertex.z = std::stof(token);
  return vertex;
}

glm::uvec3 ModelManager::ReadFaceLine(std::stringstream& ss) {
  std::string token;
  glm::vec3 face{};
  std::getline(ss, token, ' ');
  face.x = std::stoul(token);
  std::getline(ss, token, ' ');
  face.y = std::stoul(token);
  std::getline(ss, token, ' ');
  face.z = std::stoul(token);
  return face;
}

};  // namespace ambr