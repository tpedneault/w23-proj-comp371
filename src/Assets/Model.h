#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Core/System.h"
#include "Renderer/Renderer.h"

namespace ambr {

enum class OpenGLBufferType : U32 {
  VertexBuffer = 0,
  TextureCoordsBuffer = 1,
  NormalBuffer = 2
};

struct ModelMesh {
  String name;
  U32 vertexArray;
  U32 vertexBuffer;
  U32 indexBuffer;
  I32 indexCount;
  U32 textureCoordsBuffer;
  U32 normalBuffer;
};

struct Material {
  aiString name;
  aiMaterial* material;
  aiColor4D specularColor;
  aiColor4D diffuseColor;
  aiColor4D ambiantColor;
  float shininess;
};

struct Model {
  const aiScene *scene;
  std::vector<std::shared_ptr<ModelMesh>> meshes;
  Material material;
};

class ModelManager final : public System {
 public:
  static std::shared_ptr<Model> LoadModel(const String &name, const String &path);

  void OnInitialization(void *specs) override;
  void OnUpdate() override;
  void OnDestroy() override;
  void ProcessEvent(const Event &e) override;

  [[nodiscard]] String GetName() override { return "ModelManager"; }
  [[nodiscard]] std::vector<std::shared_ptr<System>> GetDependencies()
  const override;
  [[nodiscard]] std::shared_ptr<Model> GetModel(const String &name);

 private:
  std::map<String, std::shared_ptr<Model>> m_Models;
};

};  // namespace ambr