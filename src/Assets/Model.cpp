#include "Assets/Model.h"

namespace ambr {

void ModelManager::OnInitialization(void *specs) {
  m_Models["mini_tank"] = LoadModel("mini_tank", "assets/models/mini_tank.glb");
  m_Models["cow"] = LoadModel("cow", "assets/models/cow.obj");
  m_Models["couch"] = LoadModel("couch", "assets/models/Koltuk.blend");
}

void ModelManager::OnUpdate() {}

void ModelManager::OnDestroy() {}

void ModelManager::ProcessEvent(const Event &e) {}

std::vector<std::shared_ptr<System>> ModelManager::GetDependencies() const {
  return {};
}

std::shared_ptr<Model> ModelManager::GetModel(const String &name) {
  return m_Models[name];
}

std::shared_ptr<Model> ModelManager::LoadModel(const String &name,
                                               const String &path) {
  static Assimp::Importer s_Importer;

  const aiScene *scene = s_Importer.ReadFile(path.c_str(),
                                             aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs
                                                 | aiProcess_JoinIdenticalVertices);
  if (!scene) {
    AMBR_LOG_ERROR(
        fmt::format("Failed to load file {}, error string: {}", name, s_Importer.GetErrorString()));
    return nullptr;
  }

  AMBR_LOG_INFO(fmt::format("Successfully loaded model {}!", name));
  const aiNode *root = scene->mRootNode;
  AMBR_LOG_INFO(fmt::format("Model contains the following nodes:"));

  auto model = std::make_shared<Model>();
  model->scene = scene;

  // Since this is a model and not a scene, assuming no child nodes.
  for (I32 i = 0; i < root->mNumChildren; i++) {
    auto node = root->mChildren[i];
    AMBR_LOG_DEBUG(fmt::format("--> '{}' with {} child nodes, {} meshes.",
                               node->mName.C_Str(),
                               node->mNumChildren,
                               node->mNumMeshes));

    // If there are no meshes, this is either a light or a camera.
    if (node->mNumMeshes == 0) {
      continue;
    }

    auto modelMesh = std::make_shared<ModelMesh>();
    auto mesh = scene->mMeshes[node->mMeshes[0]];

    modelMesh->name = node->mName.C_Str();

    glGenVertexArrays(1, &modelMesh->vertexArray);
    glBindVertexArray(modelMesh->vertexArray);

    glEnableVertexAttribArray(static_cast<U32>(OpenGLBufferType::VertexBuffer));
    glEnableVertexAttribArray(static_cast<U32>(OpenGLBufferType::TextureCoordsBuffer));
    glEnableVertexAttribArray(static_cast<U32>(OpenGLBufferType::NormalBuffer));

    /* Load Vertices into a vertex buffer object. */
    I32 verticesSize = sizeof(aiVector3D) * mesh->mNumVertices;
    glGenBuffers(1, &modelMesh->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, modelMesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, mesh->mVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(static_cast<U32>(OpenGLBufferType::VertexBuffer), 3, GL_FLOAT, GL_FALSE, sizeof(aiVector3D),
                          static_cast<void *>(nullptr));

    I32 size = 0;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    if (size != verticesSize) {
      AMBR_LOG_ERROR(fmt::format(
          "Failed to load indices for model {}, actual size: {} s.b {}", name,
          size, verticesSize));
    }

    I32 indicesSize = mesh->mNumFaces * sizeof(glm::uvec3);
    std::vector<glm::uvec3> indices;

    for (I32 j = 0; j < mesh->mNumFaces; j++) {
      auto face = mesh->mFaces[j];
      glm::uvec3 index{
          face.mIndices[0],
          face.mIndices[1],
          face.mIndices[2],
      };
      indices.push_back(index);
    }

    glGenBuffers(1, &modelMesh->indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelMesh->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices.data(),
                 GL_STATIC_DRAW);

    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    if (size != indicesSize) {
      AMBR_LOG_ERROR(fmt::format(
          "Failed to load indices for model {}, actual size: {} s.b {}", name,
          size, indicesSize));
    }

    modelMesh->indexCount = mesh->mNumFaces;

    /* Load Texture Coordinates into a vertex buffer object. */
    I32 textureCoordsSize = mesh->mNumVertices * sizeof(aiVector3D);
    glGenBuffers(1, &modelMesh->textureCoordsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, modelMesh->textureCoordsBuffer);
    glBufferData(GL_ARRAY_BUFFER, textureCoordsSize, mesh->mTextureCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(static_cast<U32>(OpenGLBufferType::TextureCoordsBuffer),
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(aiVector3D),
                          static_cast<void *>(nullptr));
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    if (size != textureCoordsSize) {
      AMBR_LOG_ERROR(fmt::format(
          "Failed to load texture coordinates for model {}, actual size: {} s.b {}", name,
          size, textureCoordsSize));
    }

    /* Load Normals into a vertex buffer object. */
    I32 normalsSize = mesh->mNumVertices * sizeof(aiVector3D);
    glGenBuffers(1, &modelMesh->normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, modelMesh->normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normalsSize, mesh->mNormals, GL_STATIC_DRAW);
    glVertexAttribPointer(static_cast<U32>(OpenGLBufferType::NormalBuffer),
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(aiVector3D),
                          static_cast<void *>(nullptr));
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

    if (size != normalsSize) {
      AMBR_LOG_ERROR(fmt::format(
          "Failed to load normals for model {}, actual size: {} s.b {}", name,
          size, normalsSize));
    }

    modelMesh->transform = aiMatrix4x4ToGlm(node->mTransformation);

    modelMesh->material.material = scene->mMaterials[mesh->mMaterialIndex];
    aiGetMaterialString(modelMesh->material.material, AI_MATKEY_NAME, &modelMesh->material.name);

    aiColor3D ambientColor(0.0f, 0.0f, 0.0f);
    if (modelMesh->material.material->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor)) {
      AMBR_LOG_DEBUG(fmt::format("--> '{}' has ambient color r={}, g={}, b={}",
                                 modelMesh->name,
                                 ambientColor.r,
                                 ambientColor.g,
                                 ambientColor.b));
      modelMesh->material.ambientColor.x = ambientColor.r;
      modelMesh->material.ambientColor.y = ambientColor.g;
      modelMesh->material.ambientColor.z = ambientColor.b;
    }

    model->meshes.push_back(modelMesh);
  }

  return model;
}

};  // namespace ambr