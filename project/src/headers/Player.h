//
// Created by juhtyg on 18.2.24.
//

#ifndef INC_3D_GAME_PLAYER_H
#define INC_3D_GAME_PLAYER_H
#include <SFML/Graphics.hpp>
#include "3dRender.h"
#include "../Utils/Utils.h"
#include "map.h"
#include <memory>
#include "Item.h"

class Player{
private:

    Vector2d plane;
    Vector2d direction;
    Map& map;
    sf::Vector2i lastMousePos;
    std::unique_ptr<Camera> camera;
    bool isFinishable = false; // if goal is to only collect items than its false
    float sideSpeed = 0;
    float speed = 0;
    float rotationSpeed = 0;
    sf::Vector2i windowPosition;


    /**
     * @brief looks if the position on the map is accessible (there is no wall)
     * 
     * @param position 
     * @return true 
     * @return false 
     */
    bool isLegalPosition(const Vector2d& position);

    /**
     * @brief move handles input for movement
     * 
     * @param dt 
     * @param speed 
     * @param acceleration 
     */
    void move(float dt, float speed, float acceleration);

    /**
     * @brief rotate handles input for rotation
     * 
     * @param dt 
     * @param rotationSpeed 
     * @param rotAccel 
     */
    void rotate(float dt, float rotationSpeed, float rotAccel);
public:
    /**
     * @brief Construct a new Player object
     * 
     * @param texture 
     * @param windowSize
     * @param map
     * @param isFinishable
     */
    Player(Texture& texture, sf::Vector2i windowSize, Map& map, bool isFinishable = false);

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
    void Render(sf::RenderWindow &window);

};


#endif //INC_3D_GAME_PLAYER_H
