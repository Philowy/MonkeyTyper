#pragma once

#include <vector>
#include <map>

#include "../Class/Button.hpp"
#include "../Enums.hpp"

void menuSetUp(const sf::RenderWindow& window);
void menuMain(sf::RenderWindow& window);
void menuEvent(const std::optional<sf::Event>& event, Stage& gameState, sf::RenderWindow& window);
std::vector<sf::Sprite> makeSprites (const sf::RenderWindow& window);
sf::Sprite makeSprite (const sf::RenderWindow& window,  const sf::Texture&, sf::Vector2f, sf::Vector2f);
std::map<int, sf::Texture> loadTextures ();
std::vector<sf::Sprite>& getSprites ();