#include "Button.hpp"

#include "../Class/Font.hpp""
#include "Text.hpp"
#include "fmt/color.h"

//static
sf::Font Button::defaultFont;
sf::Vector2f Button::windowSize = {1920, 1080};
sf::Vector2f Button::skala = {Button::windowSize.x/1920.f , Button::windowSize.y/1080.f};
std::vector<Button> Button::buttonsMenu;
std::vector<Button> Button::buttonsSettings;

//static
void Button::backlightArea(const sf::Vector2i& mousePos) {
    for (auto& button : buttonsMenu) {
        if (button.area.getGlobalBounds().contains({float(mousePos.x), float(mousePos.y)}))
            button.text.setFillColor(button.secondColor);
        else
            button.text.setFillColor(button.firstColor);
    }

    for (auto& button : buttonsSettings) {
        if (button.area.getGlobalBounds().contains({float(mousePos.x), float(mousePos.y)}))
            button.text.setFillColor(button.secondColor);
        else
            button.text.setFillColor(button.firstColor);
    }

    // kolorki dla klikniętych przycisków rozmiaru czcionki
    for (int i = 1; i < 5; i++) {
        if (Text::charakterSize == (26 + (i-1)*8)) buttonsSettings[i].setFirstColor(sf::Color(65,157,229));
        else buttonsSettings[i].setFirstColor(sf::Color(153,153,153));
    }

    // kolorki dla klikniętych przycisków stylów fonta
    for (int i = 5; i < Font::fonts.size()+5; i++) {
        if (Text::fontName == Font::fonts[i-5].getFontName()) buttonsSettings[i].setFirstColor(sf::Color(65,157,229));
        else buttonsSettings[i].setFirstColor(sf::Color(153,153,153));
    }
}

int Button::lowestCharakterSize(const std::vector<Button>& vector) {
    auto number = vector[0].text.getCharacterSize();
    for (auto item : vector) {
        if (number > item.text.getCharacterSize())
            number = item.text.getCharacterSize();
    }
    return number;
}

Button::Button(const std::string& napis): text(defaultFont, napis, individualSize) {
    area.setScale(skala);

    text.setFillColor(sf::Color(153,153,153));

    auto bounds = area.getLocalBounds();
    area.setOrigin(bounds.getCenter());
    area.setPosition({windowSize.x/2, windowSize.y/2});
    area.setFillColor(firstColor);
    area.setOutlineColor(sf::Color(65,157,229));
    area.setOutlineThickness(3);

    text.setScale(skala);
    bounds = text.getLocalBounds();
    text.setOrigin(bounds.getCenter());
    text.setPosition(area.getPosition());
}

void Button::changeFont(Font& newFont) {
    //individualFont = newFont;
    text.setFont(newFont.getFont());
    Text::fontName = newFont.getFontName();


    auto temp = text.getCharacterSize();
    auto bounds = text.getGlobalBounds();
    while (bounds.size.x > area.getSize().x*(9.f/10.f) or bounds.size.y > area.getSize().y*(9.f/10.f)) {
        if (temp <= 5) break; // czcionka za mała
        text.setCharacterSize(--temp);
        bounds = text.getGlobalBounds();
    }
    bounds = text.getLocalBounds();
    text.setOrigin(bounds.getCenter());
    text.setPosition(area.getPosition());
}

void Button::changeTextSize(const int newSize) {
    individualSize = newSize;
    text.setCharacterSize(individualSize);
    auto bounds = text.getLocalBounds();
    text.setOrigin(bounds.getCenter());
    text.setPosition(area.getPosition());
}

void Button::repaintButton(const sf::Color firstColor, const sf::Color secondColor) {
    this->firstColor = firstColor;
    this->secondColor = secondColor;
}

void Button::changeButtonSize(const sf::Vector2f skala) {
    auto position = area.getPosition();
    area.setScale(skala);

    auto bounds = text.getGlobalBounds();
    auto temp = text.getCharacterSize();
    while (bounds.size.x > area.getSize().x or bounds.size.y > area.getSize().y) {
        text.setCharacterSize(--temp);
        bounds = text.getGlobalBounds();
    }
    bounds = text.getLocalBounds();
    text.setOrigin(bounds.getCenter());

    bounds = area.getLocalBounds();
    area.setOrigin(bounds.getCenter());
    area.setPosition(position);
    text.setPosition(area.getPosition());
}

void Button::setPosition(const sf::Vector2f& position) {
    area.setPosition(position);
    text.setPosition(area.getPosition());
}

void Button::setFirstColor(const sf::Color& color) {
    firstColor = color;
    area.setFillColor(firstColor);
}

void Button::setSecondColor(const sf::Color& color) {
    secondColor = color;
}