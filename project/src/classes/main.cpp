#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window.hpp>
#include "../headers/Player.h"
#include "../headers/map.h"
#include "../headers/button.h"
#include <memory>

using texture_ptr = std::unique_ptr<sf::Texture>;
using texture_ptrs = std::vector<std::unique_ptr<sf::Texture>>;


constexpr int WIDTH = 1200;
constexpr int HEIGHT = 900;


texture_ptrs LoadTextures() {
    texture_ptrs textures;
    texture_ptr playerTexture = std::make_unique<sf::Texture>();
    texture_ptr buttonTexture = std::make_unique<sf::Texture>();
    texture_ptr wallTexture2 = std::make_unique<sf::Texture>();


    playerTexture->loadFromFile("../external/direction.png");
    buttonTexture->loadFromFile("../external/button.png");
    wallTexture2->loadFromFile("../external/wall.png");

    textures.push_back(std::move(playerTexture));
    textures.push_back(std::move(buttonTexture));
    textures.push_back(std::move(wallTexture2));
    return textures;
}

int main() {

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Working Title");
    texture_ptrs textures;
    std::vector<std::vector<int>> map_data;
    textures = LoadTextures();
    Map map("../external/map1.txt", "../external/config.txt",300 , 200, map_data);
    Vector2d pos;
    for(int i = 0; i < map_data.size(); i++){
        for(int j = 0; j < map_data[i].size(); j++){
            if(map_data[i][j] == 2){
                pos = Vector2d(i, j);
            }
        }
    }
    sf::Font font;
    font.loadFromFile("../external/advanced_pixel-7.ttf");
    Player player(*textures[2], pos, sf::Vector2i(WIDTH, HEIGHT), sf::Vector2u(64,64), map_data);
    Button resume(sf::Vector2f(600, 400), sf::Vector2f(200, 100), *textures[1], sf::Vector2f(1, 1), "Resume", font, sf::Color::Black);
    Button quit(sf::Vector2f(600, 600), sf::Vector2f(200, 100), *textures[1], sf::Vector2f(1, 1), "Quit", font, sf::Color::Black);
    sf::Clock clock;
    bool isPaused = false;

    while (window.isOpen()) {
        sf::Event event{};
        sf::Time dt = clock.restart();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            isPaused = true;
        }
        if(!isPaused){
            player.update(dt.asSeconds());
            window.setMouseCursorVisible(false);
            window.clear();
            player.Render(window);
            map.render(window);
        } else {
            window.setMouseCursorVisible(true);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(resume.isClicked(sf::Mouse::getPosition(window)))        isPaused = false;
                else if(quit.isClicked(sf::Mouse::getPosition(window)))     window.close();

            }
            window.clear();
            player.Render(window);
            resume.Render(window);
            quit.Render(window);
        }
        window.display();

    }

    return 0;
}



