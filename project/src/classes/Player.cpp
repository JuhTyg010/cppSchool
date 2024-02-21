//
// Created by juhtyg on 18.2.24.
//

#include "../headers/Player.h"
#include "Utils.h"
#include <cmath>


Player::Player(const std::string &path, sf::Vector2f position, sf::Vector2f scale, sf::Vector2f size,sf::Vector2f matrix) {
    sprite = std::make_unique<spriteRenderer>(spriteRenderer(path, position, scale, size, matrix));
    sf::Vector2f actSize(size.x*scale.x, size.y * scale.y);
    body.setSize(actSize);
    body.setOrigin(size / 2.0f);
    body.setFillColor(sf::Color::Transparent);
    body.setPosition(sprite->sprite.getPosition());
    speed = 10;
    angle = 0;
    rotationSpeed = 150;
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

    velocity.x += acceleration.x * (float) cos(MyMath::DegToRad(angle)) - acceleration.y * (float) sin(MyMath::DegToRad(angle));
    velocity.y += acceleration.y * (float) cos(MyMath::DegToRad(angle)) + acceleration.x * (float) sin(MyMath::DegToRad(angle));
    velocity *= 0.95f;
    if(angle > 360) {
        angle -= 360;
    } else if(angle < 0) {
        angle += 360;
    }
    //0 -> 337.5 - 22.5 1 -> 22.5 - 67.5 2 -> 67.5 - 112.5 3 -> 112.5 - 157.5 4 -> 157.5 - 202.5 5 -> 202.5 - 247.5 6 -> 247.5 - 292.5 7 -> 292.5 - 337.5
    sf::Vector2f direction = sprite->getCurrentFrame();
    //TODO: Fix this
    if(angle + 22.5 < direction.x * 45) {
        sprite->prevFrame();
    } else if(angle - 22.5 > direction.x * 45 ) {
        sprite->nextFrame();
    }
    sf::Vector2f pos = body.getPosition();
    body.setPosition(pos.x + velocity.x, pos.y + velocity.y);
    sprite->setPosition(pos);
}


void Player::Render(sf::RenderWindow &window) {
    Object::Render(window);
    sprite->Render(window);
}


