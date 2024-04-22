//
// Created by juhtyg on 23.2.24.
//

#include "../headers/3dRender.h"


Camera::Camera(sf::Vector2i windowSize, Map& map, Texture& texture, const Vector2d& direction, const Vector2d& plane) :
                windowSize(windowSize), textureSize(texture.getSize()), map(map), direction(direction), plane(plane){
    for(int i = 0; i < windowSize.x; i++){
        stripes.emplace_back(std::make_shared<Stripe>(sf::Vector2f ((float)i, (float) windowSize.y / 2), texture, false));
    }
}

Camera::Camera(int windowWidth, int windowHeight, Map& map, Texture& texture, const Vector2d& direction, const Vector2d& plane) :
        Camera(sf::Vector2i (windowWidth, windowHeight), map, texture, direction, plane){}


void Camera::render(sf::RenderWindow &window) {

    //update position
    position = map.getPlayerPosition();
    std::vector<std::shared_ptr<VisibleObject>> toRender;
    std::vector<sf::Vector2i> items;

    //Draw the floor and ceiling
    sf::RectangleShape ceiling(sf::Vector2f((float)windowSize.x, (float) ((windowSize.y >> 1) + pitch)));
    ceiling.setFillColor(sf::Color(50, 50, 50));
    ceiling.setPosition(0, 0);
    window.draw(ceiling);

    sf::RectangleShape floor(sf::Vector2f((float)windowSize.x, (float)(windowSize.y + std::abs(pitch))));
    floor.setFillColor(sf::Color(100, 100, 100));
    floor.setPosition(0, (float)pitch);
    window.draw(floor);


    //which box of the map we're in
    sf::Vector2i mapPos = sf::Vector2i((int)position.x, (int)position.y);
    if(map.isItem(mapPos)){
        auto it = std::find(items.begin(), items.end(), mapPos);
        if(it == items.end())     items.emplace_back(mapPos);
    }


    for(int i = 0; i < windowSize.x; i++){
        updateStripe(i, items, mapPos);
        toRender.emplace_back(stripes[i]);
    }

    addItems(items, toRender);

    std::ranges::sort(toRender.begin(), toRender.end(), [](const std::shared_ptr<VisibleObject>& a, const std::shared_ptr<VisibleObject>& b){
        return a->distance > b->distance;
    });

    for(auto& object : toRender){
        object->Render(window);
    }
}

void Camera::addItems(std::vector <sf::Vector2i> &items, std::vector <std::shared_ptr<VisibleObject>> &toRender) {
    for(auto& itemPos : items){

        Vector2d itemVect = Vector2d(itemPos.x + .5, itemPos.y + .5) - position;//+.5 to get the center of the square
        double dist = std::sqrt(std::pow(itemVect.x, 2) + std::pow(itemVect.y, 2));

        double invDet = 1 / (plane.x * direction.y - direction.x * plane.y); //required for correct matrix multiplication

        sf::Vector2f transform = sf::Vector2f(direction.y * itemVect.x - direction.x * itemVect.y,
                                              -plane.y * itemVect.x + plane.x * itemVect.y) * (float) invDet; //this is actually the depth inside the screen, that what Z is in 3D

        float itemScreenX = (windowSize.x >> 1) * (1 + transform.x / transform.y);
        float itemScreenY = (windowSize.y / 2 - 100) / dist + pitch; // -100 to be 100 above the ground


        sf::Vector2f itemSize = sf::Vector2f(200, 200) /(float) dist;
        Item newItem = this->map.getItem(itemPos);
        newItem.Update(sf::Vector2f((float) itemScreenX, itemScreenY), itemSize);
        toRender.emplace_back(std::make_shared<Item>(newItem));
        toRender.back()->distance = dist;   //if set before it won't be sorted correctly

    }
}

bool Camera::DigitalDifferentialAnalyzer(const Vector2d &rayDir, const Vector2d &deltaDist, double &perpWallDist, std::vector<sf::Vector2i> &items, sf::Vector2i &mapPos) {
    bool isXAxis;
    sf::Vector2i step;
    //length of ray from current position to next x or y-side for more see docs
    Vector2d sideDist;

    if(rayDir.x < 0){
        step.x = -1;
        sideDist.x = (position.x - mapPos.x) * deltaDist.x;
    } else {
        step.x = 1;
        sideDist.x = (mapPos.x + 1 - position.x) * deltaDist.x;
    } if(rayDir.y < 0){
        step.y = -1;
        sideDist.y = (position.y - mapPos.y) * deltaDist.y;
    } else {
        step.y = 1;
        sideDist.y = (mapPos.y + 1 - position.y) * deltaDist.y;
    }

    bool isHit = false;
    //perform Digital Differential Analysis
    while(!isHit){
        //jump to next map square, OR in x-direction, OR in y-direction
        if(sideDist.x < sideDist.y){
            sideDist.x += deltaDist.x;
            mapPos.x += step.x;
            isXAxis = true;
        } else {
            sideDist.y += deltaDist.y;
            mapPos.y += step.y;
            isXAxis = false;
        }
        try{
            //Check if ray has hit a wall
            if(map.isItem(mapPos)) {
                auto it = std::find(items.begin(), items.end(), mapPos);
                if(it == items.end())     items.emplace_back(mapPos);
            }

            isHit = map.isWall(mapPos) || map.isFinish(mapPos); //finish is also a wall
        } catch (std::out_of_range& e){
            isHit = true;
        }

    }
    if(isXAxis)     perpWallDist = sideDist.x - deltaDist.x;
    else            perpWallDist = sideDist.y - deltaDist.y;

    return isXAxis;
}

Stripe Camera::updateStripe(int index, std::vector<sf::Vector2i> &items, sf::Vector2i mapPos) {

    Vector2d rayDir = direction + plane * ((double) (index << 1) / windowSize.x - 1);

    //length of ray from one x or y-side to next x or y-side (if rayDir.x or rayDir.y == 0 it will be infinity)
    Vector2d deltaDist = Vector2d(std::abs(1 / rayDir.x), std::abs(1 / rayDir.y));
    double perpWallDist;

    bool isXAxis = DigitalDifferentialAnalyzer(rayDir, deltaDist, perpWallDist, items, mapPos);

    // Calculate height of line to draw on screen (a/b)/c = a/(b*c)
    int lineHeight = (int)(windowSize.y / (2 * perpWallDist));

    //calculate lowest and highest pixel to fill in current Stripe
    int drawStart = lineHeight + (windowSize.y >> 1);
    if(drawStart > 4 * windowSize.y) drawStart = 4*windowSize.y;
    int drawEnd = -lineHeight + (windowSize.y >> 1);
    if(drawEnd < -4 * windowSize.y) drawEnd = -4 * windowSize.y;

    int textureNum = map.isFinish(mapPos) ? 1 : 0; //to start from 0

    double wallX; //where exactly the wall was hit
    if(isXAxis)     wallX = position.y + perpWallDist * rayDir.y;
    else            wallX = position.x + perpWallDist * rayDir.x;
    wallX -= std::floor(wallX);

    //x coordinate on the texture
    int texX = (int)(wallX * textureSize.x);
    if(isXAxis && rayDir.x > 0) texX = (int)textureSize.x - texX - 1;
    if(!isXAxis && rayDir.y < 0) texX = (int)textureSize.x - texX - 1;

    if(auto stripe = dynamic_cast<Stripe*>(stripes[index].get())){
        stripe->Update(texX, drawStart, drawEnd, textureNum, (float) pitch);
        stripes[index]->distance = perpWallDist;
        return *stripe;
    } else {
        throw std::runtime_error("Stripe is not a Stripe");
    }
}