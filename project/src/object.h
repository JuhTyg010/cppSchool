//
// Created by juhtyg on 18.1.24.
//

#ifndef INC_3D_GAME_OBJECT_H
#define INC_3D_GAME_OBJECT_H

#include <SFML/Graphics.hpp>


class Object {


    float vertical_speed;
    float horizontal_speed;

public:
    float x, y;
    float width, height;
    sf::RectangleShape body;
    Object() = default;
    ~Object() = default;
    virtual void update();
    virtual void set_speed();
};


#endif //INC_3D_GAME_OBJECT_H
