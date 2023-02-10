#pragma once

#include "Gui/Widget.h"

namespace ambr {

class ShaderEditorWidget : public Widget {
  void Render() override {
    ImGui::Begin("Shader Editor");
    {
	    
    }
    ImGui::End();
  }
};

};  // namespace ambr