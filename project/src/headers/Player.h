//
// Created by juhtyg on 18.2.24.
//

#ifndef INC_3D_GAME_PLAYER_H
#define INC_3D_GAME_PLAYER_H
#include <SFML/Graphics.hpp>
#include "object.h"

class Player: public Object{
private:
    float acceleration;
    float speed;
    float rotationSpeed;
    float jump;

public:
    Player(sf::Vector2f size, sf::Vector2f position);
    void update(float dt) override;



};


#endif //INC_3D_GAME_PLAYER_H
