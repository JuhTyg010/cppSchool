//
// Created by juhtyg on 18.2.24.
//

#include "Player.h"
#include "Utils.h"
#include <cmath>

Player::Player(sf::Vector2f size, sf::Vector2f position) {
    body.setSize(size);
    body.setOrigin(size / 2.0f);
    body.setPosition(position);
    body.setFillColor(sf::Color::Green);
    speed = 10;
    rotationSpeed = 100;
    jump = 0.0f;
}

void Player::update(float dt) {
    /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        acceleration.x = -speed * dt;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        acceleration.x = speed * dt;
    } else {
        acceleration.x = 0;
    }*/ //this will be later now we use it to rotate the player
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        body.rotate(-rotationSpeed * dt);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        body.rotate(rotationSpeed * dt);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        acceleration = -speed * dt;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        acceleration = speed * dt;
    } else {
        acceleration = 0;
    }
    velocity.x += acceleration * std::cos(body.getRotation() * 3.14159265359 / 180);
    velocity.y += acceleration * std::sin(body.getRotation() * 3.14159265359 / 180);
    velocity *= 0.95f;
    sf::Vector2f pos = body.getPosition();
    body.setPosition(pos.x + velocity.x, pos.y + velocity.y);
}

