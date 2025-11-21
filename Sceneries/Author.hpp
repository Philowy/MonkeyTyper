#pragma once

#include "../Enums.hpp"
#include "SFML/Graphics.hpp"

void authorSetUp(sf::RenderWindow& window);
void authorMain(sf::RenderWindow& window);
void authorEvent(const std::optional<sf::Event>& event, Stage& gameState);