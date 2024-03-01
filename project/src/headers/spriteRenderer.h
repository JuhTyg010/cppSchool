//
// Created by juhtyg on 19.2.24.
//

#ifndef INC_3D_GAME_SPRITERENDERER_H
#define INC_3D_GAME_SPRITERENDERER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class spriteRenderer {
private:
    sf::IntRect rectSourceSprite;
    sf::Vector2f matrix;
    sf::Vector2f currentFrame;
    //sf::Texture& texture;
public:
    sf::Sprite sprite;
    spriteRenderer() = default;
    spriteRenderer(sf::Texture& texture, sf::Vector2f position, sf::Vector2f scale, sf::Vector2f  size, sf::Vector2f matrix);
    void nextFrame();
    void prevFrame();

    void nextAnimation();
    void prevAnimation();
    void Render(sf::RenderWindow &window);
    void setPosition(sf::Vector2f position);
    void setTextureRect(sf::IntRect rect);
    void setScale(sf::Vector2f scale_);
    sf::Vector2f getCurrentFrame();

};


#endif //INC_3D_GAME_SPRITERENDERER_H
