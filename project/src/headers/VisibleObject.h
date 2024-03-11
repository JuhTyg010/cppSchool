//
// Created by juhtyg on 11.3.24.
//

#ifndef INC_3D_GAME_VISIBLEOBJECT_H
#define INC_3D_GAME_VISIBLEOBJECT_H

#include <SFML/Graphics.hpp>
#include "spriteRenderer.h"

class VisibleObject {
protected:
    std::unique_ptr<spriteRenderer> sprite;
    sf::Vector2f position;
    sf::Vector2f size;

public:
    VisibleObject() = default;
    VisibleObject(Texture& texture, sf::Vector2f position, sf::Vector2f size): position(position), size(size){
        sprite = std::make_unique<spriteRenderer>(texture, position, size);
    }
    VisibleObject(const VisibleObject& other): position(other.position), size(other.size), sprite(std::make_unique<spriteRenderer>(*other.sprite)){}
    virtual void Update(float dt) = 0;
    virtual void Render(sf::RenderWindow& window){
        sprite->Render(window);
    }
    virtual ~VisibleObject() = default;
};


#endif //INC_3D_GAME_VISIBLEOBJECT_H
