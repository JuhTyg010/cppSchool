//
// Created by juhtyg on 11.3.24.
//

#ifndef INC_3D_GAME_ITEM_H
#define INC_3D_GAME_ITEM_H

#include "VisibleObject.h"

class Item : public VisibleObject {

public:

    /**
     * @brief Construct a new Item object
     * 
     * @param texture 
     * @param position 
     * @param size 
     */
    Item(Texture &texture, sf::Vector2f position, sf::Vector2f size);

    /**
     * @brief Copy construct a new Item object
     * 
     * @param other 
     */
    Item(const Item& other);

    /**
     * @brief this is not implemented is there only for parent class
     * 
     * @param deltaTime 
     */
    void Update(float deltaTime) override;

    /**
     * @brief updates position and size of the item
     * 
     * @param position 
     * @param size 
     */
    void Update(sf::Vector2f position, sf::Vector2f size);

    /**
     * @brief returns a copy of the item
     * 
     * @return Item 
     */
    Item copy() const;

};


#endif //INC_3D_GAME_ITEM_H
