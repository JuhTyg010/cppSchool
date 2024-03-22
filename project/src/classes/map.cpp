//
// Created by juhtyg on 18.2.24.
//

#include "../headers/map.h"

Map::Map(const std::string& config, float Width, float Height, std::vector<std::vector<int>>& map)
        : map(map), Width(Width), Height(Height) {
    std::string file;
    std::string folder;

    std::unordered_map<std::string, char> settings;
    std::ifstream openconfig(config);
    std::string line;
    //loads from config
    std::cout << config << std::endl;
    while(std::getline(openconfig, line)) {
        std::stringstream ss(line);
        std::string key;
        ss >> key;
        if(key == "map_file:"){
            ss >> file;
        } else if(key == "map_legend:") {
            std::string legend;
            legend = line.substr(key.size() + 1);
            for(int i = 0; legend[i] != ']'; ++i) {
                if(legend[i] == '[' || legend[i] == ',') {
                    std::string key;
                    i++;
                    while(legend[i] == ' ') i++;
                    while(legend[i] != ':') {
                        key += legend[i];
                        i++;
                    }
                    i++;    //skip ':'
                    while(legend[i] == ' ') i++;
                    settings.emplace(key, legend[i]);
                }
            }
        } else if(key == "resource_folder:") {
            ss >> folder;
            if(folder.back() != '/') folder += '/';
        }
    }
    openconfig.close();
    for(auto& [key, value] : settings) {
        std::cout << key << " " << settings.at(key) << std::endl;
    }
    std::cout << folder + file << std::endl;
    //loads from file
    std::ifstream openfile(folder + file);
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
                if(line[i] == settings.at("wall")) {
                    map.at(row).at(i) = 1;
                    std::cout << "wall" << std::endl;
                } else if(line[i] == settings.at("player")) {
                    if(player == 0) {
                        player = 1;
                        map.at(row).at(i) = 2;
                        std::cout << "player" << std::endl;
                    }
                } else if(line[i] == settings.at("item")) {
                    map.at(row).at(i) = 5;
                    std::cout << "item" << std::endl;
                } else std::cout << line[i] << std::endl;
            } catch (std::out_of_range& e) {
                std::cerr << "Corrupted map file" << std::endl;
                exit (1);
            }
        }
        row++;
    }
    openfile.close();
}



void Map::render(sf::RenderWindow& window) {
    sf::Vector2f size(Width /(float) map.at(0).size(), Height /(float) map.size());
    sf::RectangleShape background(sf::Vector2(Width, Height));
    background.setFillColor(sf::Color::Black);
    background.setPosition(0, 0);
    window.draw(background);

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
                rectangle.setPosition((j+.25f) * size.x, (i+.25f) * size.y);
                rectangle.setFillColor(sf::Color::Green);
                window.draw(rectangle);
            }
        }
    }
}