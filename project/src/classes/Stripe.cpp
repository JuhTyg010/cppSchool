//
// Created by juhtyg on 1.3.24.
//

#include "../headers/Stripe.h"

Stripe::Stripe(sf::Vector2f position, int size, sf::Vector2f matrix, sf::Texture& texture)
    : position(position), size(sf::Vector2i(1,size)), matrix(matrix), scale(1) {
    sprite = std::make_unique<spriteRenderer>
            (spriteRenderer(texture, position, sf::Vector2f(1,1), sf::Vector2f(1,size), matrix));
}

Stripe::Stripe(const Stripe &other)
    : position(other.position), size(other.size), matrix(other.matrix), scale(other.scale), sprite(std::make_unique<spriteRenderer>(*other.sprite)){}

void Stripe::rescale(int drawStart, int drawEnd) {
    int height = std::abs(drawEnd - drawStart);
    scale = (float) height / (float) size.y;
    sprite->setScale(sf::Vector2f(1, scale));
}

void Stripe::update(int Xdistance, int drawStart, int drawEnd, int texture) {
    //sprite->setPosition(position);
    rescale(drawStart, drawEnd);
    sprite->setTextureRect(sf::IntRect(Xdistance, size.y * texture, 1, size.y));
}

void Stripe::Render(sf::RenderWindow &window) {
    sprite->Render(window);
}

