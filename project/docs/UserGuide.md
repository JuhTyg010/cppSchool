# User guide

This document provides a guide to the user interface of the application.

To run the application, you will need SFML and then need to build it:

``` cmake .```

If you don't have SFML installed, you can also build it using vcpkg:

```cmake --preset vcpkg .```

After building the cmake, you will need to build the project:

``` make```

Then run the application:

``` ./project "path_to_config"```

If you want to run the map editor, you can run:

```./editor <width> <height> "path_to_map"```

you can use config in ```src/external/config.txt``` which provides a simple demo of the application. 
For more information on how to create your own config, see the [Configuration](Configuration.md).

## Game goal
There are two variants of the game:
1. Collect all items. - You will win if you manage to collect all the items on the map.
2. Find the exit. - You will win if you manage to find the exit on the map.

## Controls
### Movement
- W - move forward
- S - move backward
- A - move left
- D - move right
### Rotation
- mouse - look around

### Action key
- E - pick up item