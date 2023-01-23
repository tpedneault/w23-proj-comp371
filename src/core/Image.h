#pragma once

#include <cstdint>
#include <GLFW/glfw3.h>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace sc {

/**
 * Represents an image in memory. Loads and parses image data into different data structures.
 */
class Image {
 public:
  Image() {}
  virtual ~Image();

  void Load(const char* path);
  GLFWimage* GetGLFWImage();
 private:
  int m_Channels;
  int m_Width, m_Height;
  uint8_t* m_Pixels;
};

};