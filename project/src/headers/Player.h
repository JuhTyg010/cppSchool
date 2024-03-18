//
// Created by juhtyg on 18.2.24.
//

#ifndef INC_3D_GAME_PLAYER_H
#define INC_3D_GAME_PLAYER_H
#include <SFML/Graphics.hpp>
#include "3dRender.h"
#include "Utils.h"
#include <memory>
#include "Item.h"

class Player{
private:
    const int legal[2] = {0,2};
    float speed;
    float rotationSpeed;
    Vector2d position;
    Vector2d direction;
    Vector2d plane;
    sf::Vector2i lastMousePosition;
    std::unique_ptr<Camera> camera;
    std::vector<std::vector<int>>& map;
    bool isLegalPosition(const Vector2d& position);
public:
    /**
     * @brief Construct a new Player object
     * 
     * @param texture 
     * @param position 
     * @param windowSize 
     * @param textureSize 
     * @param map 
     */
    Player(Texture& texture, Vector2d position, sf::Vector2i windowSize, sf::Vector2u textureSize, std::vector<std::vector<int>>& map, Item& item);
    
    /**
     * @brief Get the Position of the object
     * 
     * @return sf::Vector2f 
     */
    sf::Vector2f getPosition();
    
    /**
     * @brief Get the Direction of the object
     * 
     * @return sf::Vector2f 
     */
    sf::Vector2f getDirection();

    /**
     * @brief Update the player (check inputs, Update position)
     * 
     * @param dt - delta time
     */
    void Update(float dt);

    /**
     * @brief Render the player and also render the camera(players view)
     * 
     * @param window to render
     */
    void Render(sf::RenderWindow &window) ;


};


#endif //INC_3D_GAME_PLAYER_H
