#include <iostream>
#include <SFML/Graphics.hpp>
#include "object.h"
#include "Player.h"
#include "map.h"
#include <memory>
int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Demonstration");
    std::vector<std::shared_ptr<Object>> objects;
    std::string map = "#########";
    Map m(map, sf::Color::White);
    std::vector<Object> walls = m.getWalls();
    for(auto &wall : walls) {
        objects.push_back(std::make_shared<Object>(wall));
    }
    Player player(sf::Vector2f(60, 50), sf::Vector2f(400, 300));
    objects.push_back(std::make_shared<Player>(player));
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event{};
        sf::Time dt = clock.restart();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for(auto &object : objects) {
            object->update(dt.asSeconds());
        }
        window.clear();
        for(auto &object : objects) {
            window.draw(object->body);
        }
        window.display();
    }

    return 0;
}
