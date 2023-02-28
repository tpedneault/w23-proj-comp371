#include "Assets/Material.h"

namespace ambr {

std::shared_ptr<Material> Material::FromScene(const aiScene *scene, U32 materialIndex) {
  auto material = std::make_shared<Material>();

  auto assimpMat = scene->mMaterials[materialIndex];

  return material;
}

};