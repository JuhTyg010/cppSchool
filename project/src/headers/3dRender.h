//
// Created by juhtyg on 23.2.24.
//

#ifndef INC_3D_GAME_STRIPE_H
#define INC_3D_GAME_STRIPE_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

class Camera {
private:
    sf::Vector2f plane;
    sf::Vector2u windowSize;
    std::vector<std::vector<int>>& map;

public:
    Camera(sf::Vector2f plane, sf::Vector2u windowSize, std::vector<std::vector<int>>& map);
    Camera(float planeX, float planeY, unsigned int windowWidth, unsigned int windowHeight, std::vector<std::vector<int>>& map);
    Camera(const Camera& other);


    void render(const sf::Vector2f& position, const sf::Vector2f& direction, sf::RenderWindow& window);
};


#endif //INC_3D_GAME_STRIPE_H
