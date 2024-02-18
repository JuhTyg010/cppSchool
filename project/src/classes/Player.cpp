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
    if(angle > 0 && angle < 90) {
        sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
    } else if(angle > 90 && angle < 180) {
        sprite.setTextureRect(sf::IntRect(100, 0, 100, 100));
    } else if(angle > 180 && angle < 270) {
        sprite.setTextureRect(sf::IntRect(100, 100, 100, 100));
    } else if(angle > 270 && angle < 360) {
        sprite.setTextureRect(sf::IntRect(0, 100, 100, 100));
    }

    sf::Vector2f pos = body.getPosition();
    body.setPosition(pos.x + velocity.x, pos.y + velocity.y);
}

Player::Player(sf::Texture& texture, sf::Vector2f size, sf::Vector2f position, sf::Color color)  {
    body.setSize(size);
    body.setOrigin(size / 2.0f);
    body.setPosition(position);
    body.setFillColor(color);
    this->texture = texture;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
    speed = 10;
    angle = 0;
    rotationSpeed = 100;
}

