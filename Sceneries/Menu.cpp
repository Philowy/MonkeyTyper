#include <iostream>
#include <filesystem>
#include <fmt/ranges.h>
#include <map>
#include <fstream>  // std::fstream
#include <SFML/Audio.hpp>

#include "Game.hpp"
#include "Menu.hpp"

#include "../Enums.hpp"

#include "../Class/Banan.hpp"
#include "../Class/Font.hpp"
#include "../Class/Text.hpp"

std::vector<Banan> banany;
std::vector<sf::Sprite> sprites;
std::map<int, sf::Texture> textures;
bool ifOnLogo = false;
bool ifOnEXIT = false;

void menuSetUp(const sf::RenderWindow& window) {

    // loading 3 DEFAULT fonts
    sf::Font font;
    if (!font.openFromFile("../fonts/centurygothic.ttf")) {
        fmt::println("File centurygothic.ttf NOT found.\n");
        fmt::println("../fonts/centurygothic.png\n");
        exit(0);
    }
    std::string fontName = "centurygothic";
    Font::fonts.push_back(Font(fontName, font));

    if (!font.openFromFile("../fonts/centurygothic_bold.ttf")) {
        fmt::println("File centurygothic_bold.ttf NOT found.\n");
        fmt::println("../fonts/centurygothic_bold.png\n");
        exit(0);
    }
    fontName = "centurygothic_bold";
    Font::fonts.push_back(Font(fontName, font));

    // loading other fonts
    // https://en.cppreference.com/w/cpp/filesystem
    for (const auto& plik : std::filesystem::directory_iterator("../fonts")) {
        if (plik.path().relative_path() == "../fonts/centurygothic.ttf" or plik.path().relative_path() == "../fonts/centurygothic_bold.ttf")
            continue;
        fontName = plik.path().stem().string();
        font = sf::Font(plik.path().relative_path());
        Font::fonts.push_back(Font(fontName, font));
    }

    //PRZYPISANIE DEFAULT CZCIONKI
    Button::defaultFont = Font::fonts[0].getFont();
    Text::font = Font::fonts[0].getFont();
    Text::fontName = Font::fonts[0].getFontName();

    Button::windowSize = sf::Vector2f(window.getSize());
    Button::skala = sf::Vector2f(window.getSize().x/1920.f, window.getSize().y/1080.f);

    Text::windowSize = sf::Vector2f(window.getSize());
    Text::skala = sf::Vector2f(window.getSize().x/1920.f, window.getSize().y/1080.f);

    Button::buttonsMenu = {
        Button("START"),
        Button("SETTINGS"),
        Button("AUTHORS"),
        Button("EXIT")
    };

    // START INNA CZCIONKA i ROZMIAR
    Button::buttonsMenu[0].changeFont(Font::fonts[1]);
    Button::buttonsMenu[0].changeTextSize(85);

    // RETURN INNA POZYCJA
    Button::buttonsMenu[3].changeButtonSize({0.7f,1.2f});

    // RÓWNE USTAWIENIE START, SETTINGS, AUTHOR
    for (int i=0; i<Button::buttonsMenu.size()-1; i++)
        Button::buttonsMenu[i].setPosition({Button::buttonsMenu[i].area.getPosition().x, float(window.getSize().y)*(i/11.f)+float(window.getSize().y)*(1/1.75f)});

    // USTAWIENIE EXIT
    Button::buttonsMenu[3].setPosition({Button::buttonsMenu[3].area.getPosition().x, float(window.getSize().y)*(3/9.f)+float(window.getSize().y)*(1/1.75f)});


    // loading words jeśli puste
    if (Text::words.empty()) {
        std::fstream file;
        file = std::fstream("../words.txt");
        if (!file) {
            fmt::println("File words.txt NOT found.\n");
            fmt::println("../words.txt\n");
            exit(0);
        }

        std::string word;

        while (file >> word) {
            Text::words.push_back(word);
        }
    }

    textures = loadTextures();

    Banan::teksturka = textures[16];

    sprites = makeSprites(window);
}

void menuMain(sf::RenderWindow& window) {

    // logoGrey z tyłu
    window.draw(sprites[0]);

    // wyświetl wszystkie buttons bez EXIT
    for (int i=0; i<Button::buttonsMenu.size()-1; i++) {
        //window.draw(Button::buttonsMenu[i].area);
        window.draw(Button::buttonsMenu[i].text);
    }

    // draw other sprites
    if (!ifOnLogo)
        window.draw(sprites[1]);
    else
        window.draw(sprites[2]);

    if (!ifOnEXIT)
        window.draw(sprites[3]);
    else
        window.draw(sprites[4]);

    if (banany.size() != 0) {
        //for (auto& banan : banany) {
        for (int i=0; i<banany.size(); i++) {
            if (banany[i].kulka.getPosition().x > window.getSize().x or banany[i].kulka.getPosition().y > window.getSize().y) {
                auto iterator = banany.begin();
                iterator += i;
                banany.erase(iterator);
            }
            else {
                banany[i].leci(window);
                window.draw(banany[i].sprite);
            }
        }
    }
}

void menuEvent(const std::optional<sf::Event>& event, Stage& gameState, sf::RenderWindow& window) {

    // mechanika przycisku START USTAWIENIA AUTHOR i EXIT
    if (auto mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            auto ifContains = [mouse](int number) {
                return Button::buttonsMenu[number].area.getGlobalBounds().contains({float(mouse->position.x), float(mouse->position.y)});
            };

            // START
            if (ifContains(0))
                gameState = PREGAME;

            // USTAWIENIA
            else if (ifContains(1))
                gameState = SETTINGS;

            // AUTHOR
            else if (ifContains(2))
                gameState = AUTHOR;

            // EXIT
            else if (ifContains(3)) {
                window.close();
            }
        }
    }


    // zmiana Logo i bananki
    auto mousePos = sf::Mouse::getPosition(window);
    if (sprites[1].getGlobalBounds().contains({float(mousePos.x), float(mousePos.y)})) {
        ifOnLogo = true;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            banany.push_back(Banan(window));
    }
    else
        ifOnLogo = false;

    // zmiana sprita EXIT
    if (sprites[3].getGlobalBounds().contains({float(mousePos.x), float(mousePos.y)}))
        ifOnEXIT = true;
    else
        ifOnEXIT = false;
}

std::vector<sf::Sprite> makeSprites (const sf::RenderWindow& window) {
    std::vector<sf::Sprite> sprites;
    sprites.push_back(makeSprite(window, textures[0], {1.2f, 1.2f}, {window.getSize().x/2.f, window.getSize().y/2.f}));
    sprites.push_back(makeSprite(window, textures[1], {1.f, 1.f},   {window.getSize().x/2.f, window.getSize().y*0.23f}));
    sprites.push_back(makeSprite(window, textures[2], {1.f, 1.f},   {window.getSize().x/2.f, window.getSize().y*0.233f}));
    sprites.push_back(makeSprite(window, textures[3], {.07f, .07f}, {window.getSize().x/2.f, window.getSize().y*0.9f}));
    sprites.push_back(makeSprite(window, textures[4], {.07f, .07f}, {window.getSize().x/2.f, window.getSize().y*0.903f}));

    //return arrow
    sprites.push_back(makeSprite(window, textures[5], {0.5f, 0.5f}, {window.getSize().x/2.f, window.getSize().y*0.91f}));
    sprites.push_back(makeSprite(window, textures[6], {0.5f, 0.5f}, {window.getSize().x/2.f, window.getSize().y*0.913f}));

    //previewBox
    sprites.push_back(makeSprite(window, textures[7], {0.29f, 0.24f}, {window.getSize().x/2.f, window.getSize().y*0.5f}));

    // preGame
    sprites.push_back(makeSprite(window, textures[8], {0.25f, 0.25f}, {window.getSize().x/2.f, window.getSize().y*0.2f}));
    sprites.push_back(makeSprite(window, textures[9], {0.25f, 0.25f}, {window.getSize().x/2.f, window.getSize().y*0.2f}));
    sprites.push_back(makeSprite(window, textures[10], {0.25f, 0.25f}, {window.getSize().x/2.f, window.getSize().y*0.45f}));
    sprites.push_back(makeSprite(window, textures[11], {0.25f, 0.25f}, {window.getSize().x/2.f, window.getSize().y*0.45f}));
    sprites.push_back(makeSprite(window, textures[12], {0.25f, 0.25f}, {window.getSize().x/2.f, window.getSize().y*0.7f}));
    sprites.push_back(makeSprite(window, textures[13], {0.25f, 0.25f}, {window.getSize().x/2.f, window.getSize().y*0.7f}));
    sprites.push_back(makeSprite(window, textures[14], {0.25f, 0.25f}, {window.getSize().x/2.f, window.getSize().y*(0.5f)}));
    sprites.push_back(makeSprite(window, textures[15], {0.25f, 0.25f}, {window.getSize().x/2.f, window.getSize().y*(0.92f)}));
    sprites.push_back(makeSprite(window, textures[16], {0.25f, 0.25f}, {window.getSize().x/2.f, window.getSize().y*(0.5f)}));
    sprites.push_back(makeSprite(window, textures[17], {0.07f, 0.07f}, {window.getSize().x/12.f, window.getSize().y*(0.07f)}));
    sprites.push_back(makeSprite(window, textures[18], {0.25f, 0.25f}, {window.getSize().x/2.f, window.getSize().y*(0.5f)}));
    return sprites;
}

sf::Sprite makeSprite (const sf::RenderWindow& window, const sf::Texture& texture, sf::Vector2f scale, sf::Vector2f position) {
    sf::Sprite sprite(texture);
    sprite.setScale({(window.getSize().x / 1920.f) * scale.x, (window.getSize().y / 1080.f) * scale.y});
    auto bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.getCenter());
    sprite.setPosition(position);
    return sprite;
};

std::map<int, sf::Texture> loadTextures () {

    std::map<int, sf::Texture> makingTextures;
    sf::Texture texture;

    std::string path;

    path = "../pngs/logoGrey.png";
    if (!texture.loadFromFile(path)) {
        fmt::println("File logoGrey.png NOT found.\n");
        fmt::println("../pngs/logoGrey.png\n");
        exit(0);
    }
    makingTextures.insert({0, texture});

    path = "../pngs/logoOutline.png";
    if (!texture.loadFromFile(path)){
        fmt::println("File logoOutline.png NOT found.\n");
        fmt::println("../pngs/logoOutline.png\n");
        exit(0);
    }
    makingTextures.insert({1, texture});

    path = "../pngs/logoOutlineHover.png";
    if (!texture.loadFromFile(path)){
        fmt::println("File logoOutlineHover.png NOT found.\n");
        fmt::println("../pngs/logoOutlineHover.png\n");
        exit(0);
    }
    makingTextures.insert({2, texture});

    path = "../pngs/exitButton.png";
    if (!texture.loadFromFile(path)){
        fmt::println("File exitButton.png NOT found.\n");
        fmt::println("../pngs/exitButton.png\n");
        exit(0);
    }
    makingTextures.insert({3, texture});

    path = "../pngs/exitButtonHover.png";
    if (!texture.loadFromFile(path)){
        fmt::println("File exitButtonHover.png NOT found.\n");
        fmt::println("../pngs/exitButtonHover.png\n");
        exit(0);
    }
    makingTextures.insert({4, texture});

    path = "../pngs/returnArrow.png";
    if (!texture.loadFromFile(path)){
        fmt::println("File returnArrow.png NOT found.\n");
        fmt::println("../pngs/returnArrow.png\n");
        exit(0);
    }
    makingTextures.insert({5, texture});

    path = "../pngs/returnArrowHover.png";
    if (!texture.loadFromFile(path)){
        fmt::println("File returnArrowHover.png NOT found.\n");
        fmt::println("../pngs/returnArrowHover.png\n");
        exit(0);
    }
    makingTextures.insert({6, texture});

    path = "../pngs/previewBox.png";
    if (!texture.loadFromFile(path)){
        fmt::println("File previewBox.png NOT found.\n");
        fmt::println("../pngs/previewBox.png\n");
        exit(0);
    }
    makingTextures.insert({7, texture});

    path = "../pngs/eazy.png";
    if (!texture.loadFromFile(path)){
        fmt::println("File eazy.png NOT found.\n");
        fmt::println("../pngs/eazy.png\n");
        exit(0);
    }
    makingTextures.insert({8, texture});

    path = "../pngs/eazyHover.png";
    if (!texture.loadFromFile(path)){
        fmt::println("File eazyHover.png NOT found.\n");
        fmt::println("../pngs/eazyHover.png\n");
        exit(0);
    }
    makingTextures.insert({9, texture});

    path = "../pngs/mid.png";
    if (!texture.loadFromFile(path)){
        fmt::println("File mid.png NOT found.\n");
        fmt::println("../pngs/mid.png\n");
        exit(0);
    }
    makingTextures.insert({10, texture});

    path = "../pngs/midHover.png";
    if (!texture.loadFromFile(path)){
        fmt::println("File midHover.png NOT found.\n");
        fmt::println("../pngs/midHover.png\n");
        exit(0);
    }
    makingTextures.insert({11, texture});

    path = "../pngs/hard.png";
    if (!texture.loadFromFile(path)){
        fmt::println("File hard.png NOT found.\n");
        fmt::println("../pngs/hard.png\n");
        exit(0);
    }
    makingTextures.insert({12, texture});

    path = "../pngs/hardHover.png";
    if (!texture.loadFromFile(path)){
        fmt::println("File hardHover.png NOT found.\n");
        fmt::println("../pngs/hardHover.png\n");
        exit(0);
    }
    makingTextures.insert({13, texture});

    path = "../pngs/frame.png";
    if (!texture.loadFromFile(path)){
        fmt::println("File frame.png NOT found.\n");
        fmt::println("../pngs/frame.png\n");
        exit(0);
    }
    makingTextures.insert({14, texture});

    path = "../pngs/writingArea.png";
    if (!texture.loadFromFile(path)){
        fmt::println("File writingArea.png NOT found.\n");
        fmt::println("../pngs/writingArea.png\n");
        exit(0);
    }
    makingTextures.insert({15, texture});

    path = "../pngs/banan.png";
    if (!texture.loadFromFile(path)) {
        fmt::println("File banana.png NOT found.\n");
        fmt::println("../pngs/banan.png\n");
        exit(0);
    }
    makingTextures.insert({16, texture});

    path = "../pngs/miniLogo.png";
    if (!texture.loadFromFile(path)) {
        fmt::println("File miniLogo.png NOT found.\n");
        fmt::println("../pngs/miniLogo.png\n");
        exit(0);
    }
    makingTextures.insert({17, texture});

    path = "../pngs/youLose.png";
    if (!texture.loadFromFile(path)) {
        fmt::println("File youLose.png NOT found.\n");
        fmt::println("../pngs/youLose.png\n");
        exit(0);
    }
    makingTextures.insert({18, texture});

    return makingTextures;
};

std::vector<sf::Sprite>& getSprites () {
    return sprites;
}