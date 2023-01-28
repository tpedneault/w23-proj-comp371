#include "Systems/Assets/Font.h"

namespace Zoom {

void FontManager::Initialize(void* specs) {
  LoadFont(FontID::SourceSansProRegular,
           "assets/fonts/SourceSansPro/SourceSansPro-Regular.ttf", 18);
  LoadFont(FontID::SourceSansProBold,
           "assets/fonts/SourceSansPro/SourceSansPro-Bold.ttf", 18);
}

void FontManager::Update() {}

void FontManager::Destroy() {}

Font FontManager::LoadFont(const FontID id, const String& path, const U8 size) {
  const auto& io = SystemLocator<Gui>::Get().GetIO();

  /** Ensure that the requested font is not already loaded. **/
  for (auto& font : m_Fonts) {
    if (font.id == id) {
      return font;
    }
  }

  Font fontData{id, size, io.Fonts->AddFontFromFileTTF(path.c_str(), size)};
  m_Fonts.push_back(fontData);

  return fontData;
}

Font FontManager::GetFont(const FontID id) {
  for (auto& font : m_Fonts) {
    if (font.id == id) {
      return font;
    }
  }

  return {};
}
};  // namespace Zoom