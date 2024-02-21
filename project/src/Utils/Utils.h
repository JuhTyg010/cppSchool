//
// Created by juhtyg on 18.2.24.
//

#ifndef INC_3D_GAME_UTILS_H
#define INC_3D_GAME_UTILS_H
#include  <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

sf::Vector2f clampVec(sf::Vector2f vec, sf::Vector2f lower, sf::Vector2f upper);
class MyMath {
public:
    static double DegToRad(double deg);
    static double RadToDeg(double rad);
};

double getDistance(sf::Vector2f vec1, sf::Vector2f vec2);

#endif //INC_3D_GAME_UTILS_H
