//
// Created by juhtyg on 18.2.24.
//

#ifndef INC_3D_GAME_MAP_H
#define INC_3D_GAME_MAP_H
#include <vector>
#include "wall.h"
#include <sstream>
#include <memory>

class Map {
private:
    std::vector<Object> walls;
public:
    Map(std::string& map, sf::Color color);
    std::vector<Object>& getWalls();
};


#endif //INC_3D_GAME_MAP_H
