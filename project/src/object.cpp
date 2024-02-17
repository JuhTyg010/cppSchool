//
// Created by juhtyg on 18.1.24.
//
#include <SFML/Graphics.hpp>
#include <math.h>
#include "object.h"


Object::Object(float x, float y, float width, float height) :
x(x), y(y), width(width), height(height), horizontal_speed(0), vertical_speed(0), body(sf::Vector2f(50, 50))
{
    body.setPosition(x,y);
    body.setFillColor(sf::Color::Black);
}

void Object::update() {
    float acc = 0.2;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        vertical_speed -= acc;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        vertical_speed += acc;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        horizontal_speed += acc;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        horizontal_speed -= acc;
    }
    set_speed();
}

void Object::set_speed() {
    float dumper = 0.6;
    x += horizontal_speed;
    y += vertical_speed;
    //dumper slows you down making you have max speed limit
    horizontal_speed *= dumper;
    vertical_speed *= dumper;
    x < 0 ? x = 0 :x;
    x > width-body.getSize().x ? x = width-body.getSize().x : x;
    y < 0 ? y = 0 : y;
    y > height-body.getSize().y ? y = height-body.getSize().y : y;

    body.setPosition(x,y);

}