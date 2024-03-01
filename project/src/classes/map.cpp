//
// Created by juhtyg on 18.2.24.
//

#include "../headers/map.h"

Map::Map(const std::string& file, const std::string& config, float Width, float Height, std::vector<std::vector<int>>& map, texture_ptrs& textures)
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
    width = Width / width;
    height = Height / height;
    int row = 0;
    int player = 0;
    while(std::getline(openfile, line)) {
        for(int i = 0; i < line.size(); i++) {
            try{
                sf::Vector2f position(width * (float) i + width / 2, height * (float) row + height / 2);
                if(line[i] == '#') {
                    map.at(row).at(i) = 1;
                    objects.push_back(std::make_unique<Wall>(Wall(sf::Vector2f(width, height), position, sf::Color::Blue)));
                } else if(line[i] == 'P') {
                    if(player == 0) {
                        player = 1;
                        map.at(row).at(i) = 2;
                        objects.push_back(std::make_unique<Player>(Player(*textures[0],position, sf::Vector2f (.5,.5),
                                                                      sf::Vector2f(64, 64),sf::Vector2f(7,0))));
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

sf::Vector2f Map::getPlayerPosition() {
    for(auto& object : objects) {
        if(dynamic_cast<Player*>(object.get())) {
            sf::Vector2f pos = dynamic_cast<Player*>(object.get())->getPosition();
            //recalculate to map coordinates
            sf::Vector2f tileSize(Width / (float) map[0].size(), Height / (float) map.size());
            return { pos.x / tileSize.x, pos.y / tileSize.y};
        }
    }
    return {0,0};
}

sf::Vector2f Map::getPlayerdirection() {
    for(auto& object : objects) {
        if(dynamic_cast<Player*>(object.get())) {
            return dynamic_cast<Player*>(object.get())->getDirection();
        }
    }
    return sf::Vector2f(0,0);
}

void Map::update(float dt) {
    for(auto& object : objects) {
        object->update(dt);
    }
}

void Map::render(sf::RenderWindow& window) {
    for(auto& object : objects) {
        object->Render(window);
    }
}