//
// Created by juhtyg on 3.3.24.
//

#ifndef INC_3D_GAME_BUTTON_H
#define INC_3D_GAME_BUTTON_H

#include "spriteRenderer.h"
#include <memory>

/**
 * @brief Class for button expexting to have text and texture
 * 
 */
class Button {
private:
    sf::Text text;
    std::unique_ptr<spriteRenderer> sprite;
public:

    /**
     * @brief Construct a new Button object
     * 
     * @param texture 
     * @param position 
     * @param size 
     * @param text 
     * @param font 
     * @param color 
     */
    Button(Texture& texture, sf::Vector2f position, sf::Vector2f size, const std::string& text,
           sf::Font& font, sf::Color color);

    /**
     * @brief Render button on window
     * 
     * @param window 
     */
    void Render(sf::RenderWindow& window);

    /**
     * @brief Check if button is clicked
     * 
     * @param mousePosition 
     * @return true if button is clicked
     * @return false otherwise
     */
    bool isClicked(sf::Vector2i mousePosition);

};


#endif //INC_3D_GAME_BUTTON_H
