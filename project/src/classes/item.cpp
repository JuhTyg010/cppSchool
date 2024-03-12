//
// Created by juhtyg on 11.3.24.
//

#include "../headers/Item.h"

Item::Item(Texture &texture, sf::Vector2f position, sf::Vector2f size) : VisibleObject(texture, position, size) {}

Item::Item(const Item &other) : VisibleObject(other) {}

void Item::Update(float deltaTime) {
    
}

void Item::Update(sf::Vector2f position, sf::Vector2f size) {
    this->position = position;
    this->size = size;
    sprite->setPosition(position);
    sf::Vector2f scale = divide(size, sprite->getTextureSize());
    sprite->setScale(scale);
    std::cout << "Item::Update: " << position.x << " " << position.y << " " << size.x << " " << size.y << std::endl;
}

Item Item::copy() const {
    return Item(*this);
}