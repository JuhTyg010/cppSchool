//
// Created by juhtyg on 18.1.24.
//

#ifndef INC_3D_GAME_OBJECT_H
#define INC_3D_GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include "Collider.h"

class Object {

    float x, y;
    float width, height;
    sf::Vector2f OldPosition;

public:

    sf::RectangleShape body;
    sf::Vector2f velocity;
    Object() = default;
    ~Object() = default;
    virtual void update(float dt);
    virtual Collider getCollider();
    virtual void onCollision(sf::Vector2f &direction);
};


#endif //INC_3D_GAME_OBJECT_H
