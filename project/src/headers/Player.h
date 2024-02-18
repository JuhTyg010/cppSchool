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
    sf::Vector2f acceleration;
    float speed;
    float rotationSpeed;
    float angle;
public:
    Player(sf::Vector2f size, sf::Vector2f position);
    Player(sf::Texture& texture, sf::Vector2f size, sf::Vector2f position, sf::Color color);
    void update(float dt) override;



};


#endif //INC_3D_GAME_PLAYER_H
