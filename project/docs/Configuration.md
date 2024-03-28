# Configuration
 
Configuration file is a text file that contains the following parameters:
- `window_size` - the size (width, height separated by space) of the window in pixels.
- `resource_folder` - the path to the folder with resources (better to use absolute).
- `map_file` - the name of the file containing map information.
- `map_legend` - the legend of the map file.
- `button_texture` - the name of the file containing the texture of the button.
- `button_texture_size` - the size (width, height) of the button texture in pixels.
- `player_texture` - the name of the file containing the texture of the player.
- `player_texture_size` - the size (width, height) of the player texture in pixels.
- `item_texture` - the name of the file containing the texture of the item.
- `item_texture_size` - the size (width, height) of the item texture in pixels.
- `wall_texture` - the name of the file containing the texture of the wall (should be twice the size to show exit).
- `wall_texture_size` - the size (width, height) of the wall texture in pixels.
- `goal` - the goal of the game (either `collect` or `escape`), but default is `escape`.

The configuration file should be in the following format:
```
window_size: 1200 800

resource_folder: /path/to/resources

map_file: map1.txt
map_legend: [wall: #, player: P, item: i, empty: ., finish: F]

button_texture: button.png
button_texture_size: 128 64

wall_texture: wall.png
wall_texture_size: 64 64

player_texture: player.png
player_texture_size: 64 64

item_texture: item.png
item_texture_size: 64 64

goal: collect
```