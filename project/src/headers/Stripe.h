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
    Vector2d actualSize;
    bool isHorizontal;

    /**
     * @brief calculate the value of scale based on the full size of the stripe
     * 
     * @param drawStart 
     * @param drawEnd 
     */
    void rescale(int drawStart, int drawEnd);


public:
    /**
     * @brief Construct a new Stripe object
     * 
     * @param position 
     * @param size 
     * @param matrix 
     * @param texture 
     */
    Stripe(sf::Vector2f position, Vector2d actualSize, Texture& texture, bool isHorizontal);

    /**
     * @brief Construct a new Stripe object
     * 
     * @param other 
     */
    explicit Stripe(const Stripe& other);

    /**
     * @brief update the stripe, rescale and set the texture
     * 
     * @param Xdistance 
     * @param drawStart 
     * @param drawEnd 
     * @param texture 
     * @param isHorizontal
     */
    void update(int Xdistance, int drawStart, int drawEnd, int textureNum);

    /**
     * @brief render the stripe to the window
     * 
     * @param window 
     */
    void Render(sf::RenderWindow& window);
};


#endif //INC_3D_GAME_STRIPE_H
