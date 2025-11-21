#include "Settings.hpp"
#include "Menu.hpp"
#include "../Enums.hpp"
#include "../Class/Font.hpp"
#include "../Class/Button.hpp"
#include "../Class/Text.hpp"
#include "fmt/color.h"

std::vector<sf::RectangleShape> invisibleRectangles;
std::vector<sf::Text> texts;
std::vector<sf::Sprite> spritesSettings;
bool ifOnRETURN = false;
int justSomeRandomNumber = 0; // do odstępów w generowaniu słów
int generated = rand()%100;

void settingsSetUp(sf::RenderWindow& window){
    Text::generatedTexts.clear();

    spritesSettings = getSprites();
    spritesSettings[0].setPosition({window.getSize().x*0.22f, window.getSize().y/2.f});
    spritesSettings[0].setScale({window.getSize().x/1920*0.95f, window.getSize().y/1080*0.95f});


    // making a few invisible rectangles for eazier centernig and moving
    sf::RectangleShape invisibleMainRectangle = sf::RectangleShape({float(window.getSize().x), window.getSize().y*(3.6f/5.f)});
    auto bounds = invisibleMainRectangle.getGlobalBounds();
    invisibleMainRectangle.setOrigin(bounds.getCenter());
    invisibleMainRectangle.setPosition({window.getSize().x/2.f, window.getSize().y/2.f-window.getSize().y*(1.f/30.f)});
    invisibleRectangles.push_back(invisibleMainRectangle);

    sf::RectangleShape invisibleLeftRectangle = sf::RectangleShape({invisibleMainRectangle.getSize().x*(1.8f/5.f), invisibleMainRectangle.getSize().y});
    bounds = invisibleLeftRectangle.getGlobalBounds();
    invisibleLeftRectangle.setOrigin(bounds.getCenter());
    invisibleLeftRectangle.setPosition({invisibleMainRectangle.getGeometricCenter().x-invisibleMainRectangle.getGeometricCenter().x+invisibleLeftRectangle.getSize().x/2.f, window.getSize().y/2.f-window.getSize().y*(1.f/30.f)});
    invisibleLeftRectangle.setFillColor(sf::Color::Cyan);
    invisibleRectangles.push_back(invisibleLeftRectangle);

    sf::RectangleShape invisibleRightRectangle = sf::RectangleShape({invisibleMainRectangle.getSize().x*(2.8f/5.f), invisibleMainRectangle.getSize().y});
    bounds = invisibleRightRectangle.getGlobalBounds();
    invisibleRightRectangle.setOrigin(bounds.getCenter());
    invisibleRightRectangle.setPosition({invisibleMainRectangle.getGeometricCenter().x+invisibleMainRectangle.getGeometricCenter().x-invisibleRightRectangle.getSize().x/2.f, window.getSize().y/2.f-window.getSize().y*(1.f/30.f)});
    invisibleRightRectangle.setFillColor(sf::Color::Red);
    invisibleRectangles.push_back(invisibleRightRectangle);


    // creating texsts like: FONT STYLE, FONT SIZE, PREVIEW
    sf::Text textFONTSTYLE = sf::Text(Button::defaultFont, "FONT STYLE:", 70);
    bounds = textFONTSTYLE.getGlobalBounds();
    textFONTSTYLE.setOrigin(bounds.getCenter());
    textFONTSTYLE.setPosition({invisibleLeftRectangle.getPosition().x, invisibleLeftRectangle.getPosition().y*(5.f/9.f)});
    textFONTSTYLE.setFillColor(sf::Color(65,157,229));
    texts.push_back(textFONTSTYLE);

    sf::Text textFONTSIZE = sf::Text(Button::defaultFont, "FONT SIZE:", 70);
    bounds = textFONTSIZE.getGlobalBounds();
    textFONTSIZE.setOrigin(bounds.getCenter());
    textFONTSIZE.setPosition({invisibleLeftRectangle.getPosition().x, invisibleLeftRectangle.getPosition().y*(13.f/9.f)});
    textFONTSIZE.setFillColor(sf::Color(65,157,229));
    texts.push_back(textFONTSIZE);

    sf::Text textPREVIEW = sf::Text(Button::defaultFont, "PREVIEW:", 70);
    bounds = textPREVIEW.getGlobalBounds();
    textPREVIEW.setOrigin(bounds.getCenter());
    textPREVIEW.setPosition({invisibleRightRectangle.getPosition().x*(9.5f/10.f), invisibleRightRectangle.getPosition().y*(4.f/9.f)});
    textPREVIEW.setFillColor(sf::Color(65,157,229));
    texts.push_back(textPREVIEW);

    spritesSettings[7].setPosition({texts[2].getPosition().x, texts[2].getPosition().y*(2.4f)});


    // making buttons
    Button::buttonsSettings.push_back(Button("Return"));
    Button::buttonsSettings[0].setPosition({window.getSize().x/2.f, window.getSize().y*(8.2f/9.f)});
    Button::buttonsSettings[0].changeButtonSize({0.35f, 1.24f});

    // BUTTON 4 rozmiary czcionki
    for (int i = 1; i <= 4; i++) {
        Button::buttonsSettings.push_back(Button(std::to_string(18+8*i)));
        Button::buttonsSettings[i].changeButtonSize({0.26f, 0.8f});
        Button::buttonsSettings[i].setPosition({texts[1].getPosition().x + (i-1)*Button::buttonsSettings[i].area.getSize().y*(0.91f) - 1.5f*Button::buttonsSettings[i].area.getSize().y*(0.9f), texts[1].getPosition().y + texts[1].getPosition().y*0.12f});
        Button::buttonsSettings[i].changeTextSize(18+8*i);
        Button::buttonsSettings[i].area.setFillColor(sf::Color::White);
        Button::buttonsSettings[i].setSecondColor(sf::Color(65,157,229));
    }

    // BUTTON n stylów czcionki
    for (int i = 5; i <= Font::fonts.size()+4; i++) {
        Button::buttonsSettings.push_back(Button(Font::fonts[i-5].getFontName()));
        Button::buttonsSettings[i].changeButtonSize({1.85f, 0.5f});
        Button::buttonsSettings[i].changeFont(Font::fonts[i-5]);
        Button::buttonsSettings[i].setPosition({texts[0].getPosition().x, texts[0].getPosition().y + (i-5)*texts[0].getPosition().y*0.18f + texts[0].getPosition().y*0.25f});
        Button::buttonsSettings[i].area.setFillColor(sf::Color::White);
        Button::buttonsSettings[i].setSecondColor(sf::Color(65,157,229));
    }

    int characterSize = Button::lowestCharakterSize(Button::buttonsSettings);

    for (int i = 5; i <= Font::fonts.size()+4; i++)
        Button::buttonsSettings[i].changeTextSize(characterSize);

    Text::upperLeftCorner = {window.getSize().x*(.45f), window.getSize().y*(.25f)};
    Text::lowerRightCorner = {window.getSize().x*(.93f), window.getSize().y*(.77f)};

    Text::fontName = "centurygothic";
}

void settingsMain(sf::RenderWindow& window) {
    window.draw(spritesSettings[0]);

    // wyświetl wszystkie invisibleRectangles
    /*for (auto& rectangle : invisibleRectangles)
        window.draw(rectangle);*/

    auto iterator = Text::generatedTexts.begin();
    for (int i = 0; i < Text::generatedTexts.size(); i++){
        if (Text::generatedTexts[i].reference.getPosition().x + Text::generatedTexts[i].reference.getSize().x >= Text::lowerRightCorner.x) {
            Text::generatedTexts.erase(iterator);
            i--;
        }
        iterator++;
    }

    // wyświetl wszystkie buttons (oprócz return)
    for (int i = 1; i < Button::buttonsSettings.size(); i++) {
        //window.draw(Button::buttonsSettings[i].area);
        window.draw(Button::buttonsSettings[i].text);
    }

    //wyświetl wszystkie texts
    for (auto& text : texts)
        window.draw(text);

    auto mousePos = sf::Mouse::getPosition(window);
    // draw other sprites
    if (!spritesSettings[5].getGlobalBounds().contains({float(mousePos.x), float(mousePos.y)}))
        window.draw(spritesSettings[5]);
    else
        window.draw(spritesSettings[6]);

    window.draw(spritesSettings[7]);

    if (justSomeRandomNumber++ > generated) {
        Text::generatedTexts.push_back(Text());
        generated = rand()%(Text::generationSpeed)+50;
        justSomeRandomNumber = 0;
    }

    //Text::generatedTexts[0].vectorMove(1);
    for (int i = 0; i < Text::generatedTexts.size(); i++)
        Text::generatedTexts[i].textMove();

    // wyświetl tekst w preview
    if (Text::generatedTexts.size() != 0)
        for (auto text : Text::generatedTexts) {
            //window.draw(text.reference);
            for (auto letter : text.vectorText)
                window.draw(letter);
        }
}

void settingsEvent(const std::optional<sf::Event>& event, Stage& gameState, sf::RenderWindow& window) {

    // mechanika przycisku RETURN I CZCIONEK
    if (auto mouse = event->getIf<sf::Event::MouseButtonPressed>()) {

        auto ifContains = [mouse](int number) {
            return Button::buttonsSettings[number].area.getGlobalBounds().contains({float(mouse->position.x), float(mouse->position.y)});
        };

        // RETURN
        if (ifContains(0)) {
            Text::generatedTexts.clear();
            gameState = MENU;
        }

        // wielkości czcionek
        for (int i = 1; i < 5; i++)
            if (ifContains(i))
                // https://en.cppreference.com/w/cpp/string/basic_string/stol
                // https://www.sfml-dev.org/documentation/3.0.0/classsf_1_1String.html#a12d6659486d24cf323b4cb70533e5d38
                Text::charakterSize = std::stoi(Button::buttonsSettings[i].text.getString().toAnsiString());

        // wybór czcionek
        for (int i = 5; i < Font::fonts.size()+5; i++)
            if (ifContains(i)) {
                Text::font = Font::fonts[i-5].getFont();
                Text::fontName = Font::fonts[i-5].getFontName();
            }
    }
}