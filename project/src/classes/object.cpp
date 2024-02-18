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


