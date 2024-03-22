//
// Created by juhtyg on 22.3.24.
//

#include "../headers/UIText.h"

UIText::UIText(const std::string& text, const sf::Font& font, const sf::Vector2f& position, const sf::Color& color, unsigned int size)
        : font(font) {
    this->text.setFont(font);
    this->text.setString(text);
    this->text.setPosition(position);
    this->text.setFillColor(color);
    this->text.setCharacterSize(size);
}

void UIText::UpdateText(const std::string& text) {
    this->text.setString(text);
}

void UIText::Render(sf::RenderWindow& window) {
    window.draw(text);
}