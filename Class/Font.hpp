#pragma once
#include <vector>

#include "SFML/Graphics/Font.hpp"

class Font {
    sf::Font font;
    std::string fontName;

public:
    static std::vector<Font> fonts;

    Font(std::string, sf::Font);

    const sf::Font& getFont();
    const std::string& getFontName();
};
