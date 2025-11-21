#include "Author.hpp"
#include "Menu.hpp"
#include "../Class/Font.hpp"
#include "../Enums.hpp"

#include "SFML/Graphics.hpp"

std::vector<sf::Sprite> spritesAuthor;
std::vector<sf::Text> authors;

void authorSetUp(sf::RenderWindow& window) {
    spritesAuthor = getSprites();

    auto title = sf::Text(Font::fonts[1].getFont(), "AUTHORS", 140);
    auto bounds = title.getLocalBounds();
    title.setOrigin(bounds.getCenter());
    title.setPosition({window.getSize().x*0.5f, window.getSize().y*(0.2f)});
    title.setFillColor(sf::Color(65,157,229));
    authors.push_back(title);

    auto leadDeveloper = sf::Text(Font::fonts[0].getFont(), L"LEAD DEVELOPER", 50);
    bounds = leadDeveloper.getLocalBounds();
    leadDeveloper.setOrigin(bounds.getCenter());
    leadDeveloper.setPosition({window.getSize().x*0.5f, window.getSize().y*(0.34f)});
    authors.push_back(leadDeveloper);

    auto daniel = sf::Text(Font::fonts[0].getFont(), L"Daniel Mrówczyński s33737", 35);
    bounds = daniel.getLocalBounds();
    daniel.setOrigin(bounds.getCenter());
    daniel.setPosition({window.getSize().x*0.5f, window.getSize().y*(0.4f)});
    authors.push_back(daniel);

    auto graphicalArtists = sf::Text(Font::fonts[0].getFont(), L"GRAPHIC DESIGNERS", 50);
    bounds = graphicalArtists.getLocalBounds();
    graphicalArtists.setOrigin(bounds.getCenter());
    graphicalArtists.setPosition({window.getSize().x*0.5f, window.getSize().y*(0.55f)});
    authors.push_back(graphicalArtists);

    auto mateusz = sf::Text(Font::fonts[0].getFont(), L"Mateusz Nowak", 35);
    bounds = mateusz.getLocalBounds();
    mateusz.setOrigin(bounds.getCenter());
    mateusz.setPosition({window.getSize().x*0.5f, window.getSize().y*(0.65f)});
    authors.push_back(mateusz);

    auto piotr = sf::Text(Font::fonts[0].getFont(), L"Piotr Machel", 35);
    bounds = piotr.getLocalBounds();
    piotr.setOrigin(bounds.getCenter());
    piotr.setPosition({window.getSize().x*0.5f, window.getSize().y*(0.61f)});
    authors.push_back(piotr);
}

void authorMain(sf::RenderWindow& window) {
    window.draw(spritesAuthor[0]);

    for (auto text : authors)
        window.draw(text);

    auto mousePos = sf::Mouse::getPosition(window);
    // draw other sprites
    if (!spritesAuthor[5].getGlobalBounds().contains({float(mousePos.x), float(mousePos.y)}))
        window.draw(spritesAuthor[5]);
    else
        window.draw(spritesAuthor[6]);
}

void authorEvent(const std::optional<sf::Event>& event, Stage& gameState) {
    if (auto mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
        auto ifContains = [mouse](int number) {
            return spritesAuthor[number].getGlobalBounds().contains({float(mouse->position.x), float(mouse->position.y)});
        };

        // RETURN
        if (ifContains(0))
            gameState = MENU;
    }
}