//
// Created by juhtyg on 18.2.24.
//

#include "../headers/map.h"

Map::Map(const std::string& config, float Width, float Height, Item& item)
        : Width(Width), Height(Height) {
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
                    std::string name;
                    i++;
                    while(legend[i] == ' ') i++;
                    while(legend[i] != ':') {
                        name += legend[i];
                        i++;
                    }
                    i++;    //skip ':'
                    while(legend[i] == ' ') i++;
                    settings.emplace(name, legend[i]);
                }
            }
        } else if(key == "resource_folder:") {
            ss >> folder;
            if(folder.back() != '/') folder += '/';
        }
    }
    openconfig.close();

    //loads from file
    std::ifstream openfile(folder + file);
    std::getline(openfile, line);
    float width;
    float height;
    std::stringstream ss(line);
    ss  >> width >> height;
    //resize the map
    walls.resize(static_cast<int>(height));
    for(int i = 0; i < static_cast<int>(height); i++) {
        walls.at(i).resize(static_cast<int>(width));
    }

    items.resize(static_cast<int>(height));
    for(int i = 0; i < static_cast<int>(height); i++) {
        items.at(i).resize(static_cast<int>(width));
    }
    int row = 0;
    int player = 0;
    int itemCount = 1;       //indexing from 1 cause 0 is empty
    while(std::getline(openfile, line)) {
        for(int i = 0; i < line.size(); i++) {
            try{
                if(line[i] == settings.at("wall")) {
                    walls.at(row).at(i) = true;
                } else if(line[i] == settings.at("player")) {
                    if(player == 0) {
                        player = 1;
                        playerPosition = Vector2d(row, i);
                    }
                } else if(line[i] == settings.at("item")) {
                    items.at(row).at(i) = itemCount++;
                    itemObjects.emplace_back(Item(item));
                } else if (line[i] == settings.at("finish")) {
                    finishPosition = sf::Vector2i(row, i);
                }
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
    sf::Vector2f size(Width / (float) walls.at(0).size(), Height / (float) walls.size());
    sf::RectangleShape background(sf::Vector2(Width, Height));
    background.setFillColor(sf::Color::Black);
    background.setPosition(0, 0);
    window.draw(background);

    for (int i = 0; i < walls.size(); i++) {
        for (int j = 0; j < walls.at(i).size(); j++) {
            if (walls.at(i).at(j)) {
                sf::RectangleShape rectangle;
                rectangle.setSize(size);
                rectangle.setPosition(j * size.x, i * size.y);
                rectangle.setFillColor(sf::Color::White);
                window.draw(rectangle);
            } else if (items.at(i).at(j)) {
                sf::RectangleShape rectangle;
                rectangle.setSize(size / 2.0f);
                rectangle.setPosition((j + .25f) * size.x, (i + .25f) * size.y);
                rectangle.setFillColor(sf::Color::Green);
                window.draw(rectangle);
            } else if (finishPosition.x == i && finishPosition.y == j) {
                sf::RectangleShape rectangle;
                rectangle.setSize(size / 2.0f);
                rectangle.setPosition((j + .25f) * size.x, (i + .25f) * size.y);
                rectangle.setFillColor(sf::Color::Red);
                window.draw(rectangle);
            } else if (playerPosition.x == i && playerPosition.y == j) {
                sf::RectangleShape rectangle;
                rectangle.setSize(size / 2.0f);
                rectangle.setPosition((j + .25f) * size.x, (i + .25f) * size.y);
                rectangle.setFillColor(sf::Color::Blue);
                window.draw(rectangle);
            }
        }
    }
}

bool Map::isWall(int x, int y) const {
    return walls.at(x).at(y);
}
bool Map::isWall(sf::Vector2i pos) const {
    return walls.at(pos.x).at(pos.y);
}

bool Map::isItem(int x, int y) const {
    return items.at(x).at(y) != 0;
}

bool Map::isItem(sf::Vector2i pos) const {
    return items.at(pos.x).at(pos.y) != 0;
}

bool Map::isFinish(int x, int y) const {
    return finishPosition.x == x && finishPosition.y == y;
}

bool Map::isFinish(sf::Vector2i pos) const {
    return finishPosition == pos;
}

Vector2d Map::getPlayerPosition() const {
    return playerPosition;
}

void Map::setPlayerPosition(const Vector2d &pos) {
    playerPosition = pos;
}

int Map::getItemCount() const {
    int count = 0;
    for(auto & i : items) {
        for(int j : i) {
            if(j != 0) count++;
        }
    }
    return count;
}

Item Map::getItem(int x, int y) const {
    if(items.at(x).at(y) == 0) return Item();
    return itemObjects.at(items.at(x).at(y) - 1);   //indexing from 1
}

Item Map::getItem(sf::Vector2i vec) const {
    return getItem(vec.x, vec.y);
}


