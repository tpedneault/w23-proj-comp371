#pragma once

#include "Editor/Widgets/ShaderGraph/ShaderGraphNode.h"
#include "Core/Utils.h"

namespace ambr {

class ColorShaderGraphNode : public ShaderGraphNode {
 public:
  ColorShaderGraphNode() : ShaderGraphNode() {}
  virtual ~ColorShaderGraphNode() = default;

  void OnInitialize() override {
    m_OutputAttributes.clear();
    m_Title = "Color";

    PushInputAttribute("R");
    PushInputAttribute("G");
    PushInputAttribute("B");

    PushOutputAttribute("Color");
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

    {
      static I32 offset = static_cast<I32>(ShaderGraphAttributeType::Input);
      const char* label = fmt::format("##{}{}", m_ID << offset, 10).c_str();
      ImGui::ColorButton(label, m_Color, ImGuiColorEditFlags_NoBorder, ImVec2(120, 120));
    }

    m_Color = ImVec4();

    ImNodes::EndNode();
  }

  void SetInputAttributeValue(I32 inputAttribute, void* value) override {
    float output = *(reinterpret_cast<float*>(value));
    switch(inputAttribute) {
      case 0:
        m_Color.x = output;
        break;
      case 1:
        m_Color.y = output;
        break;
      case 2:
        m_Color.z = output;
        break;
      default:
        break;
    }
  }

 protected:
  ImVec4 m_Color;
};

};