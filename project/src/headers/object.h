//
// Created by juhtyg on 18.1.24.
//

#ifndef INC_3D_GAME_OBJECT_H
#define INC_3D_GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include "Collider.h"

class Object {
protected:
    sf::Texture texture;
    sf::Sprite sprite;

public:

    sf::RectangleShape body;
    sf::Vector2f velocity;
    Object() = default;
    ~Object() = default;
    virtual void update(float dt);
    virtual Collider getCollider(){ return (body);};
    virtual void Render(sf::RenderWindow &window) {window.draw(body); window.draw(sprite);};
};


#endif //INC_3D_GAME_OBJECT_H
