#pragma once
#include <SFML/Graphics.hpp>
#include "../Class/Font.hpp"

class Button {
    sf::Color firstColor = sf::Color(153,153,153);
    sf::Color secondColor = sf::Color(235,235,235);
    int individualSize = 60;

public:
    sf::RectangleShape area = sf::RectangleShape(sf::Vector2f(300, 90));
    sf::Text text;
    static sf::Font defaultFont;
    static sf::Vector2f windowSize;
    static sf::Vector2f skala;
    static std::vector<Button> buttonsMenu;
    static std::vector<Button> buttonsSettings;

    static void backlightArea(const sf::Vector2i& mousePos);
    static int lowestCharakterSize(const std::vector<Button>& vector);

    Button(const std::string& napis);

    void changeFont(Font& newFont);

    void changeTextSize(int newSize);

    void repaintButton(sf::Color firstColor, sf::Color secondColor);

    void changeButtonSize(sf::Vector2f skala);

    void setPosition(const sf::Vector2f& position);

    void setFirstColor(const sf::Color& color);

    void setSecondColor(const sf::Color& color);
};