//
// Created by juhtyg on 18.2.24.
//

#ifndef INC_3D_GAME_PLAYER_H
#define INC_3D_GAME_PLAYER_H
#include <SFML/Graphics.hpp>
#include "object.h"
#include <memory>

class Player: public Object{
private:
    float acceleration;
    float speed;
    float rotationSpeed;
public:
    Player(sf::Vector2f size, sf::Vector2f position);
    Player(sf::Vector2f size, sf::Vector2f position, sf::Color color);
    void update(float dt) override;



};


#endif //INC_3D_GAME_PLAYER_H
