//
// Created by juhtyg on 22.3.24.
//

#ifndef INC_3D_GAME_UITEXT_H
#define INC_3D_GAME_UITEXT_H

#include <SFML/Graphics.hpp>

class UIText{
private:
    sf::Text text;
    sf::Font font;
public:
    /**
     * @brief Construct a new UIText object
     * 
     * @param text 
     * @param font 
     * @param position 
     * @param color 
     * @param size 
     */
    UIText(const std::string& text, const sf::Font& font, const sf::Vector2f& position, const sf::Color& color, unsigned int size);

    /**
     * @brief Change text of the object
     * 
     * @param text 
     */
    void UpdateText(const std::string& text);

    /**
     * @brief Render the text on the window
     * 
     * @param window 
     */
    void Render(sf::RenderWindow& window);
};


#endif //INC_3D_GAME_UITEXT_H
