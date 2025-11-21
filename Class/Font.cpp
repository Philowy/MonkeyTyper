#include "Font.hpp"

// static
std::vector<Font> Font::fonts;

// Fonts(fontName, fontPath);
Font::Font(const std::string fontName, const sf::Font fontPath) {
    this->fontName = fontName;
    this->font = fontPath;
}

const sf::Font& Font::getFont() {
    return this->font;
}

const std::string& Font::getFontName() {
    return this->fontName;
}