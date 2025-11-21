#include "Banan.hpp"

sf::Texture Banan::teksturka;

Banan::Banan(sf::RenderWindow& window): sprite(teksturka) {
    kulka.setPosition({0, 500});
    wartoscY = -int(window.getSize().x*0.5f);

    sprite.setScale({(window.getSize().x/1920.f)*0.2f, (window.getSize().y/1080.f)*0.2f});
    auto bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.getCenter());
    sprite.setPosition(kulka.getPosition());
}

void Banan::leci(sf::RenderWindow& window) {
    wartoscY += 30;
    kulka.setPosition({wartoscY+window.getSize().x*0.5f, (1.f / 3000.f) * wartoscY * wartoscY+window.getSize().y*0.45f});
    sprite.setPosition(kulka.getPosition());
    sprite.rotate(sf::degrees(20.f));
}