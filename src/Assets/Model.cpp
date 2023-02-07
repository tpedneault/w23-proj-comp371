#include "Assets/Model.h"

namespace ambr {

std::shared_ptr<Model> ModelManager::FromOBJ(const String& name,
                                             const String& path) {
  std::ifstream fin(path);
  std::string token;

  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> faces;

  for (std::string line; std::getline(fin, line);) {
    std::stringstream ss(line);
    std::getline(ss, token, ' ');

    if (token == "v") {
      vertices.push_back(ReadVec3Line(ss));
    } else if (token == "f") {
      faces.push_back(ReadVec3Line(ss));
    }
  }

  auto model = std::make_shared<Model>();

  glGenVertexArrays(1, &model->VAO);
  glBindVertexArray(model->VAO);

  glGenBuffers(1, &model->VBO);
  glBindBuffer(GL_ARRAY_BUFFER, model->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(),
               vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
                        static_cast<void*>(nullptr));

  glGenBuffers(1, &model->IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::vec3) * faces.size(),
               faces.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  model->IndexCount = sizeof(faces) / sizeof(glm::vec3);

  return model;
}

void ModelManager::OnInitialization(void* specs) {
  auto obj = FromOBJ("cow", "assets/models/cow.txt");
  m_Models["cow"] = obj;
}

void ModelManager::OnUpdate() {}

void ModelManager::OnDestroy() {}

void ModelManager::ProcessEvent(const Event& e) {}

std::vector<std::shared_ptr<System>> ModelManager::GetDependencies() const {
  return {SystemLocator<Renderer>::Get()};
}

std::shared_ptr<Model> ModelManager::GetModel(const String& name) {
  return m_Models[name];
 }

glm::vec3 ModelManager::ReadVec3Line(std::stringstream& ss) {
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

};  // namespace ambr