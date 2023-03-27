#pragma once

#include "Editor/Widgets/ShaderGraph/ShaderGraphNode.h"
#include "Core/Utils.h"

namespace ambr {

template <typename T>
class ConstantShaderGraphNode : public ShaderGraphNode {
 public:
  ConstantShaderGraphNode() : ShaderGraphNode() {}
  virtual ~ConstantShaderGraphNode() = default;

  void OnInitialize() override {
    m_OutputAttributes.clear();

    m_Value = 0;

    PushStaticAttribute("Constant_Slider");
    PushOutputAttribute("Constant");

    m_Title = fmt::format("Constant<{}>", GetTypeName<decltype(m_Value)>());
  }

  void OnRender() override {
    ImNodes::BeginNode(m_ID);

    ImNodes::BeginNodeTitleBar();
    ImGui::TextUnformatted(m_Title.c_str());
    ImNodes::EndNodeTitleBar();

    for (const auto &attr : m_OutputAttributes) {
      static I32 offset = static_cast<I32>(ShaderGraphAttributeType::Output);
      ImNodes::BeginOutputAttribute((m_ID << offset) + attr.ID);
      ImGui::PushItemWidth(120.0f);
      RenderConstantSlider(offset, attr);
      ImGui::SameLine();
      ImGui::Indent(240.0f - ImGui::CalcTextSize(attr.title.c_str()).x);
      ImGui::TextUnformatted(attr.title.c_str());
      ImNodes::EndOutputAttribute();
    }

    ImNodes::EndNode();
  }

  void* GetOutputAttributeValue(I32 outputAttribute) override {
    return &m_Value;
  }

  void SetValue(const T& value) {
    m_Value = value;
  }

  [[nodiscard]] const T& GetValue() const {
    return m_Value;
  }

  void RenderConstantSlider(I32 offset, const ShaderGraphNodeAttribute& attribute) {}

 protected:
  T m_Value;
};

template<> inline void ConstantShaderGraphNode<float>::RenderConstantSlider(I32 offset, const ShaderGraphNodeAttribute& attribute) {
  const char* label = fmt::format("##{}{}", m_ID << offset, attribute.ID).c_str();
  ImGui::DragScalar(label, ImGuiDataType_Float, static_cast<float*>(&m_Value), 0.1f, 0, 0, "%.2f");
}

template<> inline void ConstantShaderGraphNode<double>::RenderConstantSlider(I32 offset, const ShaderGraphNodeAttribute& attribute) {
  const char* label = fmt::format("##{}{}", m_ID << offset, attribute.ID).c_str();
  ImGui::DragScalar(label, ImGuiDataType_Double, static_cast<double*>(&m_Value), 0.1f, 0, 0, "%.2f");
}

template<> inline void ConstantShaderGraphNode<U32>::RenderConstantSlider(I32 offset, const ShaderGraphNodeAttribute& attribute) {
  const char* label = fmt::format("##{}{}", m_ID << offset, attribute.ID).c_str();
  ImGui::DragScalar(label, ImGuiDataType_U32, static_cast<U32*>(&m_Value), 1, 0, 0, "%d");
}

template<> inline void ConstantShaderGraphNode<U16>::RenderConstantSlider(I32 offset, const ShaderGraphNodeAttribute& attribute) {
  const char* label = fmt::format("##{}{}", m_ID << offset, attribute.ID).c_str();
  ImGui::DragScalar(label, ImGuiDataType_U16, static_cast<U16*>(&m_Value), 1, 0, 0, "%d");
}

template<> inline void ConstantShaderGraphNode<U8>::RenderConstantSlider(I32 offset, const ShaderGraphNodeAttribute& attribute) {
  const char* label = fmt::format("##{}{}", m_ID << offset, attribute.ID).c_str();
  ImGui::DragScalar(label, ImGuiDataType_U8, static_cast<U8*>(&m_Value), 1, 0, 0, "%d");
}

template<> inline void ConstantShaderGraphNode<I32>::RenderConstantSlider(I32 offset, const ShaderGraphNodeAttribute& attribute) {
  const char* label = fmt::format("##{}{}", m_ID << offset, attribute.ID).c_str();
  ImGui::DragScalar(label, ImGuiDataType_S32, static_cast<I32*>(&m_Value), 1, 0, 0, "%d");
}

template<> inline void ConstantShaderGraphNode<I16>::RenderConstantSlider(I32 offset, const ShaderGraphNodeAttribute& attribute) {
  const char* label = fmt::format("##{}{}", m_ID << offset, attribute.ID).c_str();
  ImGui::DragScalar(label, ImGuiDataType_S16, static_cast<I16*>(&m_Value), 1, 0, 0, "%d");
}

template<> inline void ConstantShaderGraphNode<I8>::RenderConstantSlider(I32 offset, const ShaderGraphNodeAttribute& attribute) {
  const char* label = fmt::format("##{}{}", m_ID << offset, attribute.ID).c_str();
  ImGui::DragScalar(label, ImGuiDataType_S8, static_cast<I8*>(&m_Value), 1, 0, 0, "%d");
}

};  // namespace ambr