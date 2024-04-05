//
// Created by juhtyg on 23.2.24.
//

#ifndef INC_3D_GAME_3DRENDER_H
#define INC_3D_GAME_3DRENDER_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <memory>
#include <set>
#include "Stripe.h"
#include "Item.h"
#include "map.h"
#include "Utils.h"

class Camera {
private:
    sf::Vector2i windowSize;
    sf::Vector2f textureSize;
    Map& map;
    std::vector<std::shared_ptr<Stripe>> stripes;

public:
    double pitch = 0;
    /**
     * @brief Construct a new Camera object
     * 
     * @param windowSize 
     * @param map 
     */
    Camera(sf::Vector2i windowSize, Map& map, Texture& textures);

    /**
     * @brief Construct a new Camera object
     * 
     * @param windowWidth 
     * @param windowHeight 
     * @param map 
     */
    Camera(int windowWidth, int windowHeight, Map& map, Texture& texture);

    /**
     * @brief render recalculates the stripes and items which can be seen and draws them on the screen
     * 
     * @param position 
     * @param direction 
     * @param plane 
     * @param window 
     */
    void render(const Vector2d& position, const Vector2d& direction, const Vector2d& plane, sf::RenderWindow& window);



    /**
     * @brief get the window size
     * 
     * @return sf::Vector2i 
     */
    [[nodiscard]] sf::Vector2i getWindowSize() const { return windowSize; }
};


#endif //INC_3D_GAME_3DRENDER_H
