#include <iostream>
#include <SFML/Graphics.hpp>
#include "../headers/object.h"
#include "../headers/Player.h"
#include "../headers/map.h"
#include <memory>


void Generate(std::string& file, sf::Color color, float Width, float Height, std::vector<std::unique_ptr<Object>>& objects) {
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
    sf::Texture texture;
    texture.loadFromFile("../external/direction.png");
    spriteRenderer sprite( texture, sf::Vector2f(100, 100), sf::Vector2f(1, 1), sf::IntRect(0, 0, 64, 64), sf::Vector2f(0, 7));
    while(std::getline(openfile, line)) {
        for(int i = 0; i < line.size(); i++) {
            if(line[i] == '#') {
                objects.push_back(std::make_unique<Wall>(Wall(sf::Vector2f(width, height), sf::Vector2f(width * i + width / 2, height * row + height / 2), color)));
            } else if(line[i] == 'P') {
                if(player == 0) {
                    player = 1;
                    objects.push_back(std::make_unique<Player>(Player(sprite, sf::Vector2f(30, 40), sf::Vector2f(width * i + width / 2, height * row + height / 2), sf::Color::Red)));
                }
            }
        }
        row++;
    }
}

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Working Title");
    std::vector<std::unique_ptr<Object>> objects;
    std::string map = "../external/map1.txt";
    Generate(map, sf::Color::Blue,800, 600, objects);
    sf::Texture texture;
    texture.loadFromFile("../external/player.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sf::IntRect rectSourceSprite(0, 0, 100, 100);
    sprite.setTextureRect(rectSourceSprite);

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
        window.draw(sprite);
        window.display();
    }

    return 0;
}

