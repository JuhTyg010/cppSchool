//
// Created by juhtyg on 18.1.24.
//

#ifndef INC_3D_GAME_OBJECT_H
#define INC_3D_GAME_OBJECT_H

#include <SFML/Graphics.hpp>


class Object {

    float x, y;
    float width, height;
    float vertical_speed;
    float horizontal_speed;


public:
    sf::RectangleShape body;
    Object(float x, float y, float width, float height);
    void update();
    void set_speed();
};


#endif //INC_3D_GAME_OBJECT_H
