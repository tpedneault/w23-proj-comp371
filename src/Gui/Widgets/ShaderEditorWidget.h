#pragma once

#include "Gui/Widget.h"
#include "TextEditor.h"

namespace ambr {

class ShaderEditorWidget : public Widget {
 public:
  void OnInitialization() override {
    m_LanguageDefinition = TextEditor::LanguageDefinition::GLSL();
    m_Editor.SetLanguageDefinition(m_LanguageDefinition);
    m_Editor.SetPalette(TextEditor::GetDarkPalette());
    m_ShaderPath = "assets/shaders/vertex_shader.glsl";

    // Load file to edit.
    const std::ifstream fin(m_ShaderPath);
    if (fin.good()) {
      std::stringstream buffer;
      buffer << fin.rdbuf();
      m_Editor.SetText(buffer.str());
    }
  }

  void Render() override {
    const auto cursorPosition = m_Editor.GetCursorPosition();
    ImGui::Begin(
        "Shader Editor", nullptr,
        ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);
    {
      ImGui::BeginMenuBar();
      if (ImGui::BeginMenu("Shader")) {
        if (ImGui::MenuItem("New Shader"))
        {
	        
        }

        if (ImGui::MenuItem("Save"))
        {
	        
        }

        if (ImGui::MenuItem("Save & Recompile"))
        {
	        
        }

        if (ImGui::MenuItem("Recompile"))
        {
	        
        }
        ImGui::EndMenu();
      } else if (ImGui::BeginMenu("Close")) {
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();

      ImGui::Text(
          "%6d/%-6d %6d lines  | %s | %s | %s | %s", cursorPosition.mLine + 1,
          cursorPosition.mColumn + 1, m_Editor.GetTotalLines(),
          m_Editor.IsOverwrite() ? "Ovr" : "Ins",
          m_Editor.CanUndo() ? "*" : " ",
          m_Editor.GetLanguageDefinition().mName.c_str(), m_ShaderPath.c_str());

      m_Editor.Render("TextEditor");
    }
    ImGui::End();
  }

  void SetShaderPath(const String& path) { m_ShaderPath = path; }

 private:
  TextEditor m_Editor{};
  TextEditor::LanguageDefinition m_LanguageDefinition{};
  String m_ShaderPath{};
};

};  // namespace ambr