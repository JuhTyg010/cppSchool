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
#include <iostream>



class Camera {
private:
    sf::Vector2f plane;
    sf::Vector2u windowSize;
    sf::Vector2u textureSize;
    std::vector<std::vector<int>>& map;
    std::vector<std::unique_ptr<Stripe>> stripes;

public:
    Camera(sf::Vector2f plane, sf::Vector2u windowSize, sf::Vector2u textureSize, std::vector<std::vector<int>>& map, sf::Texture& texture);
    Camera(float planeX, float planeY, unsigned int windowWidth, unsigned int windowHeight, sf::Vector2u textureSize ,
           std::vector<std::vector<int>>& map, sf::Texture& texture);
    Camera(const Camera& other);


    void render(const sf::Vector2f& position, const sf::Vector2f& direction, sf::RenderWindow& window);
};


#endif //INC_3D_GAME_3DRENDER_H
