#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "Core/Base.h"
#include "ECS/Component.h"
#include "Assets/Model.h"

namespace ambr {
class Mesh {
 public:
  static Mesh FromVertices(const std::vector<glm::vec3>& vertices) {
    U32 VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(),
                 vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
                          static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    return {VAO, VBO, vertices.size()};
  }

  static Mesh FromModel(const String& modelId) {
    auto model = SystemLocator<ModelManager>::Get()->GetModel(modelId);
    return {model->VAO, model->VBO, model->EBO, model->IndexCount};
  }

  Mesh() = default;
  Mesh(const U32 VAO, const U32 VBO, const U64 size)
      : m_VAO(VAO), m_VBO(VBO), m_Size(size) {}
  Mesh(const U32 VAO, const U32 VBO, const U32 EBO, const U32 indexCount)
      : m_VAO(VAO), m_VBO(VBO), m_EBO(EBO), m_IndexCount(indexCount) {}

  [[nodiscard]] U32 GetVAO() const { return m_VAO; }
  [[nodiscard]] U32 GetVBO() const { return m_VBO; }
  [[nodiscard]] U32 GetEBO() const { return m_EBO; }
  [[nodiscard]] U32 GetIndexCount() const { return m_IndexCount; }
  [[nodiscard]] U64 GetSize() const { return m_Size; }

 private:
  U32 m_VAO{}, m_VBO{}, m_EBO{}, m_IndexCount{};
  U64 m_Size{};
};

};  // namespace ambr