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
    UIText(const std::string& text, const sf::Font& font, const sf::Vector2f& position, const sf::Color& color, unsigned int size);
    void UpdateText(const std::string& text);

    void Render(sf::RenderWindow& window);
};


#endif //INC_3D_GAME_UITEXT_H
