# Programming documentation

## Classes

### Camera  

The following document provides documentation for the `3DRender.h` header file, which contains the declaration of the `Camera` class.

#### 1. Camera Class:

The `Camera` class represents the viewpoint from which the 3D scene is rendered. 
It is responsible for calculating the orthogonal view, 
determining which objects are visible, and rendering them onto the screen. 

#### 2. Member Variables:

- `sf::Vector2i windowSize`: Represents the size of the window.
- `sf::Vector2f textureSize`: Represents the size of the texture.
- `std::vector<std::vector<int>>& map`: Reference to the map representing the environment.
- `std::vector<std::shared_ptr<Stripe>> stripes`: Vector containing the visible stripes.
- `Item& item`: Reference to the item to be rendered.
- `double pitch`: Represents the pitch angle of the camera.

#### 3. Constructor:

- `Camera(sf::Vector2i windowSize, Map& map, Texture& texture)`:
    Constructs a new Camera object with the specified window size, map, texture.
- `Camera(int windowWidth, int windowHeight, Map& map, Texture& texture)`:
    Constructs a new Camera object with the specified window width, window height, map, texture.

#### 4. Methods:

- `void render(const Vector2d& position, const Vector2d& direction, const Vector2d& plane, sf::RenderWindow& window)`: 
    Recalculates the visible stripes and items based on the camera position, direction, and plane, and draws them 
    onto the screen. Using the math explained in the Raycasting section.
- `sf::Vector2i getWindowSize() const`: Returns the size of the window.

### Button

The following document provides documentation for the `button.h` file, which contains the declaration of the `Button` class.

#### 1. Button Class:

The `Button` class represents a graphical button in a graphical user interface (GUI). It allows users to interact with the program by clicking on it.

#### 2. Constructor:

- `Button(Texture& texture, sf::Vector2f position, sf::Vector2f size, const std::string& text, sf::Font& font, sf::Color color)`:
  Constructs a new Button object with the specified texture, position, size, text, font, and color. The button's text is centered and positioned based on its size and font.

#### 3. Methods:

- `void Render(sf::RenderWindow &window)`:
  Renders the button and its text onto the given SFML RenderWindow.

- `bool isClicked(sf::Vector2i mousePosition)`:
  Checks if the button is clicked based on the given mouse position. Returns true if the mouse position is within the boundaries of the button's sprite, otherwise false.


### Item

The following document provides documentation for the `Item` class declared in the `Item.h` header file.

#### 1. Item Class:

The `Item` class represents an item in the game world. It inherits from the `VisibleObject` class.

#### 2. Constructors:

- `Item(Texture &texture, sf::Vector2f position, sf::Vector2f size, std::function<void()> OnAction = [](){})`:
  Constructs a new Item object with the specified texture, position, size and on action function.

- `Item(const Item &other)`:
  Copy constructor to create a new Item object by copying another Item object.

#### 3. Methods:

- `void Update(float deltaTime)`:
  Is overridden from the `VisibleObject` class. Please don't use.

- `void Update(sf::Vector2f position, sf::Vector2f size)`:
  Updates the position and size of the item.

- `void OnAction() `:
  Calls the on action function of the item.

- `Item copy() const`:
  Creates a copy of the current Item object and returns it.


### Map

The following document provides documentation for the `Map` class declared in the `map.h` header file.

#### 1. Map Class:

The `Map` class represents the game map in a 3D game environment. 
It is responsible for loading the map from a configuration file and rendering it 
in a top-down view.

#### 2. Constructor:

- `Map(const std::string& config, float Width, float Height)`:
  Constructs a new Map object by loading map data from the specified [configuration file](Configuration.md)
    and setting the width, height, and reference to the map. For every configuration , the map class make it universal.
    Makes bool map with true on walls and false on empty space. And other int map with items which are stored in array.
    Also sets the finish and player position.

#### 3. Methods:

- `void render(sf::RenderWindow& window)`:
  Renders the map in a top-down view onto the specified SFML RenderWindow.

- `int getItemCount() const`:
  Iterates through the map and returns the number of items present on the map. 
  Returns the number of items present on the map.

- `Item getItem(int x, int y) const` & `Item getItem(sf::Vector2i vec) const`:
  Returns the item at the specified position on the map.

- `bool isWall(int x, int y) const` & `bool isWall(sf::Vector2i vec) const`:
  Checks if the specified position on the map is a wall.

- `bool isFinish(int x, int y) const` & `bool isFinish(sf::Vector2i vec) const`:
  Checks if the specified position on the map is the finish position.

- `Vector2d getPlayerPosition() const`:
  Returns the player's position on the map.

- `void setPlayerPosition(Vector2d position)`:
  Sets the player's position on the map.

- `bool isItem(int x, int y) const` & `bool isItem(sf::Vector2i vec) const`:
  Checks if the specified position on the map contains an item.

- `void removeItem(int x, int y)` & `void removeItem(sf::Vector2i vec)`:
  Removes the item at the specified position on the map.

### Player

The following document provides documentation for the `Player` class declared in the `Player.h` header file.

#### 1. Player Class:

The `Player` class represents the player character in a 3D game environment. 
It handles player movement, rotation, and rendering through the camera.

#### 2. Member Variables:

- `bool isFinishable`: Specifies if the player's goal is only to collect items or escape.

- `float sideSpeed`: Represents the side movement speed of the player.
- `float speed`: Represents the forward/backward movement speed of the player.
- `float rotationSpeed`: Represents the rotation speed of the player.

- `Vector2d direction`: Represents the direction the player is facing.
- `Vector2d plane`: Represents the plane of the player's view (for camera).
- `sf::Vector2i lastMousePos`: Represents the last recorded mouse position.
- `sf::Vector2i windowPosition`: Represents the position of the player's window.
- `std::unique_ptr<Camera> camera`: Pointer to the camera representing the player's view.
- `Map& map`: Reference to the map object.

#### 3. Constructors:

- `Player(Texture& texture, sf::Vector2i windowSize, Map& map, bool isFinishable = false)`:
  Constructs a new Player object with the specified texture, window size, map, and goal status.

#### 4. Methods:

- `void Update(float dt)`: Updates the player's position and checks for inputs.
- `void Render(sf::RenderWindow &window)`: Renders the player and the camera (player's view) onto the specified SFML RenderWindow.

#### 5. Private Methods:

- `bool isLegalPosition(const Vector2d& position)`: Checks if the given position on the map is accessible (no wall).
- `void move(float dt, float speed, float acceleration)`: Handles input for player movement.
- `void rotate(float dt, float rotationSpeed, float rotAccel)`: Handles input for player rotation.


### spriteRenderer

The following document provides documentation for the `spriteRenderer` class declared in the `spriteRenderer.h` header file.

#### 1. spriteRenderer Class:

The `spriteRenderer` class represents a sprite renderer object responsible for rendering sprites onto an SFML RenderWindow.

#### 2. Member Variables:

- `Texture& texture`: Reference to the texture of the sprite.
- `sf::IntRect rectSourceSprite`: Integer rectangle representing the source sprite within the texture.
- `sf::Vector2f currentFrame`: Vector representing the current frame position of the sprite.

#### 3. Constructors:

- `spriteRenderer(Texture& texture, sf::Vector2f position, sf::Vector2f size)`:
  Constructs a new spriteRenderer object with the specified texture, position, and size.

- `spriteRenderer(const spriteRenderer& other)`:
  Copy constructor to create a new spriteRenderer object by copying another spriteRenderer object.

#### 4. Methods:

- `void nextFrame()`: Calculates the position of the next frame on the right side of the texture (circular).
- `void prevFrame()`: Calculates the position of the previous frame on the left side of the texture (circular).
- `void nextAnimation()`: Advances to the next animation line (circular).
- `void prevAnimation()`: Goes back to the previous animation line (circular).
- `void Render(sf::RenderWindow &window)`: Renders the sprite onto the specified SFML RenderWindow.
- `void setOrigin(sf::Vector2f origin)`: Sets the origin of the sprite.
- `void setPosition(sf::Vector2f position)`: Sets the position of the sprite.
- `void setTextureRect(sf::IntRect rect)`: Sets the texture rectangle of the sprite.
- `void setScale(sf::Vector2f scale_)`: Sets the scale of the sprite.
- `sf::Vector2f getCurrentFrame()`: Returns the current frame position of the sprite (representing the animation and frame in it).
- `sf::Vector2f getTextureSize()`: Returns the size of the texture.


### Stripe

The following document provides documentation for the `Stripe` class declared in the `Stripe.h` header file.

#### 1. Stripe Class:

The `Stripe` class represents a stripe in a 3D environment, used for rendering walls or other textured surfaces.

#### 2. Member Variables:

- `float scale`: Scale of the stripe.
- `bool isHorizontal`: Specifies whether the stripe is horizontal or vertical.

#### 3. Constructors:

- `Stripe(sf::Vector2f position, Texture& texture, bool isHorizontal)`:
  Constructs a new Stripe object with the specified position, texture, and orientation.

- `Stripe(const Stripe& other)`:
  Copy constructor to create a new Stripe object by copying another Stripe object.

#### 4. Methods:

- `void Update(int dist, int drawStart, int drawEnd, int textureNum, float pitch)`:
  Updates the stripe's distance, setting scale based on drawStart and drawEnd, texture number, and pitch angle.

#### 5. Private Methods:

- `void rescale(int drawStart, int drawEnd)`:
  Calculates the value of the scale based on the full size of the stripe.


### UIText

The following document provides documentation for the `UIText` class declared in the `UIText.h` header file.

#### 1. UIText Class:

The `UIText` class represents a user interface text element in a 3D game environment.

#### 2. Member Variables:

- `sf::Text text`: SFML Text object representing the text.
- `sf::Font font`: SFML Font object representing the font used for the text.

#### 3. Constructor:

- `UIText(const std::string& text, const sf::Font& font, const sf::Vector2f& position, const sf::Color& color, unsigned int size)`:
  Constructs a new UIText object with the specified text, font, position, color, and size.

#### 4. Methods:

- `void UpdateText(const std::string& text)`: Changes the text of the object.
- `void Render(sf::RenderWindow& window)`: Renders the text onto the specified SFML RenderWindow.


### VisibleObject

The following document provides documentation for the `VisibleObject` class declared in the `VisibleObject.h` header file.

#### 1. VisibleObject Class:

The `VisibleObject` class represents a visible object in a 3D game environment. It serves as a base class for objects that are rendered on the screen.

#### 2. Member Variables:

- `std::unique_ptr<spriteRenderer> sprite`: Unique pointer to a spriteRenderer object representing the visual representation of the object.
- `sf::Vector2f position`: Vector representing the position of the object.
- `sf::Vector2f size`: Vector representing the size of the object.

#### 3. Constructors:

- `VisibleObject(Texture& texture, sf::Vector2f position, sf::Vector2f size)`:
  Constructs a new VisibleObject object with the specified texture, position, and size.

- `VisibleObject(const VisibleObject& other)`:
  Copy constructor to create a new VisibleObject object by copying another VisibleObject object.

#### 4. Methods:

- `virtual void Update(float dt) = 0`: Pure virtual method to update the object's state.
- `virtual void Render(sf::RenderWindow& window)`: Renders the object onto the specified SFML RenderWindow.
- `virtual sf::Vector2f getScale()`: Returns the scale of the object's sprite.
- `virtual sf::Vector2f getPosition()`: Returns the position of the object.
- `virtual void setPosition(sf::Vector2f position)`: Sets the position of the object.

#### 5. Destructor:

- `virtual ~VisibleObject() = default;`: Virtual destructor to ensure proper destruction of derived classes.


### Utils

The following document provides documentation for the `Utils.h` header file.


#### 3. Class: MyMath

- `static double DegToRad(double deg)`: Converts degrees to radians.
- `static double RadToDeg(double rad)`: Converts radians to degrees.

#### 4. Structs:

- `struct Vector2d`: Represents a 2D vector with double precision.

- `struct Texture`: Represents texture information.

#### 5. Texture Constructors:

- `Texture(std::string name,const std::string& path, sf::Vector2f size, sf::Vector2f matrix)`: Constructs a new Texture object with the specified parameters.
- `Texture(const Texture& other)`: Copy constructor to create a new Texture object by copying another Texture object.

#### 6. Texture Methods:

- `const sf::Texture & getTexture()`: Returns the texture.
- `const sf::Vector2f& getSize()`: Returns the size of the texture.
- `const sf::Vector2f& getMatrix()`: Returns the matrix of the texture.
- `const std::string& getName()`: Returns the name of the texture.

#### 7. Functions:

- `const Texture& getTextureByName(const std::string& name, std::vector<Texture>& textures)`: Returns the texture with the specified name from a vector of textures.

- `double getDistance(sf::Vector2f vec1, sf::Vector2f vec2)`: Returns the Euclidean distance between two vectors.

- `template <typename T> T divide(T a, T b)`: Divides two vectors or a vector and a number.

- `template <typename T, typename C> T divide(T a, C b)`: Divides a vector by a number.


### Main

The following document provides documentation for the `main.cpp` file.

#### 1. Function: loadConfig

- `bool loadConfig(const std::string& path, int& width, int& height, std::vector<Texture>& textures, sf::Font& font)`: 
    Loads [configuration](Configuration.md) from a file and initializes window size, textures, and font.

#### 2. Function: main

- `int main(int argc, char *argv[])`: The main function of the program.

##### 2.1 Initialization:

- Loads configuration from the provided file using `loadConfig`.
- Creates an SFML RenderWindow with the specified window size.
- Initializes map, player, item, buttons, and UI texts.

##### 2.2 Game Loop:

- Polls events and updates the game state.
- Updates the player's position and renders the scene.
- If the game is paused, renders the pause menu and handles button clicks.
- Displays the window and continues the loop until the window is closed.


### Raycasting

The basic idea of raycasting is as follows:the map is a 2D square grid,
and each square can either be a wall or empty space. The player is at a certain position and facing a certain direction.

I chose to use perpendicular projection, which is a simple and efficient way to render 3D scenes.
The idea is that view is represented by a direction and plane vector, and the camera renders the scene by casting rays
from the player's position to the walls of the map. 

The plane must be perpendicular to the direction vector. based on ration we get the width of the view.

For each ray you need to check if it hits the wall,
and if it does, calculate the distance to the wall and the texture to render.
Therefor I use simple fact that the map is a square grid, so I check if its wall only
if the ray crosses the grid line.

![grid checking](https://lodev.org/cgtutor/images/raycasthit.gif)

When ray hits the wall I calculate the distance to the wall and the texture to render.
For this is used the DDA (Digital Differential Analysis) algorithm.  DDA is a fast algorithm 
typically used on square grids to find which squares a line hits 
(for example to draw a line on a screen, which is a grid of square pixels). 
So we can also use it to find which squares of the map our ray hits, and stop the algorithm 
once a square that is a wall is hit.

We also need to render items if they are in the view. to do this we need to calculate the distance 
to the item and the texture to render. Project the sprite on the camera plane 
(in 2D): subtract the player position from the sprite position, then multiply 
the result with the inverse of the 2x2 camera matrix

$$
\begin{pmatrix}
planeX & dirX \\ 
planeY & dirY
\end{pmatrix}
$$

$$ 
\frac {1} {(planeX*dirY-dirX*planeY)} * \begin{pmatrix} dirY & -dirX \\ -planeY & planeX \end{pmatrix}
$$



Then you get the X and Y coordinate of the sprite in camera space, where Y is
the depth inside the screen (in a true 3D engine, Z is the depth).
To project it on screen, divide X 
through the depth, and then translate and scale it so that it's in pixel coordinates.

And then we sort items and stripes by distance and render them.
