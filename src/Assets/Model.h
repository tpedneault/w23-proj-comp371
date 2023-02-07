#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "Core/System.h"
#include "Renderer/Renderer.h"

namespace ambr {

struct Model {
  U32 VAO;
  U32 VBO;
  U32 IBO;
  U32 IndexCount;
};

class ModelManager final : public System {
 public:
  static std::shared_ptr<Model> FromOBJ(const String& name, const String& path);

  void OnInitialization(void* specs) override;
  void OnUpdate() override;
  void OnDestroy() override;
  void ProcessEvent(const Event& e) override;
  [[nodiscard]] std::vector<std::shared_ptr<System>> GetDependencies()
      const override;

  [[nodiscard]] std::shared_ptr<Model> GetModel(const String& name);

 private:
  static glm::vec3 ReadVec3Line(std::stringstream& ss);

  std::map<String, std::shared_ptr<Model>> m_Models;
};

};  // namespace ambr