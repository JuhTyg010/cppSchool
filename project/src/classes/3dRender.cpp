//
// Created by juhtyg on 23.2.24.
//

#include "../headers/3dRender.h"


Camera::Camera(sf::Vector2f plane, sf::Vector2u windowSize, std::vector<std::vector<int>>& map) : plane(plane), windowSize(windowSize), map(map) {}

Camera::Camera(float planeX, float planeY, unsigned int windowWidth, unsigned int windowHeight, std::vector<std::vector<int>>& map) :
        plane(planeX, planeY), windowSize(windowWidth, windowHeight), map(map) {}

Camera::Camera(const Camera &other) : plane(other.plane), windowSize(other.windowSize), map(other.map) {}

void Camera::render(const sf::Vector2f &position, const sf::Vector2f &direction, sf::RenderWindow &window) {
    for(int i = 0; i < windowSize.x; i++){
        //calculate ray position and direction
        float cameraX = 2 * i / float(windowSize.x) - 1;
        sf::Vector2f rayDir = direction + plane * cameraX;

        //which box of the map we're in
        sf::Vector2i mapPos = sf::Vector2i(position.x, position.y);

        //length of ray from current position to next x or y-side for more see docs
        sf::Vector2f sideDist;

        //length of ray from one x or y-side to next x or y-side (if rayDir.x or rayDir.y == 0 it will be infinity)
        sf::Vector2f deltaDist = sf::Vector2f(std::abs(1 / rayDir.x), std::abs(1 / rayDir.y));
        float perpWallDist;

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
            if(map[mapPos.x][mapPos.y] > 0)     isHit = true;
        }
        if(isXAxis)     perpWallDist = sideDist.x - deltaDist.x;
        else            perpWallDist = sideDist.y - deltaDist.y;

        //Calculate height of line to draw on screen
        int lineHeight = (int)(windowSize.y / perpWallDist);
        int pitch = 100;

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + windowSize.y / 2 + pitch;
        if(drawStart < 0)   drawStart = 0;
        int drawEnd = lineHeight / 2 + windowSize.y / 2 + pitch;
        if(drawEnd >= windowSize.y) drawEnd = windowSize.y - 1;

        int textureNum = map[mapPos.x][mapPos.y] - 1; //to start from 0
        //TODO: Create stripe with some texture and draw it or make buffer then draw it


        //window.draw(line, 2, sf::Lines);
    }
}