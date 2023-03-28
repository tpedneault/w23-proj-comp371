#pragma once

#include "Editor/Widget.h"
#include "Nodes/ConstantNode.h"
#include "Nodes/ColorNode.h"
#include "Nodes/CheckerboardTextureNode.h"
#include "Nodes/RegisterTextureNode.h"

namespace ambr {

class ShaderGraphWidget : public Widget {
 public:
  explicit ShaderGraphWidget(const String &id) : Widget(id) {}

  ~ShaderGraphWidget() override {
    ImNodes::DestroyContext();
  }

  void OnInitialization() override {
    ImNodes::CreateContext();
    ImNodes::PushAttributeFlag(ImNodesAttributeFlags_EnableLinkDetachWithDragClick);

    PushNode<ConstantNode<glm::vec3>>();
  }

  void Render() override {
    ImGui::Begin("Shader Graph", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    {
      ImNodes::BeginNodeEditor();

      // Perform the operations that need to be performed on a Node to Node basis.
      for (auto &node : m_Nodes) {
        for (I32 i = 0; i < node->GetInputAttributeCount(); i++) {
          auto [outputNode, outputAttr] = FindConnectedNodeAndAttribute(node->GetID(), i);
          if (outputNode) {
            auto value = outputNode->GetOutputAttributeValue(outputAttr);
            node->SetInputAttributeValue(i, value);
          }
        }

        // Forward the events created in the node.
        auto events = node->ForwardEvents();
        for (const auto &event : events) {
          m_EventQueue.push_back(event);
        }

        // Render the node.
        node->OnRender();
      }

      // Render the existing links between two nodes.
      for (int i = 0; i < m_Links.size(); i++) {
        const auto &link = m_Links[i];
        ImNodes::Link(i, link.first, link.second);
      }

      ImNodes::EndNodeEditor();

      // Check if a link was created between two attributes.
      I32 startAttribute, endAttribute;
      if (ImNodes::IsLinkCreated(&startAttribute, &endAttribute)) {
        m_Links.emplace_back(startAttribute, endAttribute);
        auto link = m_Links.back();

        // Find the information of the node which takes in the input.
        I32 inputNodeID = GetNodeIDFromLinkID(ShaderGraphAttributeType::Input, link.second);
        I32 inputAttribute = GetAttributeIDFromLinkID(ShaderGraphAttributeType::Input, link.second);

        // Call the OnNodeLinkDelete function to inform the node that its input connection was severed.
        for (const auto &node : m_Nodes) {
          if (node->GetID() == inputNodeID) {
            node->OnNodeLinkCreate(inputAttribute);
            break;
          }
        }
      }

      // Check if a link was destroyed in the current frame.
      I32 removedLinkIndex;
      if (ImNodes::IsLinkDestroyed(&removedLinkIndex)) {
        auto &link = m_Links[removedLinkIndex];

        // Find the information of the node which takes in the input.
        I32 inputNodeID = GetNodeIDFromLinkID(ShaderGraphAttributeType::Input, link.second);
        I32 inputAttribute = GetAttributeIDFromLinkID(ShaderGraphAttributeType::Input, link.second);

        // Call the OnNodeLinkDelete function to inform the node that its input connection was severed.
        for (const auto &node : m_Nodes) {
          if (node->GetID() == inputNodeID) {
            node->OnNodeLinkDelete(inputAttribute);
            break;
          }
        }

        m_Links.erase(m_Links.begin() + removedLinkIndex);
      }
    }

    ImGui::End();
  }

  void ProcessEvent(const Event &e) override {
    switch (e.code) {
      case EventCode::ShaderGraph_PopNode:
        PopNode();
        break;
      case EventCode::ShaderGraph_PushNode: {
        auto specs = static_cast<ShaderGraph_PushNodeEventSpecifications *>(e.data);
        if (specs->nodeType == "constant") {
          if (specs->templateTypeName == typeid(glm::vec3).name()) {
            PushNode<ConstantNode<glm::vec3>>();
          } else if (specs->templateTypeName == typeid(float).name()) {
            PushNode<ConstantNode<float>>();
          } else if (specs->templateTypeName == typeid(double).name()) {
            PushNode<ConstantNode<double>>();
          } else if (specs->templateTypeName == typeid(U32).name()) {
            PushNode<ConstantNode<U32>>();
          } else if (specs->templateTypeName == typeid(U16).name()) {
            PushNode<ConstantNode<U16>>();
          } else if (specs->templateTypeName == typeid(U8).name()) {
            PushNode<ConstantNode<U8>>();
          } else if (specs->templateTypeName == typeid(I32).name()) {
            PushNode<ConstantNode<I32>>();
          } else if (specs->templateTypeName == typeid(U16).name()) {
            PushNode<ConstantNode<I16>>();
          } else if (specs->templateTypeName == typeid(I8).name()) {
            PushNode<ConstantNode<I8>>();
          }
        } else if (specs->nodeType == "color") {
          PushNode<ColorNode>();
        } else if (specs->nodeType == "checkerboard") {
          PushNode<CheckerboardTextureNode>();
        } else if (specs->nodeType == "register_texture") {
          PushNode<RegisterTextureNode>();
        }
        delete specs;
        break;
      }
      default:
        break;
    }

    for (const auto &node : m_Nodes) {
      node->ProcessEvent(e);
    }
  }

 private:
  std::vector<std::shared_ptr<ShaderGraphNode>> m_Nodes;
  std::vector<std::pair<I32, I32>> m_Links;

  I32 m_NextNodeID = 0;

  template<typename T>
  void PushNode() {
    static_assert(std::is_base_of_v<ShaderGraphNode, T>,
                  "Class T must inherit from the ShaderGraphNode class.");
    m_Nodes.push_back(std::make_shared<T>());
    m_Nodes.back()->SetID(m_NextNodeID++);
    m_Nodes.back()->OnInitialize();
  }

  void PopNode() {
    if (!m_Nodes.empty()) {
      RemoveFloatingLinks(m_Nodes.back()->GetID());
      m_Nodes.back()->OnDestroy();
      m_Nodes.pop_back();
      m_NextNodeID--;
    }
  }

  void RemoveFloatingLinks(I32 deletedNode) {
    for (I32 i = 0; i < m_Links.size(); i++) {
      const auto &link = m_Links[i];
      I32 lhs, rhs;

      lhs = GetNodeIDFromLinkID(ShaderGraphAttributeType::Output, link.first);
      rhs = GetNodeIDFromLinkID(ShaderGraphAttributeType::Input, link.second);

      if (lhs == deletedNode || rhs == deletedNode) {
        m_Links.erase(m_Links.begin() + i);
        i--;
      }
    }
  }

  static I32 GetNodeIDFromLinkID(ShaderGraphAttributeType attributeType, I32 id) {
    return id >> static_cast<I32>(attributeType);
  }

  static I32 GetAttributeIDFromLinkID(ShaderGraphAttributeType attributeType, I32 id) {
    return id - (GetNodeIDFromLinkID(attributeType, id) << static_cast<I32>(attributeType));
  }

  std::pair<std::shared_ptr<ShaderGraphNode>, I32> FindConnectedNodeAndAttribute(I32 nodeID, I32 inputAttr) {
    I32 inputLinkID = (nodeID << static_cast<I32>(ShaderGraphAttributeType::Input)) + inputAttr;
    for (const auto &link : m_Links) {
      if (link.second == inputLinkID) {
        I32 outputNodeID = GetNodeIDFromLinkID(ShaderGraphAttributeType::Output, link.first);
        I32 outputAttr = GetAttributeIDFromLinkID(ShaderGraphAttributeType::Output, link.first);
        for (const auto &node : m_Nodes) {
          if (node->GetID() == outputNodeID) {
            return {node, outputAttr};
          }
        }
      }
    }
    return {nullptr, -1};
  }

};

};