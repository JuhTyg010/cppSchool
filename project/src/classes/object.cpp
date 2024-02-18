//
// Created by juhtyg on 18.1.24.
//
#include "../headers/object.h"
#include <iostream>

void Object::update(float dt) {
    float x = body.getPosition().x + velocity.x;
    float y = body.getPosition().y + velocity.y;
    body.setPosition(x, y);

}

Object::Object(sf::Vector2f size, sf::Vector2f position, sf::Color color) {
    body.setSize(size);
    body.setFillColor(color);
    body.setOrigin(size / 2.0f);
    body.setPosition(position);
}



