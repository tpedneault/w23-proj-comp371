#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Core/Base.h"

namespace ambr {

constexpr U8 MATERIAL_OPACITY_MAP  (1 << 0);
constexpr U8 MATERIAL_SPECULAR_MAP (1 << 1);
constexpr U8 MATERIAL_DIFFUSE_MAP  (1 << 2);
constexpr U8 MATERIAL_AMBIENT_MAP  (1 << 3);
constexpr U8 MATERIAL_NORMAL_MAP   (1 << 4);

class Material {
  [[nodiscard]] static std::shared_ptr<Material> FromScene(const aiScene* scene, U32 materialIndex);
  String m_Name;
  U32 m_MaterialIndex;
  U8 m_Maps;
};

};
