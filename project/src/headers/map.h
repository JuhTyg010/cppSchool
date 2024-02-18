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

class Map {
private:
public:
    Map(std::string& file, sf::Color color, float Width, float Height);
};


#endif //INC_3D_GAME_MAP_H
