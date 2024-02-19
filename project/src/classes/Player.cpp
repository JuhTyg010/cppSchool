//
// Created by juhtyg on 18.2.24.
//

#include "../headers/Player.h"
#include "Utils.h"
#include <cmath>

Player::Player(sf::Vector2f size, sf::Vector2f position) {
    body.setSize(size);
    body.setOrigin(size / 2.0f);
    body.setPosition(position);
    body.setFillColor(sf::Color::Green);
    speed = 10;
    rotationSpeed = 100;
    angle = 0;
}

void Player::update(float dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        acceleration.x = -speed * dt;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        acceleration.x = speed * dt;
    } else {
        acceleration.x = 0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        angle -= rotationSpeed * dt;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
        angle += rotationSpeed * dt;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        acceleration.y = -speed * dt;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        acceleration.y = speed * dt;
    } else {
        acceleration.y = 0;
    }
    velocity.x += acceleration.x;
    velocity.y += acceleration.y;
    velocity *= 0.95f;
    if(angle > 360) {
        angle -= 360;
    } else if(angle < 0) {
        angle += 360;
    }
    //0 -> 337.5 - 22.5 1 -> 22.5 - 67.5 2 -> 67.5 - 112.5 3 -> 112.5 - 157.5 4 -> 157.5 - 202.5 5 -> 202.5 - 247.5 6 -> 247.5 - 292.5 7 -> 292.5 - 337.5
    sf::Vector2f direction = sprite->getCurrentFrame();
    if(angle < direction.x * 45 - 22.5) {
        sprite->prevAnimation();
    } else if(angle > direction.x * 45 + 22.5) {
        sprite->nextAnimation();
    }
    sf::Vector2f pos = body.getPosition();
    body.setPosition(pos.x + velocity.x, pos.y + velocity.y);
}

Player::Player(spriteRenderer& sprite, sf::Vector2f size, sf::Vector2f position, sf::Color color)  {
    body.setSize(size);
    body.setOrigin(size / 2.0f);
    body.setPosition(position);
    body.setFillColor(color);
    this->sprite = std::make_shared<spriteRenderer>(sprite);
    sprite.setPosition(position);
    speed = 10;
    angle = 0;
    rotationSpeed = 100;
}

void Player::Render(sf::RenderWindow &window) {
    Object::Render(window);
    sprite->Render(window);
}

