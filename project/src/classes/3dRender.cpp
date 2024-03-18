//
// Created by juhtyg on 23.2.24.
//

#include "../headers/3dRender.h"


Camera::Camera(sf::Vector2i windowSize, std::vector<std::vector<int>>& map, Texture& texture, Item& item) :
                windowSize(windowSize), textureSize(texture.getSize()), map(map), item(item){
    for(int i = 0; i < windowSize.x; i++){
        stripes.emplace_back(std::make_shared<Stripe>(sf::Vector2f ((float)i, (float) windowSize.y / 2), texture, false));
    }
}

Camera::Camera(int windowWidth, int windowHeight, std::vector<std::vector<int>>& map, Texture& texture, Item& item) :
        Camera(sf::Vector2i (windowWidth, windowHeight), map, texture, item){}


void Camera::render(const Vector2d &position, const Vector2d &direction, const Vector2d &plane, sf::RenderWindow &window) {
    //plane calculation
    std::vector<std::shared_ptr<VisibleObject>> toRender;
    std::vector<sf::Vector2i> items;

    //Draw the floor and ceiling

    sf::RectangleShape ceiling(sf::Vector2f(windowSize.x, windowSize.y / 2 + pitch));
    ceiling.setFillColor(sf::Color(50, 50, 50));
    ceiling.setPosition(0, 0);
    window.draw(ceiling);

    sf::RectangleShape floor(sf::Vector2f(windowSize.x, windowSize.y + std::abs(pitch)));
    floor.setFillColor(sf::Color(100, 100, 100));
    floor.setPosition(0, pitch);
    window.draw(floor);

    for(int i = 0; i < windowSize.x; i++){

        //calculate ray position and direction
        Vector2d rayDir = direction + plane * ((double) (i << 1) / windowSize.x - 1);

        //which box of the map we're in
        sf::Vector2i mapPos = sf::Vector2i((int)position.x, (int)position.y);

        //length of ray from current position to next x or y-side for more see docs
        Vector2d sideDist{};

        //length of ray from one x or y-side to next x or y-side (if rayDir.x or rayDir.y == 0 it will be infinity)
        Vector2d deltaDist = Vector2d(std::abs(1 / rayDir.x), std::abs(1 / rayDir.y));
        double perpWallDist;

        //what direction to step in x or y-direction (either +1 or -1)
        sf::Vector2i step;

        bool isHit = false;
        bool isXAxis; //was a NS(X) or a EW(Y) wall hit?

        //calculate step and initial sideDist
        if(rayDir.x < 0){
            step.x = -1;
            sideDist.x = (position.x - mapPos.x) * deltaDist.x;
        } else {
            step.x = 1;
            sideDist.x = (mapPos.x + 1.0 - position.x) * deltaDist.x;
        } if(rayDir.y < 0){
            step.y = -1;
            sideDist.y = (position.y - mapPos.y) * deltaDist.y;
        } else {
            step.y = 1;
            sideDist.y = (mapPos.y + 1.0 - position.y) * deltaDist.y;
        }

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
            //Check if ray has hit a wall
            if(map.at(mapPos.x).at(mapPos.y) > 0)     {
                if(map.at(mapPos.x).at(mapPos.y) > 4 ) {
                    //TODO: items
                    auto item = std::find(items.begin(), items.end(), mapPos);
                    if(item == items.end())     items.emplace_back(mapPos);

                } else {
                    isHit = true;
                }
            }
        }
        if(isXAxis)     perpWallDist = sideDist.x - deltaDist.x;
        else            perpWallDist = sideDist.y - deltaDist.y;

        // Calculate height of line to draw on screen
        int lineHeight = (int)(windowSize.y / perpWallDist / 2) ;   //divide by 2 to count only half of the screen

        //calculate lowest and highest pixel to fill in current Stripe
        int drawStart = lineHeight + (windowSize.y >> 1);
        if(drawStart > 4 * windowSize.y) drawStart = 4*windowSize.y;
        int drawEnd = -lineHeight + (windowSize.y >> 1);
        if(drawEnd < -4 * windowSize.y) drawEnd = -4 * windowSize.y;

        int textureNum = map[mapPos.x][mapPos.y] - 1; //to start from 0
        //TODO: Create Stripe with some texture and draw it or make buffer then draw it

        double wallX; //where exactly the wall was hit
        if(isXAxis)     wallX = position.y + perpWallDist * rayDir.y;
        else            wallX = position.x + perpWallDist * rayDir.x;
        wallX -= std::floor(wallX);

        //x coordinate on the texture
        int texX = (int)(wallX * textureSize.x);
        if(isXAxis && rayDir.x > 0) texX = (int)textureSize.x - texX - 1;
        if(!isXAxis && rayDir.y < 0) texX = (int)textureSize.x - texX - 1;

        //Update Stripe of wall is Vertical
        if(auto stripe = dynamic_cast<Stripe*>(stripes[i].get())){
            stripe->Update(texX, drawStart, drawEnd, textureNum, pitch);
            toRender.emplace_back(stripes[i]);
        } else {
            throw std::runtime_error("Stripe is not a Stripe");
        }

    }
    std::sort(toRender.begin(), toRender.end(), [](const std::shared_ptr<VisibleObject>& a, const std::shared_ptr<VisibleObject>& b){
        return a->getPosition().x < b->getPosition().x;
    }
    );

    for(auto& itemPos : items){
        //TODO: recalculate position of item to real position on the screen

        Vector2d itemVect = Vector2d(itemPos.x, itemPos.y) - position;
        double dist = std::sqrt(std::pow(itemVect.x, 2) + std::pow(itemVect.y, 2));

        //normalize itemVect
        itemVect = itemVect / dist;

        double scalar = plane.x * itemVect.x + plane.y * itemVect.y;
        //   (c << 1 / windowSize.x - 1) = scalar
        double c = (scalar + 1) * windowSize.x / 2;
        //c = std::floor(c);
        double Y = windowSize.y / dist;
        Y += windowSize.y / 2;
        Y += pitch;

        sf::Vector2f itemSize = sf::Vector2f(200, 200) /(float) dist;
        Item newItem(item);
        newItem.Update(sf::Vector2f((float) c, Y), itemSize);
        toRender.emplace_back(std::make_shared<Item>(newItem));


    }
    for(auto& object : toRender){

        object->Render(window);

    }

}