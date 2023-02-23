#include "Assets/Font.h"

namespace ambr {

void FontManager::OnInitialization(void* specs) {
  LoadFont(FontID::RubikRegular,
           "assets/fonts/Rubik/Rubik-Regular.ttf", 18);
  LoadFont(FontID::RubikBold,
           "assets/fonts/Rubik/Rubik-Bold.ttf", 18);
}

void FontManager::OnUpdate() {}

void FontManager::OnDestroy() {}

Font FontManager::LoadFont(const FontID id, const String& path, const U8 size) {
  const auto& io = SystemLocator<Editor>::Get()->GetIO();

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

std::vector<std::shared_ptr<System>> FontManager::GetDependencies() const
{
	return { SystemLocator<Editor>::Get() };
}

void FontManager::ProcessEvent(const Event& e)
{
}

};  // namespace ambr