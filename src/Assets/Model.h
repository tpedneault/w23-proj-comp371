#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Core/System.h"
#include "Renderer/Renderer.h"
#include "Assets/Material.h"

namespace ambr {

enum class OpenGLBufferType : U32 {
  VertexBuffer = 0,
  TextureCoordsBuffer = 1,
  NormalBuffer = 2
};

struct ModelMesh {
  String name;
  glm::mat4 transform;
  U32 vertexArray;
  U32 vertexBuffer;
  U32 indexBuffer;
  I32 indexCount;
  U32 textureCoordsBuffer;
  U32 normalBuffer;
  U32 materialIndex;
  U32 textureIndex;
};

struct Model {
  String name;
  const aiScene *scene;
  std::vector<std::shared_ptr<ModelMesh>> meshes;
  std::vector<std::shared_ptr<Material>> materials;
  std::vector<U32> textures;
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
  [[nodiscard]] std::vector<std::shared_ptr<Model>> GetModels();

 private:
  static void LoadMesh(const String& name, const aiScene* scene, const aiNode* node, const std::shared_ptr<Model>& model);

  [[nodiscard]] static glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4 from) {
    glm::mat4 to;

    to[0][0] = (GLfloat) from.a1;
    to[0][1] = (GLfloat) from.b1;
    to[0][2] = (GLfloat) from.c1;
    to[0][3] = (GLfloat) from.d1;
    to[1][0] = (GLfloat) from.a2;
    to[1][1] = (GLfloat) from.b2;
    to[1][2] = (GLfloat) from.c2;
    to[1][3] = (GLfloat) from.d2;
    to[2][0] = (GLfloat) from.a3;
    to[2][1] = (GLfloat) from.b3;
    to[2][2] = (GLfloat) from.c3;
    to[2][3] = (GLfloat) from.d3;
    to[3][0] = (GLfloat) from.a4;
    to[3][1] = (GLfloat) from.b4;
    to[3][2] = (GLfloat) from.c4;
    to[3][3] = (GLfloat) from.d4;

    return to;
  }

  std::vector<std::shared_ptr<Model>> m_Models;
};

};  // namespace ambr