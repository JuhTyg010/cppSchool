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



class Map {
private:
    std::vector<std::vector<int>>& map;
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
    Map( const std::string& config, float Width, float Height,  std::vector<std::vector<int>>& map, std::vector<sf::Vector2i>& items);

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
};


#endif //INC_3D_GAME_MAP_H
