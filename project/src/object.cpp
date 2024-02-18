//
// Created by juhtyg on 18.1.24.
//
#include "object.h"

void Object::update(float dt) {
    x += velocity.x;
    y += velocity.y;
    body.setPosition(x, y);

}

Collider Object::getCollider() {
    return Collider(body, velocity);
}

void Object::onCollision(sf::Vector2f &direction) {
    if (direction.x != 0.0f) {
        velocity.x = 0.0f;
    }
    if (direction.y != 0.0f) {
        velocity.y = 0.0f;
    }
    body.setPosition(OldPosition);
}

