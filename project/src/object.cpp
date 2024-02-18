//
// Created by juhtyg on 18.1.24.
//
#include "object.h"

void Object::update() {
    x += horizontal_speed;
    y += vertical_speed;
    body.setPosition(x, y);

}


