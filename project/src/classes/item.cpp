//
// Created by juhtyg on 11.3.24.
//

#include "../headers/Item.h"

Item::Item(Texture &texture, sf::Vector2f position, sf::Vector2f size, std::function<void()> action)
            : VisibleObject(texture, position, size), action(action) {}

Item::Item(const Item &other) : VisibleObject(other) , action(other.action){}



void Item::Update(float deltaTime) {
    
}

void Item::Update(sf::Vector2f position, sf::Vector2f size) {
    this->position = position;
    this->size = size;
    sprite->setPosition(position);
    sf::Vector2f scale = divide(size, sprite->getTextureSize());
    sprite->setScale(scale);
}

void Item::OnAction() {
    action();
}

Item Item::copy() const {
    return Item(*this);
}