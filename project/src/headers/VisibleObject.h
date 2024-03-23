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
    double distance = 0;    // used for sorting
    VisibleObject() = default;

    /**
     * @brief Construct a new Visible Object object
     * 
     * @param texture 
     * @param position 
     * @param size 
     */
    VisibleObject(Texture& texture, sf::Vector2f position, sf::Vector2f size): position(position), size(size){
        sprite = std::make_unique<spriteRenderer>(texture, position, size);
    }

    /**
     * @brief Copy constructor
     * 
     */
    VisibleObject(const VisibleObject& other): position(other.position), size(other.size),
            sprite(std::make_unique<spriteRenderer>(*other.sprite)){}

    virtual void Update(float dt) = 0;
    virtual void Render(sf::RenderWindow& window){
        sprite->Render(window);
    }
    inline virtual sf::Vector2f getScale() {
        return sprite->sprite.getScale();
    }
    inline virtual sf::Vector2f getPosition() {
        return sprite->sprite.getPosition();
    }

    inline virtual void setPosition(sf::Vector2f position) {
        sprite->sprite.setPosition(position);
    }


    virtual ~VisibleObject() = default;

};

#endif //INC_3D_GAME_VISIBLEOBJECT_H
