#include "Image.h"

namespace sc {

Image::~Image() {
  if(m_Pixels != nullptr) {
    stbi_image_free(m_Pixels);
  }
}

void Image::Load(const char *path) {
  m_Pixels = stbi_load(path, &m_Width, &m_Height, &m_Channels, 4);
}

GLFWimage *Image::GetGLFWImage() {
  auto *image = new GLFWimage();
  image->width = m_Width;
  image->height = m_Height;
  image->pixels = m_Pixels;
  return image;
}

};

