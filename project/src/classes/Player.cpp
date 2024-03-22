//
// Created by juhtyg on 18.2.24.
//

#include "../headers/Player.h"
#include "Utils.h"
#include <cmath>


Player::Player(Texture &texture, Vector2d position, sf::Vector2i windowSize, std::vector<std::vector<int>> &map, Item &item)
               : plane(Vector2d(0, 1)), direction(Vector2d(-1, 0)), position(position),
                 map(map), lastMousePos(sf::Mouse::getPosition()) {
    camera = std::make_unique<Camera>(Camera(windowSize, map, texture, item)); }



void Player::Update(float dt) {
    map.at(static_cast<int>(position.x)).at(static_cast<int>(position.y))  = 0;    //set 2 to 0 so if we move we don't have to find the old position
    rotate(dt, 10, .2);
    move(dt, 2, .2);
    map.at(static_cast<int>(position.x)).at(static_cast<int>(position.y)) = playerNum; //set 2 to the new position
}


void Player::Render(sf::RenderWindow &window) {
    windowPosition = window.getPosition();
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

void Player::move(float dt, float maxSpeed, float accel){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) speed += accel;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) speed -= accel;
    else speed *= 0.7;
    speed = std::max(std::min(maxSpeed, speed), -maxSpeed);

    //move forward and backwards
    if(speed > 0.01 || speed < -0.01) {
        Vector2d realSpeed = direction * speed * dt;
        if (isLegalPosition(Vector2d(position.x + realSpeed.x, position.y))) position.x += realSpeed.x;
        if (isLegalPosition(Vector2d(position.x, position.y + realSpeed.y))) position.y += realSpeed.y;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) sideSpeed += accel;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) sideSpeed -= accel;
    else sideSpeed *= 0.5;
    sideSpeed = std::max(std::min(maxSpeed, sideSpeed), -maxSpeed);
    //move left and right
    if(sideSpeed > 0.01 || sideSpeed < -0.01) {
        Vector2d realSpeed = plane * sideSpeed * dt;
        if(isLegalPosition(Vector2d(position.x - realSpeed.x, position.y)))  position.x -= realSpeed.x;
        if(isLegalPosition(Vector2d(position.x, position.y - realSpeed.y)))  position.y -= realSpeed.y;
    }
}

void Player::rotate(float dt, float rotSpeed, float rotAccel) {
    sf::Vector2i mousePos = sf::Mouse::getPosition();

    rotationSpeed = std::max(std::min((float) rotSpeed, rotationSpeed),(float) -rotSpeed);

    if(mousePos.x > lastMousePos.x) rotationSpeed -= (rotAccel * (mousePos.x - lastMousePos.x));
    else if(mousePos.x < lastMousePos.x) rotationSpeed += (rotAccel * (lastMousePos.x - mousePos.x));

    else rotationSpeed *= 0.5;

    if(rotationSpeed != 0){

        Vector2d oldDir = direction;
        direction.x = oldDir.x * std::cos(rotationSpeed * dt) - oldDir.y * std::sin(rotationSpeed * dt);
        direction.y = oldDir.x * std::sin(rotationSpeed * dt) + oldDir.y * std::cos(rotationSpeed * dt);
        Vector2d oldPlane = plane;
        plane.x = oldPlane.x * std::cos(rotationSpeed * dt) - oldPlane.y * std::sin(rotationSpeed * dt);
        plane.y = oldPlane.x * std::sin(rotationSpeed * dt) + oldPlane.y * std::cos(rotationSpeed * dt);

    }
    camera->pitch += (lastMousePos.y - mousePos.y) * 2;
    camera->pitch = std::max(std::min(camera->pitch, (double) 1000),(double) -1000);

    //set mouse position if its on border of the window
    bool setMouse = false;
    sf::Vector2i maxPos = windowPosition + camera->getWindowSize();
    int delta = 10;

    if(mousePos.x <= windowPosition.x){
        mousePos.x = maxPos.x - delta;
        setMouse = true;
    }
    else if(mousePos.x >= maxPos.x) {
        mousePos.x = windowPosition.x + delta;
        setMouse = true;
    }
    if(mousePos.y <= windowPosition.y) {
        mousePos.y = maxPos.y - delta;
        setMouse = true;
    }
    else if(mousePos.y >= maxPos.y) {
        mousePos.y = windowPosition.y + delta;
        setMouse = true;
    }
    if(setMouse) {
        sf::Mouse::setPosition(mousePos);
        setMouse = false;
    }

    lastMousePos = mousePos;
}
