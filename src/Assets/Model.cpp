#include "Assets/Model.h"

namespace Zoom {

Model* ModelManager::FromOBJ(const String& name, const String& path) {
  std::ifstream fin(path);

  std::vector<float> vertices;
  std::vector<float> textures;
  std::vector<float> normals;

  return new Model;
}

};  // namespace Zoom