#pragma once

#include "Editor/Widget.h"

namespace ambr {

class LoadModelWidget : public Widget {
 public:
  explicit LoadModelWidget(const String& id) : Widget(id), m_LoadModelSpecs(new LoadModelEventSpecs()) {}

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
        PublishEvent({EventCode::ImportModel, m_LoadModelSpecs });
        PublishEvent({ EventCode::CloseLoadModelWindow });
      }
      ImGui::SameLine();
      if(ImGui::Button("Close")) {
        PublishEvent({ EventCode::CloseLoadModelWindow });
      }
    }
    ImGui::End();
  }

 private:
  LoadModelEventSpecs* m_LoadModelSpecs;
};

};
