//
// Created by juhtyg on 1.3.24.
//

#include "../headers/Stripe.h"

Stripe::Stripe(sf::Vector2f position, Texture& texture, bool isHorizontal)
    : VisibleObject(texture, position, sf::Vector2f(1, texture.getSize().y)), scale(1), isHorizontal(isHorizontal) {}


void Stripe::rescale(int drawStart, int drawEnd) {
    if(isHorizontal){
        int width = std::abs(drawEnd - drawStart);
        scale = (float) width / (float) size.x;
        sprite->setScale(sf::Vector2f(scale, 1));
    } else {
        int height = std::abs(drawEnd - drawStart);
        scale = (float) height / (float) size.y;
        sprite->setScale(sf::Vector2f(1, scale));
    }
}

void Stripe::Update(int dist, int drawStart, int drawEnd, int textureNum, double distance) {
    //sprite->setPosition(position);
    this->distance = distance;
    rescale(drawStart, drawEnd);
    if(isHorizontal)    sprite->setTextureRect(sf::IntRect(size.x * textureNum, dist, size.x, 1));
    else                sprite->setTextureRect(sf::IntRect(dist + (textureNum*size.x), textureNum, 1, size.y));
}



