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

enum class ShaderGraphAttributeDataType : I32 {
  None,
  Vector3f,
  Float,
  Double,
  U32,
  U16,
  U8,
  I32,
  I16,
  I8,
};

static String ShaderGraphAttributeDataTypeToString(ShaderGraphAttributeDataType type) {
  switch (type) {
    case ShaderGraphAttributeDataType::Vector3f:
      return "Vector3f";
    case ShaderGraphAttributeDataType::Float:
      return "Float";
    case ShaderGraphAttributeDataType::Double:
      return "Double";
    case ShaderGraphAttributeDataType::U32:
      return "U32";
    case ShaderGraphAttributeDataType::U16:
      return "U16";
    case ShaderGraphAttributeDataType::U8:
      return "U8";
    case ShaderGraphAttributeDataType::I32:
      return "I32";
    case ShaderGraphAttributeDataType::I16:
      return "I16";
    case ShaderGraphAttributeDataType::I8:
      return "I8";
    default:
      return "Unknown";
  }
}

template <typename T>
static ShaderGraphAttributeDataType ShaderGraphAttributeDataTypeFromTypeID() {
  if(typeid(T) == typeid(glm::vec3)) {
    return ShaderGraphAttributeDataType::Vector3f;
  } else if(typeid(T) == typeid(float)) {
    return ShaderGraphAttributeDataType::Float;
  } else if(typeid(T) == typeid(double)) {
    return ShaderGraphAttributeDataType::Double;
  } else if(typeid(T) == typeid(U32)) {
    return ShaderGraphAttributeDataType::U32;
  } else if(typeid(T) == typeid(U16)) {
    return ShaderGraphAttributeDataType::U16;
  } else if(typeid(T) == typeid(U8)) {
    return ShaderGraphAttributeDataType::U8;
  } else if(typeid(T) == typeid(I32)) {
    return ShaderGraphAttributeDataType::I32;
  } else if(typeid(T) == typeid(I16)) {
    return ShaderGraphAttributeDataType::I16;
  } else if(typeid(T) == typeid(I8)) {
    return ShaderGraphAttributeDataType::I8;
  } else {
    return ShaderGraphAttributeDataType::None;
  }
}

struct ShaderGraphNodeAttribute {
  I32 ID;
  String title;
  ShaderGraphAttributeDataType dataType;
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

  virtual void OnDestroy() {

  }

  virtual void OnNodeLinkCreate(I32 inputAttribute) {

  }

  virtual void OnNodeLinkDelete(I32 inputAttribute) {

  }

  virtual void SetInputAttributeValue(I32 inputAttribute, void* value) {}

  virtual void* GetOutputAttributeValue(I32 outputAttribute) {
    return nullptr;
  }

  /**
   * \brief Retrieves and clears the widget's event queue.
   * \return A vector containing the queued events.
   */
  virtual std::vector<Event> ForwardEvents() {
    std::vector<Event> events;
    for (const Event e : m_EventQueue) {
      events.push_back(e);
    }
    m_EventQueue.clear();
    return events;
  }

  /**
   * \brief Adds an event to the widget's event queue.
   * \param e The event to be added to the queue.
   */
  virtual void PublishEvent(const Event &e) {
    m_EventQueue.push_back(e);
  }

  /**
   * \brief Processes an incoming event.
   * \param e The event to be processed.
   */
  virtual void ProcessEvent(const Event &e) {

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

  [[nodiscard]] const ShaderGraphNodeAttribute& GetAttribute(ShaderGraphAttributeType type, I32 index) {
    static const ShaderGraphNodeAttribute defaultAttribute{};
    switch(type) {
      case ShaderGraphAttributeType::Input:
        return m_InputAttributes[index];
      case ShaderGraphAttributeType::Static:
        return m_StaticAttributes[index];
      case ShaderGraphAttributeType::Output:
        return m_OutputAttributes[index];
    }
    return defaultAttribute;
  }

  [[nodiscard]] U32 GetInputAttributeCount() const {
    return m_InputAttributes.size();
  }

  [[nodiscard]] U32 GetStaticAttributeCount() const {
    return m_StaticAttributes.size();
  }

  [[nodiscard]] U32 GetOutputAttributeCount() const {
    return m_OutputAttributes.size();
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

  I32 PushInputAttribute(const String& title, ShaderGraphAttributeDataType type) {
    String typeStr = ShaderGraphAttributeDataTypeToString(type);
    m_InputAttributes.push_back({ m_NextInputAttributeID++, fmt::format("{} [{}]", title, typeStr), type });
    return m_InputAttributes.back().ID;
  }

  I32 PushStaticAttribute(const String& title) {
    m_StaticAttributes.push_back({ m_NextStaticAttributeID++, title, ShaderGraphAttributeDataType::None });
    return m_StaticAttributes.back().ID;
  }

  I32 PushOutputAttribute(const String& title, ShaderGraphAttributeDataType type) {
    String typeStr = ShaderGraphAttributeDataTypeToString(type);
    m_OutputAttributes.push_back({ m_NextOutputAttributeID++, fmt::format("{} [{}]", title, typeStr), type });
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

 protected:
  std::vector<Event> m_EventQueue; ///< The event queue used to store widget-related events.
};

};