//
// Created by juhtyg on 3.3.24.
//

#include "../headers/button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Texture& texture, sf::Vector2f matrix, const std::string& text,
               sf::Font& font, sf::Color color)
        : text(text, font, 50) {
    sf::Vector2f scale(size.x / texture.getSize().x, size.y / texture.getSize().y);
    sprite = std::make_unique<spriteRenderer>(texture, position, scale, (sf::Vector2f )texture.getSize(), matrix);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, 40);
    this->text.setPosition(position.x , position.y );
    this->text.setFillColor(color);
}

void Button::Render(sf::RenderWindow &window) {
    sprite->Render(window);
    window.draw(text);
}

bool Button::isClicked(sf::Vector2i mousePosition) {
    return sprite->sprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y);
}
