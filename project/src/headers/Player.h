//
// Created by juhtyg on 18.2.24.
//

#ifndef INC_3D_GAME_PLAYER_H
#define INC_3D_GAME_PLAYER_H
#include <SFML/Graphics.hpp>
#include "3dRender.h"
#include "Utils.h"
#include <memory>

class Player{
private:
    const int legal[2] = {0,2};
    float speed;
    float rotationSpeed;
    Vector2d position;
    Vector2d direction;
    Vector2d plane;
    int lastMousePositionX;
    std::unique_ptr<Camera> camera;
    std::vector<std::vector<int>>& map;
    bool isLegalPosition(const Vector2d& position);
public:
    Player(sf::Texture& texture, Vector2d position, sf::Vector2i windowSize, sf::Vector2u textureSize, std::vector<std::vector<int>>& map);

    sf::Vector2f getPosition();
    sf::Vector2f getDirection();

    void update(float dt) ;
    void Render(sf::RenderWindow &window) ;


};


#endif //INC_3D_GAME_PLAYER_H
