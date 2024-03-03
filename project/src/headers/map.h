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

using texture_ptrs = std::vector<std::unique_ptr<sf::Texture>>;


class Map {
private:
    std::vector<std::vector<int>>& map;
    float Width;
    float Height;
public:
    Map(const std::string& file, const std::string& config, float Width, float Height,  std::vector<std::vector<int>>& map);


    void render(sf::RenderWindow& window);
};


#endif //INC_3D_GAME_MAP_H
