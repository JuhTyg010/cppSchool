//
// Created by juhtyg on 18.2.24.
//

#include "../headers/map.h"

Map::Map(std::string& file, sf::Color color, float Width, float Height) {
    std::ifstream openfile(file);
    std::vector<std::vector<int>> tempMap;
    if(openfile.is_open()) {
        std::string line;
        while(std::getline(openfile, line)) {
            std::vector<int> row;
            std::stringstream ss(line);
            int number;
            while(ss >> number) {
                row.push_back(number);
            }
            tempMap.push_back(row);
        }
    }
    for(int i = 0; i < tempMap.size(); i++) {
        for(int j = 0; j < tempMap[i].size(); j++) {
            if(tempMap[i][j] == 1) {
                std::shared_ptr<Wall> wall = std::make_shared<Wall>(sf::Vector2f(Width / tempMap[i].size(), Height / tempMap.size()), sf::Vector2f(j * Width / tempMap[i].size(), i * Height / tempMap.size()), color);
            }
        }
    }
}