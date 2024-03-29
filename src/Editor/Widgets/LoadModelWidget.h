#pragma once

#include "Editor/Widget.h"

namespace ambr {

class LoadModelWidget : public Widget {
 public:
  explicit LoadModelWidget(const String& id) : Widget(id), m_LoadModelSpecs(new Editor_LoadModelEventSpecifications()) {}

  ~LoadModelWidget() override {
    delete m_LoadModelSpecs;
  }

  void Render() override {
    ImGui::Begin("Load Model...", nullptr, ImGuiWindowFlags_NoDocking);
    {
      ImGui::Text("Model Name");
      ImGui::InputText("##Name", &m_LoadModelSpecs->name);
      ImGui::Text("Model Path");
      ImGui::InputText("##Path", &m_LoadModelSpecs->path);

      ImGui::Dummy({0.0f, 2.0f});

      if(ImGui::Button("Load")) {
        PublishEvent({EventCode::Editor_ImportModel, m_LoadModelSpecs });
        PublishEvent({ EventCode::Editor_CloseLoadModelWindow });
      }
      ImGui::SameLine();
      if(ImGui::Button("Close")) {
        PublishEvent({ EventCode::Editor_CloseLoadModelWindow });
      }
    }
    ImGui::End();
  }

 private:
  Editor_LoadModelEventSpecifications* m_LoadModelSpecs;
};

};
