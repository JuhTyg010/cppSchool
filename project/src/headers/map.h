//
// Created by juhtyg on 18.2.24.
//

#ifndef INC_3D_GAME_MAP_H
#define INC_3D_GAME_MAP_H
#include <vector>
#include "wall.h"
#include "Player.h"
#include <sstream>
#include <memory>
#include <fstream>
#include <unordered_map>

using object_ptrs = std::vector<std::unique_ptr<Object>>;
using texture_ptrs = std::vector<std::unique_ptr<sf::Texture>>;


class Map {
private:
    std::vector<std::vector<int>>& map;
    object_ptrs objects;
    float Width;
    float Height;
public:
    Map(const std::string& file, const std::string& config, float Width, float Height,  std::vector<std::vector<int>>& map, texture_ptrs& textures);

    sf::Vector2f getPlayerPosition();
    sf::Vector2f getPlayerdirection();

    void update(float dt);
    void render(sf::RenderWindow& window);
};


#endif //INC_3D_GAME_MAP_H
