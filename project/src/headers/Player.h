//
// Created by juhtyg on 18.2.24.
//

#ifndef INC_3D_GAME_PLAYER_H
#define INC_3D_GAME_PLAYER_H
#include <SFML/Graphics.hpp>
#include "object.h"
#include "spriteRenderer.h"
#include <memory>

class Player: public Object{
private:
    sf::Vector2f acceleration;
    float speed;
    float rotationSpeed;
    float angle;
    std::unique_ptr<spriteRenderer> sprite;
public:
    Player(sf::Texture& texture, sf::Vector2f position, sf::Vector2f scale, sf::Vector2f size, sf::Vector2f matrix);

    sf::Vector2f getPosition();
    sf::Vector2f getDirection();

    void update(float dt) override;
    void Render(sf::RenderWindow &window) override;


};


#endif //INC_3D_GAME_PLAYER_H
