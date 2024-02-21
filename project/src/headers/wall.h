//
// Created by juhtyg on 18.2.24.
//

#ifndef INC_3D_GAME_WALL_H
#define INC_3D_GAME_WALL_H
#include "object.h"
#include "Collider.h"

class Wall: public Object {
public:
    Wall(sf::Vector2f size, sf::Vector2f position, sf::Color color);
    /*Collider getCollider() override;
    void onCollision(sf::Vector2f &direction) override;*/
};


#endif //INC_3D_GAME_WALL_H
