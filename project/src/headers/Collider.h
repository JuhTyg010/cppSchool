//
// Created by juhtyg on 18.2.24.
//

#ifndef INC_3D_GAME_COLLIDER_H
#define INC_3D_GAME_COLLIDER_H

#include <SFML/Graphics.hpp>

class Collider {
private:
    sf::RectangleShape& body;
public:
    Collider(sf::RectangleShape& body);

    void move(float dx, float dy) { body.move(dx, dy); }
    bool checkCollision(Collider&& other, float push);
    sf::Vector2f getPosition() { return body.getPosition(); }
    sf::Vector2f getHalfSize() { return body.getSize() / 2.0f; }
};
#endif //INC_3D_GAME_COLLIDER_H
