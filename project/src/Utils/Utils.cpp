//
// Created by juhtyg on 18.2.24.
//
#include "Utils.h"

#include <utility>



double getDistance(sf::Vector2f vec1, sf::Vector2f vec2) {
    return std::sqrt(std::pow((vec1.x - vec2.x), 2) + std::pow((vec1.y - vec2.y), 2));
}

double MyMath::DegToRad(double deg) {
    return deg * M_PI / 180;
}

double MyMath::RadToDeg(double rad) {
    return rad * 180 / M_PI;
}

Texture::Texture(std::string name, const std::string &path, sf::Vector2f size, sf::Vector2f matrix) :
    name(std::move(name)), size(size), matrix(matrix) {
    texture = std::make_unique<sf::Texture>();
    texture->loadFromFile(path);
}

Texture::Texture(const Texture &other)
: name(other.name), texture(std::make_unique<sf::Texture>(*other.texture)), size(other.size), matrix(other.matrix) {}

const sf::Texture& Texture::getTexture()  {
    return *texture;
}

const sf::Vector2f& Texture::getSize() {
    return size;
}

const sf::Vector2f& Texture::getMatrix() {
    return matrix;
}

const std::string& Texture::getName() {
    return name;
}


const Texture& getTextureByName(const std::string& name, std::vector<Texture>& textures){
    for(Texture& texture : textures){
        if(texture.getName() == name){
            return texture;
        }
    }
    throw std::runtime_error("Texture not found");
}
