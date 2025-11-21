#include "Game.hpp"
#include "Menu.hpp"
#include "../Class/Text.hpp"
#include "../Class/Font.hpp"
#include "fmt/compile.h"

std::vector<sf::Sprite> spritesGame;
std::vector<sf::Sprite> spritesLives;
sf::Text showDifficulty(Button::defaultFont, "HARD");
sf::Text points(Button::defaultFont, "0");
int pointsNumber = 0;
int lives = 3;
int randomNumber = 0; // do odstępów w generowaniu słów
int generatedNumberGame = rand()%100;
bool ifLoose = false;
auto enteredWord = std::string(); // wprowadzany w grze przez użytkownika czyszczony gdy naciśnie enter
auto enteredText = sf::Text(Text::font, "", 25);

void gameSetUp(sf::RenderWindow& window) {
    enteredText.setCharacterSize(60);
    spritesGame = getSprites();
    Text::generatedTexts.clear();
    showDifficulty.setCharacterSize(70);
    showDifficulty.setFillColor(sf::Color(65,157,229));

    points.setCharacterSize(70);
    points.setFillColor(sf::Color(65,157,229));
    points.setPosition({window.getSize().x*0.5f, window.getSize().y*(0.02f)});

    auto bounds = showDifficulty.getGlobalBounds();
    showDifficulty.setOrigin(bounds.getCenter());
    showDifficulty.setPosition({window.getSize().x*0.925f, window.getSize().y*(0.02f)});

    //setup EXIT
    spritesGame[3].setPosition({window.getSize().x*0.075f, window.getSize().y*(0.92f)});
    spritesGame[4].setPosition({window.getSize().x*0.075f, window.getSize().y*(0.923f)});

    // setup Lives
    for (int i = 0; i < lives; i++) {
        spritesLives.push_back(sf::Sprite(spritesGame[16]));
        spritesLives[i].setPosition({window.getSize().x*0.925f, window.getSize().y*(0.5f+0.12f*(i-1))});
        spritesLives[i].setScale({0.43f, 0.43f});
    }
}

void gameMain(sf::RenderWindow& window, Difficulty& difficulty, Stage& gameState) {
    if (ifLoose) {
        window.draw(spritesGame[18]);
        // EXIT button
        auto mousePos = sf::Mouse::getPosition(window);
        if (spritesGame[3].getGlobalBounds().contains({float(mousePos.x), float(mousePos.y)}))
            window.draw(spritesGame[4]);
        else window.draw(spritesGame[3]);

        return;
    }

    switch (difficulty) {
        case EASY:
            showDifficulty.setString("EASY");
            showDifficulty.setPosition({window.getSize().x*0.93f, window.getSize().y*(0.07f)});
            break;
        case MEDIUM:
            showDifficulty.setString("MID");
            showDifficulty.setPosition({window.getSize().x*0.94f, window.getSize().y*(0.07f)});
            break;
        case HARD:
            showDifficulty.setString("HARD");
            showDifficulty.setPosition({window.getSize().x*0.925f, window.getSize().y*(0.07f)});
            break;
    }

    auto iterator = Text::generatedTexts.begin();
    for (int i = 0; i < Text::generatedTexts.size(); i++){
        if (Text::generatedTexts[i].reference.getPosition().x + Text::generatedTexts[i].reference.getSize().x >= window.getSize().x*(.85f)) {
            Text::generatedTexts.erase(iterator);
            i--;
            lives--;
            if (lives <= 0) {
                ifLoose = true;
                return;
            }
        }
        iterator++;
    }

    if (randomNumber++ > generatedNumberGame) {
        Text::generatedTexts.push_back(Text());
        generatedNumberGame = rand()%50+Text::generationSpeed;
        randomNumber = 0;
    }

    for (int i = 0; i < Text::generatedTexts.size(); i++)
        Text::generatedTexts[i].textMove();

    // wyświetl tekst
    if (Text::generatedTexts.size() != 0)
        for (auto text : Text::generatedTexts)
            //window.draw(text.reference);
            for (auto letter : text.vectorText)
                window.draw(letter);

    // ramka
    window.draw(spritesGame[14]);
    // pole do pisania
    window.draw(spritesGame[15]);
    // miniLogo
    window.draw(spritesGame[17]);
    window.draw(showDifficulty);
    window.draw(points);
    window.draw(enteredText);

    // kolorowanie textu
    for (auto& generatedText : Text::generatedTexts) {
        if (enteredWord.size() == 0) {
            for (auto& letter : generatedText.vectorText)
                letter.setFillColor(sf::Color(50,52,55));
            continue;
        }
        auto ifCorrect = true;

        for (int i = 0; i < enteredWord.size(); i++) {
            if (generatedText.vectorText[i].getString() != enteredWord[i])
                ifCorrect = false;
        }

        if (ifCorrect) {
            for (int i = 0; i < generatedText.vectorText.size(); i++) {
                if (i < enteredWord.size()) {
                    generatedText.vectorText[i].setFillColor(sf::Color(255,255,255));
                }
                else
                    generatedText.vectorText[i].setFillColor(sf::Color(25,52,55));
            }
        }
        else {
            for (auto& letter : generatedText.vectorText)
             letter.setFillColor(sf::Color(50,52,55));
        }
    }

    // EXIT button
    {
        auto mousePos = sf::Mouse::getPosition(window);
        if (spritesGame[3].getGlobalBounds().contains({float(mousePos.x), float(mousePos.y)}))
            window.draw(spritesGame[4]);
        else
            window.draw(spritesGame[3]);
    }

    bool ifFound = false;
    iterator = Text::generatedTexts.begin();
    for (int i = 0; i < Text::generatedTexts.size(); i++) {
        if (!ifFound) {
            // check if word is entered
            if (enteredWord == Text::generatedTexts[i].word) {
                pointsNumber++;
                points.setString(std::to_string(pointsNumber));
                Text::generatedTexts.erase(iterator);
                enteredWord = "";
                enteredText.setString("");
                ifFound = true;
            }
            iterator++;
        }
    }

    // for (auto live : spritesLives)
    for (int i = 0; i < lives; i++)
        window.draw(spritesLives[i]);
}

void gameEvent(const std::optional<sf::Event>& event, Stage& gameState, sf::RenderWindow& window) {
    if (auto mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
        auto ifContains = [mouse](int number) {
            return spritesGame[number].getGlobalBounds().contains({float(mouse->position.x), float(mouse->position.y)});
        };

        // EXIT
        if (ifContains(3)) {
            Text::generatedTexts.clear();
            gameState = MENU;
            pointsNumber = 0;
            points.setString("0");
            enteredWord = "";
            enteredText.setString("");
            //ustawienie pozycji renderowanie słów
            Text::upperLeftCorner = {window.getSize().x*(.42f), window.getSize().y*(.25f)};
            Text::lowerRightCorner = {window.getSize().x*(.95f), window.getSize().y*(.77f)};
            ifLoose = false;
        }
    }

    if (auto key = event->getIf<sf::Event::KeyPressed>()) {
        // wprowadzanie liter do wprowadzonyWyraz
        if (int(key->code)>=0 and int(key->code)<=25) {
            if (enteredWord.size() > 20) {
                enteredWord = "";
                enteredText.setString("");
            }
            enteredWord += char(int(key->code)+97);
            enteredText.setString(enteredWord);
            auto bounds = enteredText.getLocalBounds();
            enteredText.setOrigin({bounds.getCenter().x,bounds.getCenter().y});
            enteredText.setPosition({window.getSize().x * (.5f), window.getSize().y * (.918f)});
        }

        // usuwanie liter
        if (enteredWord.size() > 0 and key->scancode == sf::Keyboard::Scancode::Backspace) {
            enteredWord.pop_back();
            enteredText.setString(enteredWord);
            auto bounds = enteredText.getLocalBounds();
            enteredText.setOrigin({bounds.getCenter().x,bounds.getCenter().y});
        }
    }
}

int& getLives() {
    return lives;
}

int& getPointsNumber() {
    return pointsNumber;
}

