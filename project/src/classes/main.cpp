#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window.hpp>
#include "../headers/Player.h"
#include "../headers/map.h"
#include "../headers/button.h"
#include <algorithm>



void loadConfig(const std::string& path, int& width, int& height, std::vector<Texture>& textures, sf::Font& font){
    std::ifstream openfile(path);
    std::string line;
    std::string value;
    std::string resourceFolder;
    std::string fontFile;
    std::map<std::string, std::string> texturePaths;
    std::map<std::string, sf::Vector2f> textureSizes;

    try {

        while (std::getline(openfile, line)) {
            std::string key;
            std::stringstream ss(line);
            ss >> key;

            if (key == "window_size:") {
                ss >> width >> height;

            } else if (key == "button_texture:") {
                ss >> value;
                texturePaths.try_emplace("button", value);

            } else if (key == "wall_texture:") {
                ss >> value;
                texturePaths.try_emplace("wall", value);
            } else if (key == "player_texture:") {
                ss >> value;
                texturePaths.try_emplace("player", value);
            } else if (key == "item_texture:") {
                ss >> value;
                texturePaths.try_emplace("item", value);
            } else if (key == "button_texture_size:") {
                float x, y;
                ss >> x >> y;
                textureSizes.try_emplace("button", sf::Vector2f(x, y));
            } else if (key == "wall_texture_size:") {
                float x, y;
                ss >> x >> y;
                textureSizes.try_emplace("wall", sf::Vector2f(x, y));
            } else if (key == "player_texture_size:") {
                float x, y;
                ss >> x >> y;
                textureSizes.try_emplace("player", sf::Vector2f(x, y));
            } else if (key == "item_texture_size:") {
                float x, y;
                ss >> x >> y;
                textureSizes.try_emplace("item", sf::Vector2f(x, y));
            } else if (key == "resource_folder:") {
                ss >> resourceFolder;
                if (resourceFolder.back() != '/') resourceFolder += '/';
            } else if(key == "font_file:"){
                ss >> value;
                fontFile = value;
            }
        }
        if(resourceFolder.empty()) throw std::runtime_error("Resource folder not specified");
        for (auto &[key, val]: texturePaths) {
            textures.emplace_back(key, resourceFolder + val, textureSizes[key], sf::Vector2f(1, 1));
            std::cout << "Texture loaded: " << resourceFolder + val << std::endl;
        }
        font.loadFromFile(resourceFolder + fontFile);
    } catch (std::exception& e) {
        std::cerr << "Error while loading from config: " << e.what() << std::endl;
        exit (1);
    }
}


int main(int argc, char *argv[]) {
    std::cout << std::filesystem::current_path().string();
    std::vector<Texture> textures;
    std::vector<std::vector<int>> map_data;
    sf::Font font;

    int WIDTH, HEIGHT;
    if(argc < 2){
        std::cerr << "No config file provided" << std::endl;
        return 1;
    }
    loadConfig(argv[1], WIDTH, HEIGHT, textures, font);
    std::cout << "Config loaded" << std::endl;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Working Title");
    std::cout << "Window size: " << WIDTH << "x" << HEIGHT << std::endl;
    window.setVerticalSyncEnabled(true);
    Map map( argv[1],WIDTH/3 , HEIGHT/4, map_data);
    std::cout << "Map loaded" << std::endl;
    Vector2d pos;
    /*if(auto result = std::find_if(map_data.begin(), map_data.end(),
                                  [](std::vector<int> a) {return std::find(a.begin(), a.end(), 2) == a.end(); }); result == map_data.end()){
        pos = Vector2d(map_data.end()-result, std::find (result->begin(), result->end(), 2) - result->begin());

    }*/
    for(int i = 0; i < map_data.size(); i++){
        for(int j = 0; j < map_data[i].size(); j++){
            if(map_data[i][j] == 2){
                pos = Vector2d(i, j);
                std::cout << "Player position: " << i << " " << j << std::endl;
            }
        }
    }
    sf::Mouse::setPosition(sf::Vector2i(WIDTH/2, HEIGHT/2) + window.getPosition());

    auto playerTex = getTextureByName("wall", textures);
    auto itemTex = getTextureByName("item", textures);
    Item item(itemTex, sf::Vector2f(200, 200), sf::Vector2f(1, 1));

    Player player(playerTex, pos, sf::Vector2i(WIDTH, HEIGHT), map_data, item);
    std::cout << "Player position: " << pos.x << " " << pos.y << std::endl;



    auto buttonTex = getTextureByName("button", textures);
    Button resume(buttonTex, sf::Vector2f((float)WIDTH/2, (float)HEIGHT/2 -100), sf::Vector2f(200, 100), "Resume", font, sf::Color::Black);
    Button quit(buttonTex, sf::Vector2f((float)WIDTH/2, (float)HEIGHT/2+100), sf::Vector2f(200, 100), "Quit", font, sf::Color::Black);

    spriteRenderer renderer(playerTex, sf::Vector2f((float)WIDTH/2, (float)HEIGHT/2), sf::Vector2f(64, 64));

    sf::Clock clock;
    bool isPaused = false;

    std::cout << "here" << std::endl;
    while (window.isOpen()) {
        sf::Event event{};
        sf::Time dt = clock.restart();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            isPaused = true;
        }
        if(!isPaused){
            player.Update(dt.asSeconds());
            window.setMouseCursorVisible(false);
            window.clear();
            player.Render(window);
            map.render(window);
        } else {
            window.setMouseCursorVisible(true);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(resume.isClicked(sf::Mouse::getPosition(window)))        isPaused = false;
                else if(quit.isClicked(sf::Mouse::getPosition(window)))     window.close();
            }
            window.clear();
            player.Render(window);
            resume.Render(window);
            quit.Render(window);
        }

        window.display();

    }

    return 0;
}


