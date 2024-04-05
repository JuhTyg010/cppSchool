#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>

const std::string  legend = "map_legend: [wall: #, player: P, item: i, empty: ., finish: F]";

using grid_t = std::vector<std::vector<int>>;

// Function to save drawn image as a top-down map
void saveMapToFile(const grid_t& grid, int width, int height, std::string filename) {
    std::ofstream outfile(filename);
    outfile << width << " " << height << std::endl;
    for (int y(0); y < height; ++y) {
        for (int x(0); x < width; ++x) {
            switch (grid[x][y]) {
                case 1:
                    outfile << "#";
                    break;
                case 2:
                    outfile << "F";
                    break;
                case 3:
                    outfile << "P";
                    break;
                case 4:
                    outfile << "i";
                    break;
                default:
                    outfile << ".";
                    break;
            }
        }
        outfile << std::endl;
    }
    outfile.close();
}

void generateConfig(std::string mapFile){
    std::filesystem::path fullPath(mapFile);
    std::string folder = fullPath.parent_path().string();
    std::string mapFileName = fullPath.filename().string();
    std::string configName = "config_"+mapFileName;
    if(std::filesystem::exists(folder + "/" + configName)) return;
    std::ofstream outStream(folder + "/" + configName);
    std::cout << configName + folder + mapFileName << std::endl;

    outStream << "window_size: 1200 800" << std::endl;
    outStream << "resource_folder: ." << std::endl;
    outStream << "map_file: " + mapFileName << std::endl;
    outStream << legend << std::endl;

    outStream.close();

}

grid_t loadMapFromFile(std::string filename, int width_, int height_) {

    std::ifstream(infile);
    grid_t grid(width_, std::vector<int>(height_, 0));
    try {
        infile.open(filename);
        int width, height;
        infile >> width >> height;
        if(width != width_ || height != height_) {
            std::cerr << "Invalid or none map file" << std::endl;
            return grid;
        }

        std::string line;
        std::getline(infile, line);
        for (int y(0); y < height; ++y) {
            std::getline(infile, line);
            for (int x(0); x < width; ++x) {
                switch (line[x]) {
                    case '#':
                        grid[x][y] = 1;
                        break;
                    case 'F':
                        grid[x][y] = 2;
                        break;
                    case 'P':
                        grid[x][y] = 3;
                        break;
                    case 'i':
                        grid[x][y] = 4;
                        break;
                    default:
                        grid[x][y] = 0;
                        break;
                }
            }
        }
        infile.close();
        return grid;
    } catch (std::exception& e){
        std::cout << "File not found, creating new one" << std::endl;
        return grid;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <width> <height> <output_file>" << std::endl;
        return 1;
    }
    int width, height;
    try {
         width = std::stoi(argv[1]);
         height = std::stoi(argv[2]);
    } catch (std::exception e){
        std::cerr << "Invalid map size" << std::endl;
        return 1;
    }
    if(width <= 0 || height <= 0) {
        std::cerr << "Invalid map size" << std::endl;
        return 1;
    }
    std::string filename = argv[3];

    sf::Color backgroundColor = sf::Color::Black;
    sf::Color wallColor = sf::Color::White;
    sf::Color itemColor = sf::Color::Red;
    sf::Color playerColor = sf::Color::Green;
    sf::Color finishColor = sf::Color::Blue;
    sf::Color windowColor = sf::Color(69, 63, 120);

    sf::Vector2f windowSize(800, 600);
    sf::Vector2f drawAreaSize(600, 500);
    sf::Vector2f drawAreaPosition(20, 20);

    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Grid Drawing");


    sf::RectangleShape drawArea(drawAreaSize);
    drawArea.setPosition(drawAreaPosition);
    drawArea.setFillColor(backgroundColor);

    std::string message = " wall press 1 \n finish press 2 \n player press 3 \n item press 4";
    sf::Font font;
    font.loadFromFile("./Utils/Montserrat-Regular.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(drawAreaSize.x + drawAreaPosition.x, drawAreaPosition.y);

    // Create grid
    grid_t grid = loadMapFromFile(filename, width, height);

    sf::Vector2f cellSize(drawArea.getSize().x / width, drawArea.getSize().y / height);
    bool isDrawing = false;
    bool isErasing = false;
    bool playerPlaced = false;
    bool finishPlaced = false;
    // 1 - wall, 2 - finish, 3 - player, 4 - item
    int selectedValue = 1;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1) {
                    selectedValue = 1;
                }
                else if (event.key.code == sf::Keyboard::Num2) {
                    selectedValue = 2;
                }
                else if (event.key.code == sf::Keyboard::Num3) {
                    selectedValue = 3;
                }
                else if (event.key.code == sf::Keyboard::Num4) {
                    selectedValue = 4;
                }
            }

            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isDrawing = true;
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    isErasing = true;
                }
            }

            else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isDrawing = false;
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    isErasing = false;
                }
            }


            if (isDrawing) {
                    // Get the position of the mouse cursor
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Calculate the position of the cell in the grid
                    int x = (mousePos.x - drawAreaPosition.x) / cellSize.x;
                    int y = (mousePos.y - drawAreaPosition.y) / cellSize.y;

                    try{
                        if(selectedValue == 3){
                            if(!playerPlaced) {
                                if(grid.at(x).at(y) == 2) finishPlaced = false;
                                grid.at(x).at(y) = selectedValue;
                                playerPlaced = true;
                            }
                        } else if(selectedValue == 2){
                            if(!finishPlaced){
                                if(grid.at(x).at(y) == 3) playerPlaced = false;
                                grid.at(x).at(y) = selectedValue;
                                finishPlaced = true;
                            }
                        } else {
                            if(grid.at(x).at(y) == 3) playerPlaced = false;
                            if(grid.at(x).at(y) == 2) finishPlaced = false;
                            grid.at(x).at(y) = selectedValue;
                        }
                    } catch (std::out_of_range& e) {
                        continue;
                    }
                } else if (isErasing) {
                    // Get the position of the mouse cursor
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Calculate the position of the cell in the grid
                    int x = (mousePos.x - drawAreaPosition.x) / cellSize.x;
                    int y = (mousePos.y - drawAreaPosition.y) / cellSize.y;

                    try {
                        if(grid.at(x).at(y) == 3) playerPlaced = false;
                        if(grid.at(x).at(y) == 2) finishPlaced = false;
                        grid.at(x).at(y) = 0;
                    } catch (std::out_of_range &e) {
                        continue;
                    }
                }

        }

        window.clear(windowColor);
        window.draw(drawArea);
        window.draw(text);

        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                if (grid[x][y] != 0) {
                    sf::RectangleShape cell(cellSize);
                    cell.setPosition(x * cellSize.x + drawAreaPosition.x, y * cellSize.y + drawAreaPosition.y);
                    switch (grid[x][y]) {
                        case 1:
                            cell.setFillColor(wallColor);
                            break;
                        case 2:
                            cell.setFillColor(finishColor);
                            break;
                        case 3:
                            cell.setFillColor(playerColor);
                            break;
                        case 4:
                            cell.setFillColor(itemColor);
                            break;
                    }
                    window.draw(cell);
                }
            }
        }
        window.display();
    }

    // Save drawn image as a top-down map
    saveMapToFile(grid, width, height, filename);
    generateConfig(filename);

    return 0;
}
