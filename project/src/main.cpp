#include <iostream>
#include <SFML/Graphics.hpp>
#include "object.h"
#include "Player.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Demonstration");
    std::vector<Object> objects;
    std::string map = "#########"
                      "#       #"
                      "#       #"
                      "#       #"
                      "#       #"
                      "#########";
    Player player(sf::Vector2f(20, 30), sf::Vector2f(400, 300));
    objects.push_back(player);
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        sf::Time dt = clock.restart();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle keyboard input

        }

        player.update(dt.asSeconds());
        window.clear();
        for(auto &object : objects) {
            window.draw(object.body);
        }
        window.display();
    }

    return 0;
}
