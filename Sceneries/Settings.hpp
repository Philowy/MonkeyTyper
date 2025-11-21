#pragma once
#include "../Class/Button.hpp"
#include "../Enums.hpp"

void settingsSetUp(sf::RenderWindow& window);
void settingsMain(sf::RenderWindow& window);
void settingsEvent(const std::optional<sf::Event>& event, Stage& gameState, sf::RenderWindow& window);