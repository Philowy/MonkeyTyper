#pragma once
#include <SFML/Graphics.hpp>

struct Banan {
    sf::CircleShape kulka = sf::CircleShape(10);
    sf::Sprite sprite;
    float wartoscY;

    static sf::Texture teksturka;


    Banan(sf::RenderWindow& window);
    void leci(sf::RenderWindow& window);
};