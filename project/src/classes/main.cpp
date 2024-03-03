#include <iostream>
#include <SFML/Graphics.hpp>
#include "../headers/object.h"
#include "../headers/Player.h"
#include "../headers/map.h"
#include "../headers/3dRender.h"
#include <memory>

using texture_ptr = std::unique_ptr<sf::Texture>;
using texture_ptrs = std::vector<std::unique_ptr<sf::Texture>>;
using object_ptr = std::unique_ptr<Object>;
using object_ptrs = std::vector<std::unique_ptr<Object>>;

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;


texture_ptrs LoadTextures() {
    texture_ptrs textures;
    texture_ptr playerTexture = std::make_unique<sf::Texture>();
    texture_ptr wallTexture = std::make_unique<sf::Texture>();

    playerTexture->loadFromFile("../external/direction.png");
    wallTexture->loadFromFile("../external/background1.png");

    textures.push_back(std::move(playerTexture));
    textures.push_back(std::move(wallTexture));

    return textures;
}

int main() {

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Working Title");
    texture_ptrs textures;
    std::vector<std::vector<int>> map_data;
    textures = LoadTextures();
    Map map("../external/map1.txt", "../external/config.txt",400 , 300, map_data);
    Vector2d pos;
    for(int i = 0; i < map_data.size(); i++){
        for(int j = 0; j < map_data[i].size(); j++){
            if(map_data[i][j] == 2){
                pos = Vector2d(i, j);
            }
        }
    }
    Player player(*textures[1], pos, window.getSize(), textures[1]->getSize(), map_data);
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event{};
        sf::Time dt = clock.restart();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        /*for(auto& object : objects){
            for(auto& other : objects){
                if(dynamic_cast<Wall*>(object.get()) && dynamic_cast<Player*>(other.get())){
                    object->getCollider().checkCollision(other->getCollider(), 1.0f);
                }
            }
        }*/

        player.update(dt.asSeconds());
        window.clear();
        player.Render(window);
        map.render(window);
        window.display();
    }

    return 0;
}



