//
// Created by juhtyg on 18.2.24.
//

#include "../headers/map.h"

Map::Map(const std::string& file, const std::string& config, float Width, float Height, std::vector<std::vector<int>>& map)
        : map(map), Width(Width), Height(Height) {
    std::ifstream openfile(file);

    std::unordered_map<std::string, std::string> settings;
    std::ifstream openconfig(config);
    std::string line;
    //loads from config
    while(std::getline(openconfig, line)) {
        std::string key;
        std::string value;
        std::stringstream ss(line);
        ss >> key >> value;
        settings.insert(std::make_pair(key, value));
    }
    openconfig.close();
    //loads from file
    std::getline(openfile, line);
    float width;
    float height;
    std::stringstream ss(line);
    ss  >> width >> height;
    map.resize(static_cast<int>(height));
    for(int i = 0; i < static_cast<int>(height); i++) {
        map[i].resize(static_cast<int>(width));
    }
    int row = 0;
    int player = 0;
    while(std::getline(openfile, line)) {
        for(int i = 0; i < line.size(); i++) {
            try{
                if(line[i] == '#') {
                    map.at(row).at(i) = 1;
                } else if(line[i] == 'P') {
                    if(player == 0) {
                        player = 1;
                        map.at(row).at(i) = 2;
                    }
                }
            } catch (std::out_of_range& e) {
                std::cerr << "Corrupted file" << std::endl;
            }
        }
        row++;
    }
    openfile.close();
}



void Map::render(sf::RenderWindow& window) {
    sf::Vector2f size(Width / map.at(0).size(), Height / map.size());

    for(int i = 0; i < map.size(); i++) {
        for(int j = 0; j < map.at(i).size(); j++) {
            if(map.at(i).at(j) == 1) {
                sf::RectangleShape rectangle;
                rectangle.setSize(size);
                rectangle.setPosition(j * size.x, i * size.y);
                rectangle.setFillColor(sf::Color::White);
                window.draw(rectangle);
            } else if(map.at(i).at(j) == 2) {
                sf::RectangleShape rectangle;
                rectangle.setSize(size / 2.0f);
                rectangle.setPosition((j+.5f) * size.x, (i+.5f) * size.y);
                rectangle.setFillColor(sf::Color::Green);
                window.draw(rectangle);
            }
        }
    }
}