#include <SFML/Graphics.hpp>
#include <fmt/ranges.h>

#include "Class/Button.hpp"

#include "Enums.hpp"
#include "Class/Text.hpp"

#include "Sceneries/Menu.hpp"
#include "Sceneries/PreGame.hpp"
#include "Sceneries/Game.hpp"
#include "Sceneries/Settings.hpp"
#include "Sceneries/Author.hpp"

auto main() -> int {

    auto window = sf::RenderWindow(
        // deafult: 1920, 1080
        sf::VideoMode({1920, 1080}), "Monkey typer",
        sf::Style::Default,
        sf::State::Fullscreen,
        //sf::State::Windowed,
        sf::ContextSettings{.antiAliasingLevel = 8}
        );

    window.setFramerateLimit(60);

    menuSetUp(window);
    preGameSetUp(window);
    settingsSetUp(window);
    gameSetUp(window);
    authorSetUp(window);

    auto gameState = MENU;
    auto difficulty = EASY;

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            // shortcuts
            if (auto key = event->getIf<sf::Event::KeyPressed>()) {
                int iterator = 0;

                for (int i = 0; i < Font::fonts.size(); i++) {
                    if (Font::fonts[i].getFontName() == Text::fontName) {
                        iterator += i;
                    }
                }

                // change font
                if (key->scancode == sf::Keyboard::Scan::Right) {
                    if (iterator == Font::fonts.size()-1) {
                        Text::font = Font::fonts[0].getFont();
                        Text::fontName = Font::fonts[0].getFontName();
                    }
                    else {
                        iterator++;
                        Text::font = Font::fonts[iterator].getFont();
                        Text::fontName = Font::fonts[iterator].getFontName();
                    }
                }

                if (key->scancode == sf::Keyboard::Scan::Left) {
                    if (iterator == 0) {
                        Text::font = Font::fonts[Font::fonts.size()-1].getFont();
                        Text::fontName = Font::fonts[Font::fonts.size()-1].getFontName();
                    }
                    else {
                        iterator--;
                        Text::font = Font::fonts[iterator].getFont();
                        Text::fontName = Font::fonts[iterator].getFontName();
                    }
                }

                //chrakterSize
                if (key->scancode == sf::Keyboard::Scan::Up)
                    if (Text::charakterSize != 50)
                        Text::charakterSize += 8;

                if (key->scancode == sf::Keyboard::Scan::Down)
                    if (Text::charakterSize != 26)
                        Text::charakterSize -= 8;
            }

            switch (gameState) {
                case 0: menuEvent(event, gameState, window); break;
                case 1: preGameEvent(gameState, event, window, difficulty); break;
                case 2: gameEvent(event, gameState, window); break;
                case 3: settingsEvent(event, gameState, window); break;
                case 4: authorEvent(event, gameState); break;
            }

            // gives different lighting when the mouse hovers
            Button::backlightArea(sf::Mouse::getPosition(window));
        }

        switch (gameState) {
            case 0: menuMain(window); break;
            case 1: preGameMain(window); break;
            case 2: gameMain(window, difficulty, gameState); break;
            case 3: settingsMain(window); break;
            case 4: authorMain(window); break;
        }

        window.display();

        if (gameState != GAME)
            window.clear(sf::Color(50,52,55));
        else
            window.clear(sf::Color(65,157,229));
    }
}