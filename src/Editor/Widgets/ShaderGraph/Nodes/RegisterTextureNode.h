#pragma once

#include "Editor/Widgets/ShaderGraph/ShaderGraphNode.h"
#include "ECS/Components/GraphTexture.h"

namespace ambr {

class RegisterTextureNode : public ShaderGraphNode {
 public:
  RegisterTextureNode() : ShaderGraphNode() {}

  void OnInitialize() override {
    m_Title = "Register Texture";
    PushInputAttribute("Texture ID (U32)");
    m_Texture.nodeID = m_ID;
  }

  void OnRender() override {
    ImNodes::BeginNode(m_ID);

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(m_Title.c_str());
    ImNodes::EndNodeTitleBar();

    for (const auto &attr : m_InputAttributes) {
      static I32 offset = static_cast<I32>(ShaderGraphAttributeType::Input);
      ImNodes::BeginInputAttribute((m_ID << offset) + attr.ID);
      ImGui::TextUnformatted(attr.title.c_str());
      ImNodes::EndInputAttribute();
    }

    static I32 offset = static_cast<I32>(ShaderGraphAttributeType::Static);
    {
      const char* label = fmt::format("##{}{}", m_ID << offset, 10).c_str();
      ImGui::PushItemWidth(120.0f);
      ImGui::InputText(label, &m_Texture.title);
    }

    {
      const char* label = fmt::format("Register [{}]", m_ID).c_str();
      if(ImGui::Button(label)) {
        PublishEvent({EventCode::ShaderGraph_RegisterTexture, &m_Texture});
      }
    }

    {
      static I32 offset = static_cast<I32>(ShaderGraphAttributeType::Static);
      const char *label = fmt::format("##{}{}", m_ID << offset, 10).c_str();
      ImGui::Image(reinterpret_cast<void*>(m_Texture.textureID), ImVec2(120, 120));
    }

    ImNodes::EndNode();
  }

  void OnDestroy() override {
    PublishEvent({EventCode::ShaderGraph_UnregisterTexture, &m_ID});
  }

  void OnNodeLinkDelete(I32 inputAttribute) override {
    PublishEvent({EventCode::ShaderGraph_UnregisterTexture, &m_ID});
  }

  void SetInputAttributeValue(I32 inputAttribute, void *value) override {
    switch (inputAttribute) {
      case 0:
        m_Texture.textureID = *(static_cast<U32 *>(value));
        break;
      default:
        break;
    }
  }

  void *GetOutputAttributeValue(I32 outputAttribute) override {
    return nullptr;
  }

 private:
  GraphTexture m_Texture;
};

};