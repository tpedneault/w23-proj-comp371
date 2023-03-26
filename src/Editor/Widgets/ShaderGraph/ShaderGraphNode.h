#pragma once

#include "imnodes.h"
#include "imnodes_internal.h"

#include "Core/Base.h"

namespace ambr {

enum class ShaderGraphAttributeType : I32 {
  Input  = 8,
  Static = 16,
  Output = 24
};

struct ShaderGraphNodeAttribute {
  I32 ID;
  String title;
};

class ShaderGraphNode {
 public:
  ShaderGraphNode() : m_ID(0) { }
  virtual ~ShaderGraphNode() = default;

  virtual void OnInitialize() {}

  virtual void OnRender() {
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

    for(const auto &attr : m_StaticAttributes) {
      static I32 offset = static_cast<I32>(ShaderGraphAttributeType::Static);
      ImNodes::BeginStaticAttribute((m_ID << offset) + attr.ID);
      ImGui::PushItemWidth(120.0f);
      ImGui::TextUnformatted(attr.title.c_str());
      ImNodes::EndStaticAttribute();
    }

    for(const auto& attr : m_OutputAttributes) {
      static I32 offset = static_cast<I32>(ShaderGraphAttributeType::Output);
      ImNodes::BeginOutputAttribute((m_ID << offset) + attr.ID);
      ImGui::Indent(120.0f - ImGui::CalcTextSize(attr.title.c_str()).x);
      ImGui::TextUnformatted(attr.title.c_str());
      ImNodes::EndOutputAttribute();
    }

    ImNodes::EndNode();
  }

  void SetID(I32 id) {
    m_ID = id;
  }

  [[nodiscard]] I32 GetID() const {
    return m_ID;
  }

  [[nodiscard]] const String& GetTitle() const {
    return m_Title;
  }

 protected:
  I32 m_ID{};
  String m_Title;

  I32 m_NextInputAttributeID = 0;
  I32 m_NextStaticAttributeID = 0;
  I32 m_NextOutputAttributeID = 0;

  std::vector<ShaderGraphNodeAttribute> m_InputAttributes;
  std::vector<ShaderGraphNodeAttribute> m_StaticAttributes;
  std::vector<ShaderGraphNodeAttribute> m_OutputAttributes;

  I32 PushInputAttribute(const String& title) {
    m_InputAttributes.push_back({ m_NextInputAttributeID++, title });
    return m_InputAttributes.back().ID;
  }

  I32 PushStaticAttribute(const String& title) {
    m_StaticAttributes.push_back({ m_NextStaticAttributeID++, title });
    return m_StaticAttributes.back().ID;
  }

  I32 PushOutputAttribute(const String& title) {
    m_OutputAttributes.push_back({ m_NextOutputAttributeID++, title });
    return m_OutputAttributes.back().ID;
  }

  void PopInputAttribute() {
    m_InputAttributes.pop_back();
    m_NextInputAttributeID--;
  }

  void PopStaticAttribute() {
    m_StaticAttributes.pop_back();
    m_NextStaticAttributeID--;
  }

  void PopOutputAttribute() {
    m_OutputAttributes.pop_back();
    m_NextOutputAttributeID--;
  }
};

};