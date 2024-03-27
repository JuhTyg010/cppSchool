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
#include "Item.h"



class Map {
private:
    std::vector<std::vector<bool>> walls;
    std::vector<std::vector<int>> items;
    std::vector<Item> itemObjects;
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
    Map( const std::string& config, float Width, float Height, Item& item);

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
     * @brief returns the item on the position
     *
     * @param x
     * @param y
     * @return Item
     */
    Item getItem(int x, int y) const;
    Item getItem(sf::Vector2i vec) const;

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
     * @param pos vector2d
     */
    void setPlayerPosition(const Vector2d& pos);


    /**
     * @brief returns if the position is an item
     *
     * @param x, y position
     *
     * @return bool
     */
    bool isItem(int x, int y) const;
    bool isItem(sf::Vector2i vec) const;

    /**
     * @brief removes the item from the position
     *
     * @param x, y position
     */
    void removeItem(int x, int y);
    void removeItem(sf::Vector2i vec);
};


#endif //INC_3D_GAME_MAP_H
