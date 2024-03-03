//
// Created by juhtyg on 1.3.24.
//

#include "../headers/Stripe.h"

Stripe::Stripe(int position, int size, sf::Vector2f matrix, sf::Texture& texture)
    : position(position), size(sf::Vector2i(1,size)), matrix(matrix), scale(1) {
    sprite = std::make_unique<spriteRenderer>
            (spriteRenderer(texture, sf::Vector2f(position, 0), sf::Vector2f(1,1), sf::Vector2f(1,size), matrix));
}

Stripe::Stripe(const Stripe &other)
    : position(other.position), size(other.size), matrix(other.matrix), scale(other.scale), sprite(std::make_unique<spriteRenderer>(*other.sprite)){}

void Stripe::rescale(int drawStart, int drawEnd) {
    int height = drawEnd - drawStart;
    scale = (float) height / (float) size.y;
    sprite->setScale(sf::Vector2f(1, scale));
}

void Stripe::update(int Xdistance, int drawStart, int drawEnd, int texture) {
    sprite->setPosition(sf::Vector2f(position, 500-drawStart));
    rescale(drawStart, drawEnd);
    sprite->setTextureRect(sf::IntRect(Xdistance, texture, 1, size.y));
}

void Stripe::Render(sf::RenderWindow &window) {
    sprite->Render(window);
}