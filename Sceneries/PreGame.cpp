#include <fmt/ranges.h>

#include "../Enums.hpp"
#include "../Class/Text.hpp"

#include "PreGame.hpp"
#include "Game.hpp"
#include "Menu.hpp"

std::vector<sf::Sprite> spritesPreGame;

void preGameSetUp(sf::RenderWindow& window) {
    spritesPreGame = getSprites();
}

void preGameMain(sf::RenderWindow& window) {
    auto mousePos = sf::Mouse::getPosition(window);
    for (int i = 5 ; i<13; i+=2) {
        if (i == 7) {
            i--;
            continue;
        }

        if (spritesPreGame[i].getGlobalBounds().contains({float(mousePos.x), float(mousePos.y)}))
            window.draw(spritesPreGame[i+1]);
        else
            window.draw(spritesPreGame[i]);
    }
}

void preGameEvent(Stage& gameState, const std::optional<sf::Event>& event, sf::RenderWindow& window, Difficulty& difficulty) {
    if (auto mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
        auto ifContains = [mouse](int number) {
            return spritesPreGame[number].getGlobalBounds().contains({float(mouse->position.x), float(mouse->position.y)});
        };
        auto reset = [&window]() {
            Text::generatedTexts.clear();
            Text::upperLeftCorner = {window.getSize().x*(.09f), window.getSize().y*(.1f)};
            Text::lowerRightCorner = {window.getSize().x*.95f, window.getSize().y*(.85f)};
            getLives() = 3;
            getPointsNumber() = 0;
        };
        if (ifContains(5))
            gameState = MENU;

        if (ifContains(8)) {
            reset();
            difficulty = EASY;
            Text::textSpeed = 1;
            Text::generationSpeed = 120;
            gameState = GAME;
        }

        if (ifContains(10)) {
            reset();
            difficulty = MEDIUM;
            Text::textSpeed = 2;
            Text::generationSpeed = 70;
            gameState = GAME;
        }

        if (ifContains(12)) {
            reset();
            difficulty = HARD;
            Text::textSpeed = 3;
            Text::generationSpeed = 40;
            gameState = GAME;
        }
    }
}