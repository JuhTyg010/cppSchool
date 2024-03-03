//
// Created by juhtyg on 23.2.24.
//

#ifndef INC_3D_GAME_3DRENDER_H
#define INC_3D_GAME_3DRENDER_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <memory>
#include "Stripe.h"
#include "Utils.h"
#include <iostream>



class Camera {
private:
    sf::Vector2u windowSize;
    sf::Vector2u textureSize;
    std::vector<std::vector<int>>& map;
    std::vector<std::unique_ptr<Stripe>> stripes;

public:
    Camera(sf::Vector2u windowSize, sf::Vector2u textureSize, std::vector<std::vector<int>>& map, sf::Texture& texture);
    Camera(unsigned int windowWidth, unsigned int windowHeight, sf::Vector2u textureSize ,
           std::vector<std::vector<int>>& map, sf::Texture& texture);
    Camera(const Camera& other);


    void render(const Vector2d& position, const Vector2d& direction, const Vector2d& plane, sf::RenderWindow& window);
};


#endif //INC_3D_GAME_3DRENDER_H
