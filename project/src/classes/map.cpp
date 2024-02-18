//
// Created by juhtyg on 18.2.24.
//

#include "../headers/map.h"

Map::Map(std::string& map, sf::Color color) {
    float width = 50.0f;
    float height = 50.0f;
    std::stringstream ss(map);
    std::string line;
    int row = 0;
    while(std::getline(ss, line)) {
        for(int i = 0; i < line.size(); i++) {
            if(line[i] == '#') {
                walls.push_back(Wall(sf::Vector2f(width, height), sf::Vector2f(width * i, height * row), color));
            }
        }
        row++;
    }

}

std::vector<Object>& Map::getWalls()  {
    return walls;
}