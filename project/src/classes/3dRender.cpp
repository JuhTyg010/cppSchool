//
// Created by juhtyg on 23.2.24.
//

#include "../headers/3dRender.h"


Camera::Camera(sf::Vector2i windowSize, sf::Vector2u textureSize, std::vector<std::vector<int>>& map, sf::Texture& texture):
                windowSize(windowSize), textureSize(textureSize), map(map){
    for(int i = 0; i < windowSize.x; i++){
        stripes.push_back(std::make_unique<Stripe>(sf::Vector2f ((float)i, (float) windowSize.y / 2), textureSize.y, sf::Vector2f(1, 1), texture));
    }
}

Camera::Camera(int windowWidth, int windowHeight, sf::Vector2u textureSize,
               std::vector<std::vector<int>>& map, sf::Texture& texture) :
         windowSize(windowWidth, windowHeight), textureSize(textureSize), map(map) {
    for(int i = 0; i < windowSize.x; i++){
        stripes.push_back(std::make_unique<Stripe>(sf::Vector2f((float)i, (float) windowHeight / 2), textureSize.y, sf::Vector2f(1, 1), texture));
    }
}

Camera::Camera(const Camera &other) :  windowSize(other.windowSize), textureSize(other.textureSize), map(other.map){
    for(int i = 0; i < windowSize.x; i++){
        stripes.push_back(std::make_unique<Stripe>(*other.stripes[i]));
    }
}

void Camera::render(const Vector2d &position, const Vector2d &direction, const Vector2d &plane, sf::RenderWindow &window) {
    //plane calculation

    for(int i = 0; i < windowSize.x; i++){
        //calculate ray position and direction
        double cameraX = 2 * i / double(windowSize.x) - 1;

        Vector2d rayDir = direction + plane * cameraX;

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
                    //TODO: item pickup
                } else {
                    isHit = true;
                }
            }
        }
        if(isXAxis)     perpWallDist = sideDist.x - deltaDist.x;
        else            perpWallDist = sideDist.y - deltaDist.y;

        // Calculate height of line to draw on screen
        int lineHeight = (int)(windowSize.y / perpWallDist) ;   //divide by 2 to count only half of the screen

        //calculate lowest and highest pixel to fill in current Stripe
        int drawStart = lineHeight + (windowSize.y >> 1);
        int drawEnd = -lineHeight + (windowSize.y >> 1);

        int textureNum = map[mapPos.x][mapPos.y] - 1; //to start from 0
        //TODO: Create Stripe with some texture and draw it or make buffer then draw it

        double wallX; //where exactly the wall was hit
        if(isXAxis)     wallX = position.y + perpWallDist * rayDir.y;
        else            wallX = position.x + perpWallDist * rayDir.x;
        wallX -= std::floor(wallX);

        //x coordinate on the texture
        int texX = (int)(wallX * (float)textureSize.x);
        if(isXAxis && rayDir.x > 0) texX = (int)textureSize.x - texX - 1;
        if(!isXAxis && rayDir.y < 0) texX = (int)textureSize.x - texX - 1;

        //update Stripe
        stripes[i]->update(texX , drawStart, drawEnd, textureNum);

    }
    for(auto& stripe : stripes){
        stripe->Render(window);
    }
}