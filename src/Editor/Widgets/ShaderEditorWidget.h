#pragma once

#include "Editor/Widget.h"
#include "TextEditor.h"

namespace ambr {

struct ShaderEditorSpecifications {
  String path;
  String name;
};

class ShaderEditorWidget : public Widget {
 public:
  ShaderEditorWidget(const String &id, void *specs) : Widget(id) {
    m_Specs = reinterpret_cast<ShaderEditorSpecifications *>(specs);
  }

  void OnInitialization() override {
    m_LanguageDefinition = TextEditor::LanguageDefinition::GLSL();
    m_Editor.SetLanguageDefinition(m_LanguageDefinition);
    m_Editor.SetPalette(TextEditor::GetDarkPalette());
    m_Editor.SetShowWhitespaces(false);

    // Load file to edit.
    const std::ifstream fin(m_Specs->path);
    if (fin.good()) {
      std::stringstream buffer;
      buffer << fin.rdbuf();
      m_Editor.SetText(buffer.
          str());
    }
  }

  void Render() override {
    const auto cursorPosition = m_Editor.GetCursorPosition();
    ImGui::Begin(
        fmt::format("Shader Editor - {}", m_Specs->name).c_str(), nullptr,
        ImGuiWindowFlags_HorizontalScrollbar);
    {
      ImGui::Text(
          "%6d/%-6d %6d lines | %s | %s | %s | %s", cursorPosition.mLine + 1,
          cursorPosition.mColumn + 1, m_Editor.GetTotalLines(),
          m_Editor.IsOverwrite() ? "Ovr" : "Ins",
          m_Editor.CanUndo() ? "*" : " ",
          m_Editor.GetLanguageDefinition().mName.c_str(), m_Specs->path.c_str());

      m_Editor.Render("TextEditor");
    }
    ImGui::End();
  }

 private:
  ShaderEditorSpecifications *m_Specs;
  TextEditor m_Editor{};
  TextEditor::LanguageDefinition m_LanguageDefinition{};
};

};  // namespace ambr