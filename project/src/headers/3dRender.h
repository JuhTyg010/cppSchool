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
#include "Item.h"
#include "Utils.h"



class Camera {
private:
    sf::Vector2i windowSize;
    sf::Vector2f textureSize;
    std::vector<std::vector<int>>& map;
    std::unique_ptr<Stripe> stripe;
    Item& item;

public:
    Camera(sf::Vector2i windowSize, std::vector<std::vector<int>>& map, Texture& , Item& item);
    Camera(int windowWidth, int windowHeight, std::vector<std::vector<int>>& map, Texture& texture, Item& item);


    void render(const Vector2d& position, const Vector2d& direction, const Vector2d& plane, sf::RenderWindow& window);
};


#endif //INC_3D_GAME_3DRENDER_H
