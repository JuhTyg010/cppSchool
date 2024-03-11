//
// Created by juhtyg on 1.3.24.
//

#include "../headers/Stripe.h"

Stripe::Stripe(sf::Vector2f position, Texture& texture)
    : position(position), size(texture.getSize()), matrix(texture.getMatrix()), scale(1) {
    sprite = std::make_unique<spriteRenderer>
            (spriteRenderer(texture, position, sf::Vector2f(1, texture.getSize().y)));
    std::cout << sprite->sprite.getOrigin().x << sprite->sprite.getOrigin().y << std::endl;
}

Stripe::Stripe(const Stripe &other)
    : position(other.position), size(other.size), matrix(other.matrix), scale(other.scale), sprite(std::make_unique<spriteRenderer>(*other.sprite)){}

void Stripe::rescale(int drawStart, int drawEnd, bool isHorizontal) {
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

void Stripe::update(int dist, int drawStart, int drawEnd, int textureNum, bool isHorizontal) {
    //sprite->setPosition(position);
    rescale(drawStart, drawEnd, isHorizontal);
    if(isHorizontal)    sprite->setTextureRect(sf::IntRect(size.x * textureNum, dist, size.x, 1));
    else                sprite->setTextureRect(sf::IntRect(dist + (textureNum*size.x), textureNum, 1, size.y));
}

void Stripe::Render(sf::RenderWindow &window) {
    sprite->Render(window);
}

