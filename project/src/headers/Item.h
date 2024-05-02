//
// Created by juhtyg on 11.3.24.
//

#ifndef INC_3D_GAME_ITEM_H
#define INC_3D_GAME_ITEM_H

#include "VisibleObject.h"
#include <functional>

class Item : public VisibleObject {
private:
    std::function<void()> action;

public:

    /**
     * @brief Construct a new Item object
     * 
     * @param texture 
     * @param position 
     * @param size
     * @param action
     */
    Item(Texture &texture, sf::Vector2f position, sf::Vector2f size, std::function<void()> action = [](){});

    /**
     * @brief Copy construct a new Item object
     * 
     * @param other 
     */
    Item(const Item& other);

    /**
     * @brief updates position and size of the item
     * 
     * @param position 
     * @param size 
     */
    void Update(sf::Vector2f position, sf::Vector2f size);

    /**
     * @brief OnAction is called when the player collides with the item
     *
     * @param action
     */
    void OnAction();

    /**
     * @brief returns a copy of the item
     * 
     * @return Item 
     */
    Item copy() const;

};


#endif //INC_3D_GAME_ITEM_H
