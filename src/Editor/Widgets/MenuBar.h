#pragma once

#include "Editor/Widget.h"

namespace ambr {

class MenuBar : public Widget {
 public:
  MenuBar(const String& id) : Widget(id) {}

  void Render() override {
    if (ImGui::BeginMainMenuBar()) {
      /* File Menu */
      if (ImGui::BeginMenu("File"))
      {
        if(ImGui::MenuItem("Import Model")) {
          PublishEvent({ EventCode::Editor_OpenLoadModelWindow });
        }

        if (ImGui::MenuItem("Exit")) {
          PublishEvent({ EventCode::ExitApplication });
        }
        ImGui::EndMenu();
      }

      if(ImGui::BeginMenu("Shader Graph")) {
        if(ImGui::BeginMenu("Add Node")) {
          auto* specs = new ShaderGraph_PushNodeEventSpecifications;
          if(ImGui::BeginMenu("Constant Node")) {
            specs->nodeType = "constant";
            if(ImGui::MenuItem("Vector3f")) {
              specs->templateTypeName = typeid(glm::vec3).name();
              PublishEvent({ EventCode::ShaderGraph_PushNode, specs });
            }
            else if(ImGui::MenuItem("float")) {
              specs->templateTypeName = typeid(float).name();
              PublishEvent({ EventCode::ShaderGraph_PushNode, specs });
            }
            else if(ImGui::MenuItem("double")) {
              specs->templateTypeName = typeid(double).name();
              PublishEvent({ EventCode::ShaderGraph_PushNode, specs });
            }
            else if(ImGui::MenuItem("U32")) {
              specs->templateTypeName = typeid(U32).name();
              PublishEvent({ EventCode::ShaderGraph_PushNode, specs });
            }
            else if(ImGui::MenuItem("U16")) {
              specs->templateTypeName = typeid(U16).name();
              PublishEvent({ EventCode::ShaderGraph_PushNode, specs });
            }
            else if(ImGui::MenuItem("U8")) {
              specs->templateTypeName = typeid(U8).name();
              PublishEvent({ EventCode::ShaderGraph_PushNode, specs });
            }
            else if(ImGui::MenuItem("I32")) {
              specs->templateTypeName = typeid(I32).name();
              PublishEvent({ EventCode::ShaderGraph_PushNode, specs });
            }
            else if(ImGui::MenuItem("I16")) {
              specs->templateTypeName = typeid(I16).name();
              PublishEvent({ EventCode::ShaderGraph_PushNode, specs });
            }
            else if(ImGui::MenuItem("I8")) {
              specs->templateTypeName = typeid(I8).name();
              PublishEvent({ EventCode::ShaderGraph_PushNode, specs });
            }
            else {
              delete specs;
            }
            ImGui::EndMenu();
          }
          else if(ImGui::MenuItem("Color Node")) {
            specs->nodeType = "color";
            PublishEvent({ EventCode::ShaderGraph_PushNode, specs });
          }
          else if(ImGui::MenuItem("Checkerboard Node")) {
            specs->nodeType = "checkerboard";
            PublishEvent({ EventCode::ShaderGraph_PushNode, specs });
          }
          else if(ImGui::MenuItem("Register Texture")) {
            specs->nodeType = "register_texture";
            PublishEvent({ EventCode::ShaderGraph_PushNode, specs });
          }
          else {
            delete specs;
          }
          ImGui::EndMenu();
        }

        if(ImGui::MenuItem("Remove Node")) {
          PublishEvent({ EventCode::ShaderGraph_PopNode });
        }
        ImGui::EndMenu();
      }

      /* Edit Menu */
      if (ImGui::BeginMenu("Edit"))
      {
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("View"))
      {
        ImGui::EndMenu();
      }

      ImGui::EndMainMenuBar();
    }
  }
};

};  // namespace ambr