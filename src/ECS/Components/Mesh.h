#pragma once

#include <Core/Base.h>
#include <GL/glew.h>

#include <glm/glm.hpp>

namespace Zoom {
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

    return { VAO, VBO, vertices.size() };
  }

  Mesh() = default;
  Mesh(const U32 VAO, const U32 VBO, const U64 size) : m_VAO(VAO), m_VBO(VBO), m_Size(size) {}

  [[nodiscard]] U32 GetVAO() const { return m_VAO; }
  [[nodiscard]] U32 GetVBO() const { return m_VBO; }
  [[nodiscard]] U64 GetSize() const { return m_Size; }

 private:
  U32 m_VAO{}, m_VBO{};
  U64 m_Size{};
};

};  // namespace Zoom