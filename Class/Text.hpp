#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Text {
public:
    std::vector<sf::Text> vectorText;
    sf::RectangleShape reference;
    std::string word;

    static sf::Vector2f windowSize;
    static sf::Vector2f skala;
    static sf::Font font;
    static std::string fontName;
    static int charakterSize;
    static std::vector<std::string> words;
    static std::vector<Text> generatedTexts;
    static float textSpeed;
    static int generationSpeed;
    static sf::Vector2f upperLeftCorner;
    static sf::Vector2f lowerRightCorner;


    Text();

    void setOrigin(sf::Text& letter);
    void textMove();
    void setToMiddle();
};