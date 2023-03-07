#include "Assets/Model.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace ambr {

void ModelManager::OnInitialization(void *specs) {
  m_Models.push_back(LoadModel("Cube", "assets/models/cube.obj"));
  m_Models.push_back(LoadModel("Cow", "assets/models/cow.obj"));
  m_Models.push_back(LoadModel("Mini Tank", "assets/models/mini_tank.glb"));
  m_Models.push_back(LoadModel("Couch", "assets/models/couch.blend"));
}

void ModelManager::OnUpdate() {}

void ModelManager::OnDestroy() {}

void ModelManager::ProcessEvent(const Event &e) {
  switch (e.code) {
    case EventCode::ImportModel: {
      auto specs = static_cast<LoadModelEventSpecs *>(e.data);
      m_Models.push_back(LoadModel(specs->name, specs->path));
      break;
    }
    default:
      break;
  }
}

std::vector<std::shared_ptr<System>> ModelManager::GetDependencies() const {
  return {};
}

std::shared_ptr<Model> ModelManager::LoadModel(const String &name,
                                               const String &path) {
  static Assimp::Importer s_Importer;

  const aiScene *scene = s_Importer.ReadFile(path.c_str(),
                                             aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs
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
  model->name = name;
  model->scene = scene;

  // Load the textures for the scene.
  if (scene->HasTextures()) {
    for (U32 i = 0; i < scene->mNumTextures; i++) {
      U32 textureId;
      glGenTextures(1, &textureId);
      glBindTexture(GL_TEXTURE_2D, textureId);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,
                      GL_TEXTURE_WRAP_S,
                      (scene->mTextures[i]->achFormatHint[0] & 0x01 ? GL_REPEAT : GL_CLAMP));
      glTexParameteri(GL_TEXTURE_2D,
                      GL_TEXTURE_WRAP_T,
                      (scene->mTextures[i]->achFormatHint[0] & 0x01 ? GL_REPEAT : GL_CLAMP));
      glTexImage2D(GL_TEXTURE_2D,
                   0,
                   GL_RGBA8,
                   scene->mTextures[i]->mWidth,
                   scene->mTextures[i]->mHeight,
                   0,
                   GL_BGRA,
                   GL_UNSIGNED_BYTE,
                   scene->mTextures[i]->pcData);
      model->textures.push_back(textureId);
    }
  }

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

    // Load the mesh and add its data to the model.
    LoadMesh(name, scene, node, model);
  }

  return model;
}

void ModelManager::LoadMesh(const String &name,
                            const aiScene *scene,
                            const aiNode *node,
                            const std::shared_ptr<Model> &model) {
  // Load the child nodes first.
  for (U32 i = 0; i < node->mNumChildren; i++) {
    LoadMesh(name, scene, node->mChildren[i], model);
  }

  for (int i = 0; i < node->mNumMeshes; i++) {
    auto modelMesh = std::make_shared<ModelMesh>();
    auto mesh = scene->mMeshes[node->mMeshes[i]];

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

    // Get the texture for the mesh.
    if (scene->HasTextures()) {
      aiString baseColor;
      auto material = scene->mMaterials[mesh->mMaterialIndex];

      aiReturn result = material->GetTexture(AI_MATKEY_BASE_COLOR_TEXTURE, &baseColor);
      if (result != AI_SUCCESS) {
        AMBR_LOG_WARN("Failed to load the texture for the current mesh.");
      }

      auto texture = scene->GetEmbeddedTextureAndIndex(baseColor.C_Str());
      modelMesh->textureIndex = texture.second;
    }

    model->meshes.push_back(modelMesh);
  }
}

std::shared_ptr<Model> ModelManager::GetModel(const String &name) {
  for (auto model : m_Models) {
    if (model->name == name) {
      return model;
    }
  }
  return nullptr;
}

std::vector<std::shared_ptr<Model>> ModelManager::GetModels() {
  return m_Models;
}
std::shared_ptr<Model> ModelManager::GetDefaultModel() {
  return m_Models[0];
}

};  // namespace ambr