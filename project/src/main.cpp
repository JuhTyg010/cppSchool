#include <iostream>
#include <SFML/Graphics.hpp>
#include "object.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Demonstration");

    sf::RectangleShape button(sf::Vector2f(100, 50));
    button.setPosition(350, 275);
    button.setFillColor(sf::Color::White);

    Object Player(50,50,800,600);

    std::vector<sf::Color> colorList = {
            sf::Color::Red,
            sf::Color::Green,
            sf::Color::Blue,
            sf::Color::Yellow,
            sf::Color::Magenta
    };
    int color = 0;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (button.getGlobalBounds().contains(mousePos)) {

                    ++color %= colorList.size();
                }
            }
            sf::Time deltaTime = clock.restart();

            // Handle keyboard input

        }

        Player.update();

        window.clear(colorList[color]);
        window.draw(Player.body);
        window.draw(button);
        window.display();
    }

    return 0;
}
