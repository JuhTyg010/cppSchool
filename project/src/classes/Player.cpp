//
// Created by juhtyg on 18.2.24.
//

#include "../headers/Player.h"
#include "Utils.h"
#include <cmath>


Player::Player(sf::Texture &texture, Vector2d position, sf::Vector2i windowSize, sf::Vector2u textureSize,
               std::vector<std::vector<int>> &map)
               : plane(Vector2d(0, 0.66)), direction(Vector2d(-1, 0)), position(position), speed(2), rotationSpeed(30),
               map(map), lastMousePositionX(400){
    camera = std::make_unique<Camera>(Camera(windowSize, textureSize, map, texture)); }



void Player::update(float dt) {
    map.at(static_cast<int>(position.x)).at(static_cast<int>(position.y))  = 0;    //set 2 to 0 so if we move we dont have to find the old position

    //when rotating we need to rotate both direction and plane vectors
    if(sf::Mouse::getPosition().x > lastMousePositionX){
        Vector2d oldDir = direction;
        direction.x = direction.x * std::cos(-rotationSpeed * dt) - direction.y * std::sin(-rotationSpeed * dt);
        direction.y = oldDir.x * std::sin(-rotationSpeed * dt) + direction.y * std::cos(-rotationSpeed * dt);
        Vector2d oldPlane = plane;
        plane.x = plane.x * std::cos(-rotationSpeed * dt) - plane.y * std::sin(-rotationSpeed * dt);
        plane.y = oldPlane.x * std::sin(-rotationSpeed * dt) + plane.y * std::cos(-rotationSpeed * dt);
    }
    //rotate to the left using mouse x-axes
    if(sf::Mouse::getPosition().x < lastMousePositionX){
        Vector2d oldDir = direction;
        direction.x = direction.x * std::cos(rotationSpeed * dt) - direction.y * std::sin(rotationSpeed * dt);
        direction.y = oldDir.x * std::sin(rotationSpeed * dt) + direction.y * std::cos(rotationSpeed * dt);
        Vector2d oldPlane = plane;
        plane.x = plane.x * std::cos(rotationSpeed * dt) - plane.y * std::sin(rotationSpeed * dt);
        plane.y = oldPlane.x * std::sin(rotationSpeed * dt) + plane.y * std::cos(rotationSpeed * dt);
    }
    sf::Mouse::setPosition(sf::Vector2i(400, 300)); //set mouse position to the middle of the screen
    //move forward and backwards
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        if(isLegalPosition(Vector2d(position.x + (direction.x * speed * dt), position.y))) position.x += direction.x * speed * dt;
        if(isLegalPosition(Vector2d(position.x, position.y + (direction.y * speed * dt)))) position.y += direction.y * speed * dt;

    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        if(isLegalPosition(Vector2d(position.x - (direction.x * speed * dt), position.y))) position.x -= direction.x * speed * dt;
        if(isLegalPosition(Vector2d(position.x, position.y - (direction.y * speed * dt)))) position.y -= direction.y * speed * dt;
    }
    //move left and right
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        if(isLegalPosition(Vector2d(position.x - (plane.x * speed * dt), position.y))) position.x -= plane.x * speed * dt;
        if(isLegalPosition(Vector2d(position.x, position.y - (plane.y * speed * dt))) ) position.y -= plane.y * speed * dt;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        if(isLegalPosition(Vector2d(position.x + (plane.x * speed * dt), position.y))) position.x += plane.x * speed * dt;
        if(isLegalPosition(Vector2d(position.x, position.y + (plane.y * speed * dt))) ) position.y += plane.y * speed * dt;
    }
    map.at(static_cast<int>(position.x)).at(static_cast<int>(position.y)) = 2; //set 2 to the new position
}


void Player::Render(sf::RenderWindow &window) {
    camera->render(position, direction, plane, window);
}

bool Player::isLegalPosition(const Vector2d &pos) {
    try {
        int x = map.at(static_cast<int>(pos.x)).at(static_cast<int>(pos.y));
        for (int i: legal) {
            if (x == i) return true;
        }
        return false;
    } catch (std::out_of_range &e) {
        return false;
    }
}
