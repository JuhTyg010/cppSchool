//
// Created by juhtyg on 3.3.24.
//

#ifndef INC_3D_GAME_BUTTON_H
#define INC_3D_GAME_BUTTON_H

#include "spriteRenderer.h"
#include <memory>

class Button {
private:
    sf::Text text;
    std::unique_ptr<spriteRenderer> sprite;
public:
    Button(sf::Vector2f position, sf::Vector2f size, sf::Texture& texture, sf::Vector2f matrix, const std::string& text,
           sf::Font& font, sf::Color color);
    void Render(sf::RenderWindow& window);
    bool isClicked(sf::Vector2i mousePosition);

};


#endif //INC_3D_GAME_BUTTON_H
