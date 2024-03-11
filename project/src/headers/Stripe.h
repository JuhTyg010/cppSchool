//
// Created by juhtyg on 1.3.24.
//

#ifndef INC_3D_GAME_STRIPE_H
#define INC_3D_GAME_STRIPE_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <memory>
#include "VisibleObject.h"

class Stripe : public VisibleObject {
private:
    float scale; // scale of the Stripe
    sf::Vector2f matrix;

    /**
     * @brief calculate the value of scale based on the full size of the stripe
     * 
     * @param drawStart 
     * @param drawEnd 
     */
    void rescale(int drawStart, int drawEnd, bool isHorizontal);


public:
    /**
     * @brief Construct a new Stripe object
     * 
     * @param position 
     * @param size 
     * @param matrix 
     * @param texture 
     */
    Stripe(sf::Vector2f position, Texture& texture);


    /**
     * @brief Update the stripe, rescale and set the textureNum
     * 
     * @param dist
     * @param drawStart 
     * @param drawEnd 
     * @param textureNum
     * @param isHorizontal
     */
    void Update(int dist, int drawStart, int drawEnd, int textureNum, bool isHorizontal);

    void Update(float dt) override {}
};


#endif //INC_3D_GAME_STRIPE_H
