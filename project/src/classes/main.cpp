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
    while(std::getline(openfile, line)) {
        for(int i = 0; i < line.size(); i++) {
            if(line[i] == '#') {
                objects.push_back(std::make_unique<Wall>(Wall(sf::Vector2f(width, height), sf::Vector2f(width * i + width / 2, height * row + height / 2), color)));
            } else if(line[i] == 'P') {
                if(player == 0) {
                    player = 1;
                    objects.push_back(std::make_unique<Player>(Player(sf::Vector2f(30, 20), sf::Vector2f(width * i + width / 2, height * row + height / 2), sf::Color::Red)));
                }
            }
        }
        row++;
    }
}

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Demonstration");
    std::vector<std::unique_ptr<Object>> objects;
    std::string map = "../external/map1.txt";
    Generate(map, sf::Color::White,800, 600, objects);
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
                if(object != other && !dynamic_cast<Player*>(object.get())){
                    object->getCollider().checkCollision(other->getCollider(), 1.0f);
                    //TODO: wall collisions
                }
            }
        }

        window.clear();

        for(auto &object : objects) object->Render(window);
        window.display();
    }

    return 0;
}

