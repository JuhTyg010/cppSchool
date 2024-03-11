#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window.hpp>
#include "../headers/Player.h"
#include "../headers/map.h"
#include "../headers/button.h"
#include <memory>
#include <algorithm>



constexpr int WIDTH = 1200;
constexpr int HEIGHT = 900;



std::vector<Texture> LoadTextures(std::string& extPath) {
    std::vector<Texture> textures;
    textures.push_back(Texture("player", extPath + "direction.png", sf::Vector2u(64, 64), sf::Vector2u(1, 1)));
    textures.push_back(Texture("button", extPath + "button.png", sf::Vector2u(128, 64), sf::Vector2u(1, 1)));
    textures.push_back(Texture("wall", extPath + "wall.png", sf::Vector2u(64, 64), sf::Vector2u(1, 1)));

    return textures;
}

int main() {
    std::string extPath = getExternalPath();
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Working Title");
    std::vector<Texture> textures;
    std::vector<std::vector<int>> map_data;
    textures = LoadTextures(extPath);
    Map map(extPath + "map1.txt", extPath + "config.txt",300 , 200, map_data);
    Vector2d pos;
    /*if(auto result = std::find_if(map_data.begin(), map_data.end(),
                                  [](std::vector<int> a) {return (std::find(a.begin(), a.end(), 2)) == a.end()})){


    }*/
    for(int i = 0; i < map_data.size(); i++){
        for(int j = 0; j < map_data[i].size(); j++){
            if(map_data[i][j] == 2){
                pos = Vector2d(i, j);
            }
        }
    }
    sf::Font font;
    font.loadFromFile(extPath + "advanced_pixel-7.ttf");
    auto it = std::find_if(textures.begin(), textures.end(), [&](const Texture& s){return s.getName() == "wall";});
    Player player(*it, pos, sf::Vector2i(WIDTH, HEIGHT), map_data);
    sf::RectangleShape sky(sf::Vector2f(WIDTH, HEIGHT / 2));
    sky.setFillColor(sf::Color::Cyan);
    sky.setPosition(0, 0);

    it = std::find_if(textures.begin(), textures.end(), [&](const Texture& s){return s.getName() == "button";});

    Button resume(sf::Vector2f(600, 400), Vector2d(200, 100), *it, "Resume", font, sf::Color::Black);
    
    Button quit(sf::Vector2f(600, 600), Vector2d(200, 100), *it, "Quit", font, sf::Color::Black);

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
            window.draw(sky);
            player.Render(window);
            map.render(window);
        } else {
            window.setMouseCursorVisible(true);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(resume.isClicked(sf::Mouse::getPosition(window)))        isPaused = false;
                else if(quit.isClicked(sf::Mouse::getPosition(window)))     window.close();
            }
            window.clear();
            window.draw(sky);
            player.Render(window);
            resume.Render(window);
            quit.Render(window);
        }
        window.display();

    }

    return 0;
}



