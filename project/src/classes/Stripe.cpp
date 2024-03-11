//
// Created by juhtyg on 1.3.24.
//

#include "../headers/Stripe.h"

Stripe::Stripe(sf::Vector2f position, Vector2d size, Texture& texture, bool isHorizontal)
    : position(position), actualSize(size), isHorizontal(isHorizontal) {
    sprite = std::make_unique<spriteRenderer>(spriteRenderer(texture, position, size));
}

Stripe::Stripe(const Stripe &other)
    : position(other.position), actualSize(other.actualSize), sprite(std::make_unique<spriteRenderer>(*other.sprite)){}

void Stripe::rescale(int drawStart, int drawEnd) {
    if(isHorizontal){
        int width = std::abs(drawEnd - drawStart);
        float scale = (float) width / (float) actualSize.x;
        sprite->setScale(sf::Vector2f(scale, 1));
    } else {
        int height = std::abs(drawEnd - drawStart);
        float scale = (float) height / (float) actualSize.y;
        sprite->setScale(sf::Vector2f(1, scale));
    }
}

void Stripe::update(int Xdistance, int drawStart, int drawEnd, int textureNum) {
    //sprite->setPosition(position);
    rescale(drawStart, drawEnd);
    if(isHorizontal) {
        sprite->setTextureRect(sf::IntRect((int) actualSize.x * textureNum, Xdistance,(int) actualSize.x, 1));
    } else
    sprite->setTextureRect(sf::IntRect(Xdistance,(int) actualSize.y * textureNum, 1,(int) actualSize.y));
}

void Stripe::Render(sf::RenderWindow &window) {
    sprite->Render(window, position);
}

