#pragma once

#include <GL/glew.h>

#include "Editor/Widgets/ShaderGraph/ShaderGraphNode.h"

namespace ambr {

class CheckerboardShaderGraphNode : public ShaderGraphNode {
 public:
  CheckerboardShaderGraphNode() : ShaderGraphNode() {}

  void OnInitialize() override {
    m_OutputAttributes.clear();
    m_Title = "Checkerboard";

    PushInputAttribute("Grid Size (U32)");
    PushInputAttribute("Color #1 (Vector3f)");
    PushInputAttribute("Color #2 (Vector3f)");

    PushOutputAttribute("Texture ID (U32)");
  }

  void OnRender() override {
    ImNodes::BeginNode(m_ID);

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(m_Title.c_str());
    ImNodes::EndNodeTitleBar();

    for(const auto& attr : m_InputAttributes) {
      static I32 offset = static_cast<I32>(ShaderGraphAttributeType::Input);
      ImNodes::BeginInputAttribute((m_ID << offset) + attr.ID);
      ImGui::TextUnformatted(attr.title.c_str());
      ImNodes::EndInputAttribute();
    }

    for(const auto& attr : m_OutputAttributes) {
      static I32 offset = static_cast<I32>(ShaderGraphAttributeType::Output);
      ImNodes::BeginOutputAttribute((m_ID << offset) + attr.ID);
      ImGui::Indent(120.0f - ImGui::CalcTextSize(attr.title.c_str()).x);
      ImGui::TextUnformatted(attr.title.c_str());
      ImNodes::EndOutputAttribute();
    }

    // Regenerate the texture.
    CreateTexture();

    {
      static I32 offset = static_cast<I32>(ShaderGraphAttributeType::Static);
      const char *label = fmt::format("##{}{}", m_ID << offset, 10).c_str();
      ImGui::Image(reinterpret_cast<void*>(m_TextureID), ImVec2(120, 120));
    }

    ImNodes::EndNode();
  }

  void OnNodeLinkDelete(I32 inputAttribute) override {
    switch(inputAttribute) {
      case 0:
        m_GridSize = 1;
        break;
      case 1:
        m_FirstColor = glm::vec3();
        break;
      case 2:
        m_SecondColor = glm::vec3();
        break;
      default:
        break;
    }
  }

  void SetInputAttributeValue(I32 inputAttribute, void *value) override {
    switch (inputAttribute) {
      case 0:
        m_GridSize = *(reinterpret_cast<U32 *>(value));
        break;
      case 1:
        m_FirstColor = *(reinterpret_cast<glm::vec3 *>(value));
        break;
      case 2:
        m_SecondColor = *(reinterpret_cast<glm::vec3 *>(value));
        break;
      default:
        break;
    }
  }

  void *GetOutputAttributeValue(I32 outputAttribute) override {
    return reinterpret_cast<void *>(m_TextureID);
  }

 private:
  U32 m_GridSize{};
  glm::vec3 m_FirstColor{}, m_SecondColor{};
  U32 m_TextureID{};

  void CreateTexture() {
    U32 width = 512;
    U32 height = 512;
    U32 cellSize = m_GridSize > 0 ? width / m_GridSize : width;

    std::vector<GLubyte> data(width * height * 3);

    for (GLsizei y = 0; y < height; ++y) {
      for (GLsizei x = 0; x < width; ++x) {
        bool isColor1 = ((x / cellSize) % 2 == (y / cellSize) % 2);
        glm::vec3 color = isColor1 ? m_FirstColor : m_SecondColor;
        size_t idx = (y * width + x) * 3;

        data[idx]     = static_cast<GLubyte>(color.r * 255);
        data[idx + 1] = static_cast<GLubyte>(color.g * 255);
        data[idx + 2] = static_cast<GLubyte>(color.b * 255);
      }
    }

    if (m_TextureID == 0) {
      glGenTextures(1, &m_TextureID);
      glBindTexture(GL_TEXTURE_2D, m_TextureID);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
      // Update the existing texture data
      glBindTexture(GL_TEXTURE_2D, m_TextureID);
      glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data.data());
    }

    glBindTexture(GL_TEXTURE_2D, 0);
  }
};

};