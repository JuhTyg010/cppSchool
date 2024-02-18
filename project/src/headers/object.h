//
// Created by juhtyg on 18.1.24.
//

#ifndef INC_3D_GAME_OBJECT_H
#define INC_3D_GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include "Collider.h"

class Object {


public:

    sf::RectangleShape body;
    sf::Vector2f velocity;
    Object() = default;
    Object(sf::Vector2f size, sf::Vector2f position, sf::Color color);
    ~Object() = default;
    virtual void update(float dt);
    virtual Collider getCollider(){ return (body);};
    virtual void Render(sf::RenderWindow &window) {window.draw(body);};
};


#endif //INC_3D_GAME_OBJECT_H
