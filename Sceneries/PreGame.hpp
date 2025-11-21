#pragma once
#include "../Class/Button.hpp"
#include "../Enums.hpp"

void preGameSetUp(sf::RenderWindow&);
void preGameMain(sf::RenderWindow&);
void preGameEvent(Stage&, const std::optional<sf::Event>&, sf::RenderWindow&, Difficulty& difficulty);