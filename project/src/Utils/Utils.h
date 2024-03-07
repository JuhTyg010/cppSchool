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
#include <algorithm> 
#include <iostream> 
#include <filesystem> 

sf::Vector2f clampVec(sf::Vector2f vec, sf::Vector2f lower, sf::Vector2f upper);
std::string getExternalPath();

class MyMath {
public:
    static double DegToRad(double deg);
    static double RadToDeg(double rad);
};
struct Vector2d{
public:
    double x;
    double y;
    Vector2d() = default;
    Vector2d(double x, double y): x(x), y(y) {}
    Vector2d operator+(Vector2d vec) const{
        return {x + vec.x, y + vec.y};
    }
    Vector2d operator-(Vector2d vec) const{
        return {x - vec.x, y - vec.y};
    }
    Vector2d operator*(double scalar) const{
        return {x * scalar, y * scalar};
    }
    Vector2d operator/(double scalar) const{
        return {x / scalar, y / scalar};
    }
};
double getDistance(sf::Vector2f vec1, sf::Vector2f vec2);

#endif //INC_3D_GAME_UTILS_H
