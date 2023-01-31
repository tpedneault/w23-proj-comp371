#pragma once

#include "Gui/Gui.h"
#include "Core/System.h"

namespace Zoom {

enum class FontID : U8 {
  SourceSansProRegular,
  SourceSansProBold,
};

struct Font {
  const FontID id;
  const U8 pixelSize;
  ImFont* imGuiFont;
};

class FontManager final : public System {
 public:
  void Initialization(void* specs) override;
  void Update() override;
  void Destroy() override;

  Font LoadFont(const FontID id, const String& path, const U8 size);
  Font GetFont(const FontID id);

private:
  std::vector<Font> m_Fonts;
};

};  // namespace Zoom