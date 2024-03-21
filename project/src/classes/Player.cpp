//
// Created by juhtyg on 18.2.24.
//

#include "../headers/Player.h"
#include "Utils.h"
#include <cmath>


Player::Player(Texture &texture, Vector2d position, sf::Vector2i windowSize,
               std::vector<std::vector<int>> &map, Item &item)
               : plane(Vector2d(0, 1)), direction(Vector2d(-1, 0)), position(position), speed(2), rotationSpeed(30),
                 map(map), lastMousePos(sf::Mouse::getPosition()) {
    camera = std::make_unique<Camera>(Camera(windowSize, map, texture, item)); }



void Player::Update(float dt) {
    map.at(static_cast<int>(position.x)).at(static_cast<int>(position.y))  = 0;    //set 2 to 0 so if we move we dont have to find the old position

    sf::Vector2i mousePos = sf::Mouse::getPosition();

    //when rotating we need to rotate both direction and plane vectors
    if(mousePos.x != lastMousePos.x){
        float x = mousePos.x > lastMousePos.x ? -1 : 1;

            Vector2d oldDir = direction;
            direction.x = direction.x * std::cos(x * rotationSpeed * dt) - direction.y * std::sin(x * rotationSpeed * dt);
            direction.y = oldDir.x * std::sin( x * rotationSpeed * dt) + direction.y * std::cos(x * rotationSpeed * dt);
            Vector2d oldPlane = plane;
            plane.x = plane.x * std::cos(x * rotationSpeed * dt) - plane.y * std::sin(x * rotationSpeed * dt);
            plane.y = oldPlane.x * std::sin(x * rotationSpeed * dt) + plane.y * std::cos(x * rotationSpeed * dt);

    }

    camera->pitch += (lastMousePos.y - mousePos.y) * 2;

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
        if(isLegalPosition(Vector2d(position.x - (plane.x * speed * dt), position.y)))  position.x -= plane.x * speed * dt;
        if(isLegalPosition(Vector2d(position.x, position.y - (plane.y * speed * dt))))  position.y -= plane.y * speed * dt;

    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        if(isLegalPosition(Vector2d(position.x + (plane.x * speed * dt), position.y)))  position.x += plane.x * speed * dt;
        if(isLegalPosition(Vector2d(position.x, position.y + (plane.y * speed * dt))))  position.y += plane.y * speed * dt;
    }
    map.at(static_cast<int>(position.x)).at(static_cast<int>(position.y)) = 2; //set 2 to the new position
}


void Player::Render(sf::RenderWindow &window) {
    camera->render(position, direction, plane, window);

}

bool Player::isLegalPosition(const Vector2d &pos) {
    try {
        int x = map.at(static_cast<int>(pos.x)).at(static_cast<int>(pos.y));
        return std::ranges::any_of(legal, [x](int i) {return x == i;});

    } catch (std::out_of_range &e) {
        return false;
    }
}
