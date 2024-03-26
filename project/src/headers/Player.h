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
    // if goal is to only collect items than its false
    bool isFinishable = false;

    int finishNum = 2; //convection on map
    int playerNum = 3; //convection on map
    const int legal[3] = {0,playerNum, 5};  //0 is empty and 5 is item
    float sideSpeed = 0;
    float speed = 0;
    float rotationSpeed = 0;

    Vector2d position;
    Vector2d direction;
    Vector2d plane;
    sf::Vector2i lastMousePos;
    sf::Vector2i windowPosition;

    std::unique_ptr<Camera> camera;
    std::vector<std::vector<int>>& map;
    std::vector<sf::Vector2i>& items;

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
     * @param position 
     * @param windowSize 
     * @param textureSize 
     * @param map
     * @param items
     * @param item
     * @param isFinishable
     */
    Player(Texture& texture, sf::Vector2i windowSize, std::vector<std::vector<int>>& map, std::vector<sf::Vector2i>& items, Item& item, bool isFinishable = false);
    
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
    void Render(sf::RenderWindow &window);

};


#endif //INC_3D_GAME_PLAYER_H
