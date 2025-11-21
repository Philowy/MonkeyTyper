#include <cstdlib>
#include "Text.hpp"

//static
sf::Vector2f Text::windowSize = {1920, 1080};
sf::Vector2f Text::skala = {1, 1};
sf::Font Text::font;
std::string Text::fontName = "centurygothic";
int Text::charakterSize = 26;
std::vector<std::string> Text::words;
std::vector<Text> Text::generatedTexts;
float Text::textSpeed = 1;
int Text::generationSpeed = 20;
sf::Vector2f Text::upperLeftCorner;
sf::Vector2f Text::lowerRightCorner;


Text::Text() {
    // https://www.w3schools.com/cpp/cpp_howto_random_number.asp
    int randomNum = rand() % words.size();
    word = words[randomNum];
    //std::string word = "abagjc";
    float textLength;
    int iterator = 0;

    for (const auto c : word) {
        vectorText.push_back(sf::Text(font, c, charakterSize));
        auto bounds = vectorText[iterator++].getLocalBounds();
        textLength += bounds.size.x;
        textLength += charakterSize/6;
    }

    reference.setSize({textLength, charakterSize + 2.f});
    auto bounds = reference.getGlobalBounds();
    reference.setOrigin({0, bounds.size.y/2.f}); // środek lewej ścianki

    //ustawianie na podstawie podanych granic
    float randomNumber = rand() % int(lowerRightCorner.y*(0.9) - upperLeftCorner.y) + upperLeftCorner.y*(1.05) + windowSize.y*(1.f/35.f);

    reference.setPosition({upperLeftCorner.x, randomNumber});

    reference.setFillColor(sf::Color::Black);

    // środkowanie i synchronizowanie z reference
    setToMiddle();
}

void Text::setOrigin(sf::Text& letter) {
    // a b c d e f g h i j k l m n o p q r s t u v w x y z
    // aceimnorsuwxz
    // bdfhklt
    // jpqy

    auto bounds = letter.getGlobalBounds();

    // https://www.geeksforgeeks.org/stringnpos-in-c-with-examples/
    if (std::string("acemnorsuvwxz").find(letter.getString()) != std::string::npos)
        letter.setOrigin({0, bounds.size.y+charakterSize*0.2f});
    else if (letter.getString() == 'j') {
        letter.setOrigin({0-charakterSize*0.1f, bounds.size.y-charakterSize*0.2f});
    }
    else
        letter.setOrigin({0, bounds.size.y});
}

void Text::textMove() {

    reference.move({textSpeed, 0});
    for (auto& singular : vectorText) {
        singular.move({textSpeed, 0});
        singular.setCharacterSize(charakterSize);
    }
    setToMiddle();
}

void Text::setToMiddle() {
    auto bounds = vectorText[0].getGlobalBounds();

    for (int i = 0; i < vectorText.size(); i++) {
        setOrigin(vectorText[i]);
        if (i==0) vectorText[i].setPosition(reference.getPosition());
        else {
            if (std::string("yg").find(vectorText[i-1].getString()) != std::string::npos) {
                bounds = vectorText[i-1].getGlobalBounds();
                bounds.size.x = bounds.size.x - charakterSize/10.f;
            }
            else bounds = vectorText[i-1].getGlobalBounds();
            vectorText[i].setPosition({vectorText[i-1].getPosition().x+bounds.size.x+charakterSize/6.f, reference.getPosition().y});
        }
    }
}