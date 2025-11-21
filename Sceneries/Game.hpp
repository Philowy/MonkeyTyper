#pragma once
#include "../Class/Button.hpp"
#include "../Enums.hpp"

void gameSetUp(sf::RenderWindow& window);
void gameMain(sf::RenderWindow& window, Difficulty& difficulty, Stage& stage);
void gameEvent(const std::optional<sf::Event>& event, Stage& gameState, sf::RenderWindow& window);
int& getLives();
int& getPointsNumber();