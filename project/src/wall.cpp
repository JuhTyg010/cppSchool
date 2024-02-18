//
// Created by juhtyg on 18.2.24.
//

#include "wall.h"

Wall::Wall(sf::Vector2f size, sf::Vector2f position, sf::Color color) {
    body.setSize(size);
    body.setFillColor(color);
    body.setPosition(position);
}