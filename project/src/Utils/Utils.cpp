//
// Created by juhtyg on 18.2.24.
//
#include "Utils.h"

sf::Vector2f clampVec(sf::Vector2f vec, sf::Vector2f lower, sf::Vector2f upper) {
    sf::Vector2f output;
    output.x = std::min(std::max(vec.x, lower.x), upper.x);
    output.y = std::min(std::max(vec.y, lower.y), upper.y);
    return output;
}


float getDistance(sf::Vector2f vec1, sf::Vector2f vec2) {
    return std::sqrt(std::pow((vec1.x - vec2.x), 2) + std::pow((vec1.y - vec2.y), 2));
}