#include <iostream>
#include <SFML/Graphics.hpp>
#include "../headers/object.h"
#include "../headers/Player.h"
#include "../headers/map.h"
#include <memory>

using texture_ptr = std::unique_ptr<sf::Texture>;
using texture_ptrs = std::vector<std::unique_ptr<sf::Texture>>;
using object_ptr = std::unique_ptr<Object>;
using object_ptrs = std::vector<std::unique_ptr<Object>>;

texture_ptrs LoadTextures() {
    texture_ptrs textures;
    texture_ptr playerTexture = std::make_unique<sf::Texture>();

    playerTexture->loadFromFile("../external/direction.png");
    textures.push_back(std::move(playerTexture));

    return textures;
}

void Generate(std::string& file, sf::Color color, float Width, float Height, object_ptrs& objects,const texture_ptrs& textures) {
    std::ifstream openfile(file);

    std::string line;
    std::getline(openfile, line);
    float width;
    float height;
    std::stringstream ss(line);
    ss  >> width >> height;
    width = Width / width;
    height = Height / height;
    int row = 0;
    int player = 0;
    while(std::getline(openfile, line)) {
        for(int i = 0; i < line.size(); i++) {
            sf::Vector2f position(width * (float) i + width / 2, height * (float) row + height / 2);
            if(line[i] == '#') {
                objects.push_back(std::make_unique<Wall>(Wall(sf::Vector2f(width, height), position, color)));
            } else if(line[i] == 'P') {
                if(player == 0) {
                    player = 1;
                    objects.push_back(std::make_unique<Player>(Player(*textures[0],position, sf::Vector2f (.5,.5),
                                                                      sf::Vector2f(64, 64),sf::Vector2f(7,0))));
                }
            }
        }
        row++;
    }
}

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Working Title");
    object_ptrs objects;
    std::string map = "../external/map1.txt";
    std::vector<std::unique_ptr<sf::Texture>> textures;
    textures = LoadTextures();
    Generate(map, sf::Color::Blue,800, 600, objects, textures);


    //Player player(sf::Vector2f(60, 50), sf::Vector2f(400, 300));

    //objects.push_back(std::make_shared<Player>(player));
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event{};
        sf::Time dt = clock.restart();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for(auto& object : objects) {
            object->update(dt.asSeconds());
        }

        for(auto& object : objects){
            for(auto& other : objects){
                if(dynamic_cast<Wall*>(object.get()) && dynamic_cast<Player*>(other.get())){
                    object->getCollider().checkCollision(other->getCollider(), 1.0f);
                }
            }
        }

        window.clear();

        for(auto &object : objects) object->Render(window);
        window.display();
    }

    return 0;
}



