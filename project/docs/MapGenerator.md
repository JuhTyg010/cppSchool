# Map generator

To make it easier to create maps there is small sub-program in which you can generate a map.

## User guide

To run the application, you will need vcpkg and then need to build it:

``` cmake .```

Then run the application:

``` ./generator <widthOfMap> <heightOfMap> "nameToStore"```

It opens the window in which we can Draw the map, you can draw in black window.
Default brush is wall (1) you can switch between the brushes via nums:
1 - wall
2 - finish
3 - player
4 - item

To draw use mouse left button to erase mouse right button.

if you specify valid file it will recognise it and opens its content, otherwise file is created.
File is saved on exit from map, and if config file isn't created for this map it will generate one.


## Developer guide

This documentation provides an overview of the provided C++ code for generating and manipulating a 2D grid-based map using SFML library for graphics rendering.


## Global Constants

- `legend`: Describes the legend for the map symbols used to represent different elements in the grid.

## Type Definitions

- `grid_t`: Alias for a 2D vector representing the grid.

## Functions

1. `saveMapToFile(const grid_t& grid, int width, int height, std::string filename)`: Saves the drawn image as a top-down map to a file.

2. `generateConfig(std::string mapFile)`: Generates a configuration file based on the provided map file. More in [Configuration](Configuration.md).

3. `loadMapFromFile(std::string filename, int width_, int height_)`: Loads a map from a file.

4. `main(int argc, char* argv[])`: Entry point of the program. It initializes the SFML window, handles user input, draws the grid, and saves the map to a file.

## Main Function Flow

1. Parses command-line arguments to obtain the width, height, and output filename for the map.
2. Initializes colors for different map elements.
3. Creates the SFML window with specified dimensions.
4. Sets up drawing area and text for instructions.
5. Loads the map from the specified file.
6. Enters the main event loop to handle user input and drawing.
7. Draws grid cells based on map contents and selected value.
8. Updates the window display and continues looping until the window is closed.
9. Saves the drawn map to a file and generates a configuration file based on the map filename.

This code provides functionality to draw and manipulate a 2D grid-based map interactively using SFML, allowing users to specify different elements such as walls, players, items, and the finish line.
