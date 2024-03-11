//
// Created by juhtyg on 11.3.24.
//

#ifndef INC_3D_GAME_ITEM_H
#define INC_3D_GAME_ITEM_H

#include "VisibleObject.h"

class Item : public VisibleObject {

public:

    Item(Texture &texture, sf::Vector2f position, sf::Vector2f size);

    Item(const Item& other);

    void Update(float deltaTime) override;
    void Update(sf::Vector2f position, sf::Vector2f size);

    Item copy() const;

};


#endif //INC_3D_GAME_ITEM_H
