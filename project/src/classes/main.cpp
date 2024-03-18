#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window.hpp>
#include "../headers/Player.h"
#include "../headers/map.h"
#include "../headers/button.h"
#include "../headers/Item.h"
#include <memory>
#include <algorithm>

using texture_ptr = std::unique_ptr<sf::Texture>;
using texture_ptrs = std::vector<std::unique_ptr<sf::Texture>>;


constexpr int WIDTH = 900;
constexpr int HEIGHT = 600;
constexpr int BUTTON_TEXTURE = 1;
constexpr int WALL_TEXTURE = 2;


std::vector<Texture> LoadTextures(std::string& extPath) {
    std::vector<Texture> textures;

    textures.emplace_back("player", extPath + "direction.png", sf::Vector2f(64, 64), sf::Vector2f(1, 1));
    textures.emplace_back("button", extPath + "button.png", sf::Vector2f(128, 64), sf::Vector2f(1, 1));
    textures.emplace_back("wall", extPath + "wall.png", sf::Vector2f(64, 64), sf::Vector2f(1, 1));

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
                                  [](std::vector<int> a) {return std::find(a.begin(), a.end(), 2) == a.end(); }); result == map_data.end()){
        pos = Vector2d(map_data.end()-result, std::find (result->begin(), result->end(), 2) - result->begin());

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
    sf::Mouse::setPosition(sf::Vector2i(WIDTH/2, HEIGHT/2), window);

    auto playerTex = getTextureByName("wall", textures);
    auto itemTex = getTextureByName("wall", textures);
    Item item(itemTex, sf::Vector2f(64, 64), sf::Vector2f(1, 1));

    Player player(playerTex, pos, sf::Vector2i(WIDTH, HEIGHT), sf::Vector2u(64,64), map_data, item);
    std::cout << "Player position: " << std::endl;
    sf::RectangleShape sky(sf::Vector2f(WIDTH, HEIGHT / 2));
    sky.setFillColor(sf::Color::Cyan);
    sky.setPosition(0, 0);


    auto buttonTex = getTextureByName("button", textures);
    Button resume(buttonTex, sf::Vector2f(WIDTH/2, HEIGHT/2 -100), sf::Vector2f(200, 100), "Resume", font, sf::Color::Black);
    Button quit(buttonTex, sf::Vector2f(WIDTH/2, HEIGHT/2+100), sf::Vector2f(200, 100), "Quit", font, sf::Color::Black);

    spriteRenderer renderer(playerTex, sf::Vector2f(WIDTH/2, HEIGHT/2), sf::Vector2f(64, 64));
    sf::Clock clock;
    bool isPaused = false;
    int m=0;

    std::cout << "here" << std::endl;
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
            player.Update(dt.asSeconds());
            window.setMouseCursorVisible(false);
            window.clear();
            window.draw(sky);
            player.Render(window);
            sf::Mouse::setPosition(sf::Vector2i(WIDTH/2, HEIGHT/2), window);
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G)){

            renderer.setTextureRect(sf::IntRect(m++, 0, 1, 64));
        }

        //renderer.Render(window);
        window.display();

    }

    return 0;
}



