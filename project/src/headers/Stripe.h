//
// Created by juhtyg on 1.3.24.
//

#ifndef INC_3D_GAME_STRIPE_H
#define INC_3D_GAME_STRIPE_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "spriteRenderer.h"
#include <memory>

class Stripe {
private:
    std::unique_ptr<spriteRenderer> sprite;
    sf::Vector2f position;   // just X axis from left to right
    float scale; // scale of the Stripe
    sf::Vector2i size; //x is 1 and y is the height of the texture
    sf::Vector2f matrix;
    void rescale(int drawStart, int drawEnd);


public:
    Stripe(sf::Vector2f position, int size, sf::Vector2f matrix, sf::Texture& texture);
    explicit Stripe(const Stripe& other);

    void update(int Xdistance, int drawStart, int drawEnd, int texture);
    void Render(sf::RenderWindow& window);
};


#endif //INC_3D_GAME_STRIPE_H
