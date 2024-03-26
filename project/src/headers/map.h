//
// Created by juhtyg on 18.2.24.
//

#ifndef INC_3D_GAME_MAP_H
#define INC_3D_GAME_MAP_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include <memory>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include "Utils.h"



class Map {
private:
    std::vector<std::vector<bool>> walls;
    std::vector<std::vector<bool>> items;
    Vector2d playerPosition;
    sf::Vector2i finishPosition;

    float Width;
    float Height;
public:
    /**
     * @brief Construct a new Map object from config file
     * 
     * @param config 
     * @param Width 
     * @param Height 
     * @param map 
     */
    Map( const std::string& config, float Width, float Height);

    /**
     * @brief renders the map from top-down view 
     * 
     * @param window 
     */
    void render(sf::RenderWindow& window);

    /**
     * @brief returns the number of items on the map
     * 
     * @return int 
     */
    int getItemCount() const;

    /**
     * @brief returns if the position is a wall
     *
     * @return bool
     */
    bool isWall(int x, int y) const;
    bool isWall(sf::Vector2i vec) const;


    /**
     * @brief returns if the position is a finish
     *
     * @return bool
     */
    bool isFinish(int x, int y) const;
    bool isFinish(sf::Vector2i vec) const;

    /**
     * @brief returns the position of the player
     *
     * @return sf::Vector2f
     */
    Vector2d getPlayerPosition() const;

    /**
     * @brief sets the position of the player
     *
     * @param pos
     */
    void setPlayerPosition(const Vector2d& pos);


    /**
     * @brief returns if the position is an item
     *
     * @return bool
     */
    bool isItem(int x, int y) const;
    bool isItem(sf::Vector2i vec) const;
};


#endif //INC_3D_GAME_MAP_H
